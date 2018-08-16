// I2C Functions for TE MS5607-02BA03 & MS5611-01BA03
// Patrick Chizek
// Written for CPSS, 8/2018

#include <zephyr.h>
#include <errno.h>
#include <misc/printk.h>
#include <device.h>
#include <i2c.h>
#include <ms56xx.h>
#include <math.h>

/* Calibration values */
uint16_t C[6] = {0};

/* Reset Barometer */
int ms56xx_reset(struct device *ms56xx_dev){

    u8_t reset = BARO_RESET;
    int rc = i2c_write(ms56xx_dev,&reset,1,BARO_ADDR);
    k_sleep(3);
    return rc;

}

/* Reset Barometer and Read PROM for calibration values */
int ms56xx_init(struct device *ms56xx_dev) {
    
    int rc;
    u8_t i2buf[2];
    u8_t prom;

    ms56xx_reset(ms56xx_dev);

    /* Get calibration data */
    for(u8_t i=0;i<6;i++) {

       /* Get address of calibration coefficients */
        prom = BARO_PROM_READ + 2 + (i*2);

        /* Send PROM read command */
        rc = i2c_write(ms56xx_dev,&prom,1,BARO_ADDR);
        //if (rc){return rc;}

        k_sleep(5);

        /* Read 16-Bit PROM data */
        rc = i2c_read(ms56xx_dev,i2buf,2,BARO_ADDR);
        if (rc){return rc;}

        /* Store Calibration Data */
        C[i] = ((i2buf[0] << 8) | i2buf[1]);
        
        k_sleep(1);
    }
    
    #ifdef MS56XX_DEBUG
    printk("%d",C[0]);
    printk(" , ");
    printk("%d",C[1]);
    printk(" , ");
    printk("%d",C[2]);
    printk(" , ");
    printk("%d",C[3]);
    printk(" , ");
    printk("%d",C[4]);
    printk(" , ");
    printk("%d",C[5]);
    printk("\n");
    #endif

    return rc;
}

/* Take Reading from Barometer */
int ms56xx_prime(struct device *ms56xx_dev,u8_t reading) {

    int rc;

    /* Only prime if user is attempting a legal reading */
    if ((reading==MS56XX_PRESS) || (reading==MS56XX_TEMP)){
        rc = i2c_write(ms56xx_dev,&reading,1,BARO_ADDR);
        if (rc){return rc;}
    }
    else{
        return EINVAL;
    }

    return 0;

}

/* Reads the raw values based on the previous priming method (Temperature or Pressure) */
int ms56xx_read_raw(struct device *ms56xx_dev,u8_t raw[]) {
  
    int rc;
    u8_t buf = 0x00;

    /* Send Read Commmand (0x00) */
    rc = i2c_write(ms56xx_dev,&buf,1,BARO_ADDR);
    if (rc){return rc;}
  
    /* Request 24-Bit Reading */ 
    rc = i2c_read(ms56xx_dev,raw, 3,BARO_ADDR);

    return rc;

}

/* Reads ambient pressure and returns it as a floating point value. */
int ms56xx_read_pressure(struct device *ms56xx_dev,struct ms56xx_data *data){
    
    int rc;
    u8_t raw[3];

    rc = ms56xx_read_raw(ms56xx_dev,raw);
    if (rc){return rc;}

    u32_t D1 = (raw[0]<<16) | (raw[1]<<8) | (raw[2]);
    s32_t dT = (int32_t)(((((data->temperature) * 100.0) - 2000) * 8388608) / C[5]);

    #ifdef MS5607

    s64_t OFF  = (int64_t)C[1]*131072 + ((int64_t)C[3]*dT)/64;
    s64_t SENS = (int64_t)C[0]*65536 + ((int64_t)C[2]*dT)/128;

    #endif

    #ifdef MS5611

    s64_t OFF  = (int64_t)C[1]*65536 + ((int64_t)C[3]*dT)/128;
    s64_t SENS = (int64_t)C[0]*32768 + (int64_t)C[2]*dT/256;

    #endif
        
    s32_t P = (D1*SENS/2097152 - OFF)/32768;
        
    data->pressure = P / 100.0;

    return rc;
}

/* Reads ambient temperature and returns it as a floating point value. */
int ms56xx_read_temperature(struct device *ms56xx_dev,struct ms56xx_data *data){

    int rc;
    u8_t raw[3];

    rc = ms56xx_read_raw(ms56xx_dev,raw);
    if (rc){return rc;}

    u32_t D2 = (raw[0]<<16) | (raw[1]<<8) | (raw[2]);
        
    s32_t dT = D2-((u32_t)C[4] << 8);     //update '_dT'

    // Below, 'dT' and '_C[6]'' must be casted in order to prevent overflow
    // A bitwise division can not be dobe since it is unpredictible for signed integers
    s32_t T = 2000 + ((s64_t)dT * C[5])/8388608;
        
    data->temperature = T / 100.0;

    return rc;

}

/* Calculates altitude and returns it as a floating point value */
void ms56xx_calc_altitude(struct ms56xx_data *data){
    
    data->altitude = ((pow((1013.25 / data->pressure), 1/5.257) - 1.0)
    * (data->temperature + 273.15)) / 0.0065;
     
}
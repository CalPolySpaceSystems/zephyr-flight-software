// I2C Functions for TE MS5607-02BA03 & MS5611-01BA03
// Patrick Chizek
// Written for CPSS, 8/2018

#include <zephyr.h>
#include <i2c.h>
#include <ms56xx.h>

// Barometer Configuration
#define MS56XX_PRESS 	(0x48)
#define MS56XX_TEMP 	(0x58)
#define BARO_ADDR 	    (0x76)
#define BARO_RESET 		(0x1E)
#define BARO_PROM_READ 	(0xA0)

// Part definition
#define MS5607
//#define MS5611

// calibration data
uint16_t C[6] = {0};

// Initialize barometer from unknown state
int ms56xx_init(struct device *ms56xx_dev) {
  // reset the barometer
    int rc;
    u8_t buf[2];

    // Reset barometer
    buf = BARO_RESET;
    rc = i2c_write(ms56xx_dev,&buf[0],1,BARO_ADDR);

    ksleep(3);

    // Get calibration data
    for(u8_t i=0;i<6;i++) {

        // Write to request PROM data
        buf = BARO_PROM_READ + (i * 2);

        rc = i2c_write(ms56xx_dev,&buf[0],1,BARO_ADDR);
        if (rc){return rc;}

        // read calibration data
        rc = i2c_read(ms56xx_dev,&buf,2,BARO_ADDR);
        if (rc){return rc;}

        C[i] = ((buf[0] << 8) | buf[1]);

        /* TODO: Test how data is transferred vs stored */

        ksleep(10);
    }
  return;
}

// Primes MS5611 to organize temperature data for reading
int ms56xx_prime(struct device *ms56xx_dev,u8_t reading) {

    if ((reading==MS56XX_PRESS) || (reading==MS56XX_TEMP)){
        rc = i2c_write(ms56xx_dev,&reading,1,BARO_ADDR);
        if (rc){return rc;}
    }
    else{
        return EINVAL;
    }

    return i2c_write(ms56xx_dev,&reading,1,BARO_ADDR);

}


// Reads the raw values based on the previous priming method (Temp or Pressure)
int ms56xx_read_raw(struct device *ms56xx_dev,u8_t raw[]) {
  
    rc = i2c_write(ms56xx_dev,0x00,1,BARO_ADDR);
    if (rc){return rc;}
  
    rc = i2c_read(ms56xx_dev, &raw, 3,BARO_ADDR);
    return rc;

}

int ms56xx_read_float(struct device *ms56xx_dev,u8_t reading,
    struct ms56xx_data *data){
    
    u8_t raw[3];

    rc = ms56xx_read_raw(ms56xx_dev,raw);
    if (rc){return rc;}

    if (reading == MS56XX_PRESS){

        u32_t D1 = (raw[0]<<16) | (raw[1]<<8) | (raw[2]);
        32_t dT = (int32_t)(((((data->temp) * 100.0) - 2000) * 8388608) / C[6]);

        #ifdef MS5607

        64_t OFF  = (int64_t)C[2]*131072 + ((int64_t)C[4]*dT)/64;

        64_t SENS = (int64_t)C[1]*65536 + ((int64_t)C[3]*dT)/128;

        #endif

        #ifdef MS5611

        64_t OFF  = (int64_t)C[2]*65536 + ((int64_t)C[4]*dT)/128;

        64_t SENS = (int64_t)C[1]*32768 + (int64_t)C[3]*dT/256;

        #endif
        
        32_t P = (D1*SENS/2097152 - OFF)/32768;
        
        data->pressure = P / 100.0;

    }

    else if (reading == MS56XX_TEMP){
        
        u32_t D2 = (raw[0]<<16) | (raw[1]<<8) | (raw[2]);
        
        32_t dT = D2-((uint32_t)C[5] << 8);     //update '_dT'

        // Below, 'dT' and '_C[6]'' must be casted in order to prevent overflow
        // A bitwise division can not be dobe since it is unpredictible for signed integers
        32_t T = 2000 + ((int64_t)dT * C[6])/8388608;
        
        data->temp = T / 100.0;
    }

    else {
        return EINVAL;
    }

}

void ms56xx_calc_altitude(struct device *ms56xx_dev,struct ms56xx_data *data){
    data->altitude = ((pow((1013.25 / data->pressure), 1/5.257) - 1.0)
    * (data->temp + 273.15)) / 0.0065;
}
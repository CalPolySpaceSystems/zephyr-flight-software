// I2C Functions for STM A3G4250D
// Patrick Chizek
// Written for CPSS, 6/2017

#include <math.h>
#include <a3g4250d.h>

//Device Address
#define A3G_DEVICE_ADDR (0b1101001)

//CTRL Reg Addresses
#define A3G_CTRL_REG1		0x20 // Toggle axes, data rates
#define A3G_CTRL_REG2		0x21 // HP filter settings
#define A3G_CTRL_REG3		0x22 // Interrupts,DRDY
#define A3G_CTRL_REG4		0x23 // Big/Little Endian,Self_test,SPI Mode
#define A3G_CTRL_REG5		0x24 // HP Filter Enable, FIFO enable, Reboot
#define FIFO_CTRL_REG		0x2E // FIFO Settings

// Status Register
#define A3G_STATUS_REG	0x27

// Output Registers
#define A3G_OUT_START		0x28
#define A3G_OUT_TEMP    0x26

// Registers to find
#define STAT_ZYXOR			0x80
#define STAT_ZYXDA			0x08

// Necessary Variables
struct device *a3g_dev;

static int set_reg(struct device *a3g_dev, u8_t tgt_reg, u8_t dev_opt){

	u8_t buf[2] = {tgt_reg,dev_opt};

	return i2c_write(a3g_dev, &buf, 2, A3G_DEVICE_ADDR);

}

static int a3g_init(struct device *a3g_dev, const char *i2c_inst){

	/* Set up the A3G4250D on the given I2C bus */
	a3g_dev = device_get_binding(i2c_inst);

	rc = i2c_write(a3g_dev, 1,);

  writeReg(A3G_CTRL_REG1,0b00001111,A3G_DEVICE_ADDR); // Enable all Gyro axes, Set Bandwidth
  writeReg(A3G_CTRL_REG2,0b00000011,A3G_DEVICE_ADDR); // High Pass filter settings
  writeReg(A3G_CTRL_REG5,0b00010000,A3G_DEVICE_ADDR); // Enable HP Filter
}

static int a3g_read_raw(struct device *a3g_dev, u8_t *a3g_raw){

	// Allocate array of messages to send (addresses)
	struct i2c_msg msgs[2];

	for (u8_t i=0;i<6;i++){

		/* Send the address to write to */
		msgs[0].buf = (A3G_OUT_START+i);
		msgs[0].len = 1;
		msgs[0].flags = I2C_MSG_WRITE;	

		/* Read from the output register */
		msgs[1].buf = a3g_raw[i];
		msgs[1].len = 1;
		msgs[1].flags = I2C_MSG_WRITE | I2C_MSG_STOP;

		ret = i2c_transfer(a3g_dev, &msgs[0], 2, A3G_DEVICE_ADDR);

		/*
		Wire.beginTransmission(A3G_DEVICE_ADDR);
		Wire.write(A3G_OUT_START + 2*i + 1);
		Wire.endTransmission(false);
		
		Wire.requestFrom(A3G_DEVICE_ADDR,1,true);
		
		a3g_raw[i] = (Wire.read()<< 8);

		Wire.beginTransmission(A3G_DEVICE_ADDR);
		Wire.write(A3G_OUT_START +  2*i);
		Wire.endTransmission(false);
				
		Wire.requestFrom(A3G_DEVICE_ADDR,1,true);
				
		a3g_raw[i] |= (Wire.read());
		*/
	}
	
}

static int a3g_read_flt(struct device *a3g_dev, float *a3g_flt){

	u8_t raw[6];
	rc = read_raw_a3g(a3g_dev, u8_t *raw)

	for (int i=0;i<6;i=i+2){
		a3g_flt[i] = (raw[i] || (raw[i+1]<<8)) * 0.007477);
	}
	
}

/*
void readFixIntA3G(int16_t *fpA3G){

	int16_t raw[3];
	reada3g_raw(raw);

	for (int i=0;i<3;i++){
		fpA3G[i] = round(raw[i] * 0.7477);
	}

}

bool checkReg(byte deviceAddress, byte targetRegister, byte expectedValue){

	Wire.beginTransmission(deviceAddress);
	Wire.write(targetRegister);
	Wire.endTransmission(false);

	Wire.requestFrom(deviceAddress,1,true);
	
	byte regValue = Wire.read();

	if ((regValue & expectedValue) > 0) {
		return true;
	}

	else{
		return false;
	}
	
}
*/
// I2C Library for TE MS5607-02BA03 & MS5611-01BA03
// Patrick Chizek
// Written for CPSS, 8/2018

#ifndef _BARO_H
#define _BARO_H

/* Barometer Commands */
#define MS56XX_PRESS 	(0x48)
#define MS56XX_TEMP 	(0x58)
#define BARO_ADDR 	    (0x76)
#define BARO_RESET 		(0x1E)
#define BARO_PROM_READ 	(0xA0)

/* Part Definition */
#define MS5607
//#define MS5611

/* Debug */
//#define MS56XX_DEBUG

#include <zephyr.h>
#include <i2c.h>

/* NOTE: all data reads must be primed an allow for a 10 ms
 *       delay after priming before reading.
 */

struct ms56xx_data {
  float temperature;
  float pressure;
  float altitude;
};

/* Reset Barometer */
int ms56xx_reset(struct device *ms56xx_dev);

/* Reset Barometer and Read PROM for calibration values */
int ms56xx_init(struct device *ms56xx_dev);

/* Take Reading from Barometer */
int ms56xx_prime(struct device *ms56xx_dev,u8_t reading);

/* Reads the raw values based on the previous priming method (Temperature or Pressure) */
int ms56xx_read_raw(struct device *ms56xx_dev,u8_t raw[]);

/* Reads ambient pressure and returns it as a floating point value. */
int ms56xx_read_pressure(struct device *ms56xx_dev, struct ms56xx_data *data);

/* Reads ambient temperature and returns it as a floating point value. */
int ms56xx_read_temperature(struct device *ms56xx_dev, struct ms56xx_data *data);

/* Calculates altitude and returns it as a floating point value */
void ms56xx_calc_altitude(struct ms56xx_data *data);

#endif

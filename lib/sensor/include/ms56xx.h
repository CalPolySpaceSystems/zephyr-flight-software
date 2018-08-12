// I2C Library for TE MS5607-02BA03 & MS5611-01BA03
// Patrick Chizek
// Written for CPSS, 8/2018

#ifndef _BARO_H
#define _BARO_H

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

// Initialize barometer from unknown state
int ms56xx_init(struct device *ms56xx_dev);

// Primes MS5611 to organize temperature data for reading
int ms56xx_prime(struct device *ms56xx_dev,u8_t reading);

// Reads the raw values based on the previous priming method (Temp or Pressure)
int ms56xx_read_raw(struct device *ms56xx_dev,u8_t raw[]);

int ms56xx_read_float(struct device *ms56xx_dev,u8_t reading,
    struct ms56xx_data *data);

void ms56xx_calc_altitude(struct device *ms56xx_dev,struct ms56xx_data *data);

#endif


// I2C Library for STM A3G4250D
// Patrick Chizek
// Written for CPSS, 6/2017

#ifndef _A3G4250D_H
#define _A3G4250D_H

#include <zephyr.h>
#include <i2c.h>

// Define buffers?

static int set_reg(struct device *a3g_dev, u8_t tgt_reg, u8_t dev_opt);

static int a3g_init(struct device *a3g_dev, const char *i2c_inst);

static int a3g_read_raw(struct device *a3g_dev, u8_t *a3g_raw);

static int a3g_read_flt(struct device *a3g_dev, float *a3g_flt);

#endif
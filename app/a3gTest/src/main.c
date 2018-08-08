/*
 * Copyright (c) 2017 Linaro Limited
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <errno.h>
#include <zephyr.h>
#include <misc/printk.h>
#include <device.h>
#include <i2c.h>
#include <board.h>
#include <a3g4250d.h>
#include <string.h>

#if defined(CONFIG_SOC_QUARK_SE_C1000_SS)
#define I2C_DEV CONFIG_I2C_SS_0_NAME
#else
#define I2C_DEV CONFIG_I2C_0_NAME
#endif

/* 1000 msec = 1 sec */
#define SLEEP_TIME 	1000

void main(void)
{
	float gyr_data[3];

	// Init i2c
	a3g_init(a3g_dev, I2C_DEV);

	while (1) {

		rc = a3g_read_flt(a3g_dev, &gyr_data);

		if(rc){
			printk("Error");
		}

		else{
			printk(gyr_data[0],',',gyr_data[1],',',gyr_data[2]);
		}

		k_sleep(SLEEP_TIME);
	}
}
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
#include <ms56xx.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

#if defined(CONFIG_SOC_QUARK_SE_C1000_SS)
#define I2C_DEV CONFIG_I2C_SS_0_NAME
#else
#define I2C_DEV CONFIG_I2C_1_NAME
#endif

/* 1000 msec = 1 sec */

struct ms56xx_data baro;

void main(void)
{
	int rc;

	// Necessary Variables
	struct device *ms56xx_dev;

	// Init i2c
	ms56xx_dev = device_get_binding(I2C_DEV);

	rc = ms56xx_init(ms56xx_dev);
	
	//k_sleep(2000);

	while (1) {

		rc = ms56xx_prime(ms56xx_dev,MS56XX_TEMP);
		if(rc){
			printk("Prime Temp Error\n"); 
		}
		//printk("Temp Primed\n");
		k_sleep(10);

		rc = ms56xx_read_temperature(ms56xx_dev,&baro);
		if(rc){
			printk("Read Temp Error\n");
		}
		//printk("Temp Read\n");
		k_sleep(1);

		rc = ms56xx_prime(ms56xx_dev,MS56XX_PRESS);
		if(rc){
			printk("Prime Pressure Error\n");
		}

		//printk("Pressure Primed\n");
		k_sleep(10);

		rc = ms56xx_read_pressure(ms56xx_dev,&baro);
		if(rc){
			printk("Read Pressure Error\n");
		}
		//printk("Pressure Read\n");

		// Calculate altitude
		ms56xx_calc_altitude(&baro);

		// Convert values to integers
		int temp1 = (int32_t)(floor(baro.temperature));
		int press1 = (int32_t)(floor(baro.pressure));
		int alt1 = (int32_t)(floor(baro.altitude));

		int temp2 = (int32_t)floor(1000*(baro.temperature-temp1));
		int press2 = (int32_t)floor(1000*(baro.pressure-press1));
		int alt2  = (int32_t)floor(1000*(baro.altitude-alt1));

		// Print values
		printk("%d",temp1);
		printk(".");
		printk("%d",temp2);
		printk(", ");
		printk("%d",press1);
		printk(".");
		printk("%d",press2);
		printk(", ");
		printk("%d",alt1);
		printk(".");
		printk("%d",alt2);
		printk("\n");

		k_sleep(1000);

	}
	
}
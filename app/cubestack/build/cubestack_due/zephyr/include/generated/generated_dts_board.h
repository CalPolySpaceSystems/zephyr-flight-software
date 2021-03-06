/**************************************************
 * Generated include file for arduino,due
 *               DO NOT MODIFY
 */

#ifndef _DEVICE_TREE_BOARD_H
#define _DEVICE_TREE_BOARD_H

/* flash@80000 */
#define CONFIG_FLASH_BASE_ADDRESS	0x80000
#define CONFIG_FLASH_LOAD_OFFSET	0
#define CONFIG_FLASH_LOAD_SIZE		0
#define CONFIG_FLASH_SIZE		512
#define FLASH_FLASH_0_LABEL		"FLASH_0"
#define FLASH_LABEL			"FLASH_0"

/* memory@20070000 */
#define CONFIG_SRAM_BASE_ADDRESS	0x20070000
#define CONFIG_SRAM_SIZE		96

/* i2c@4008C000 */
#define ATMEL_SAM_I2C_TWI_4008C000_BASE_ADDRESS		0x4008c000
#define ATMEL_SAM_I2C_TWI_4008C000_CLOCK_FREQUENCY	100000
#define ATMEL_SAM_I2C_TWI_4008C000_IRQ_0		22
#define ATMEL_SAM_I2C_TWI_4008C000_IRQ_0_PRIORITY	0
#define ATMEL_SAM_I2C_TWI_4008C000_LABEL		"I2C_0"
#define ATMEL_SAM_I2C_TWI_4008C000_PERIPHERAL_ID	22
#define ATMEL_SAM_I2C_TWI_4008C000_SIZE			296
#define I2C_0_BASE_ADDRESS				ATMEL_SAM_I2C_TWI_4008C000_BASE_ADDRESS
#define I2C_0_CLOCK_FREQUENCY				ATMEL_SAM_I2C_TWI_4008C000_CLOCK_FREQUENCY
#define I2C_0_IRQ					ATMEL_SAM_I2C_TWI_4008C000_IRQ_0
#define I2C_0_IRQ_PRIORITY				ATMEL_SAM_I2C_TWI_4008C000_IRQ_0_PRIORITY
#define I2C_0_LABEL					ATMEL_SAM_I2C_TWI_4008C000_LABEL
#define I2C_0_PERIPHERAL_ID				ATMEL_SAM_I2C_TWI_4008C000_PERIPHERAL_ID
#define I2C_0_SIZE					ATMEL_SAM_I2C_TWI_4008C000_SIZE

/* i2c@40090000 */
#define ATMEL_SAM_I2C_TWI_40090000_BASE_ADDRESS		0x40090000
#define ATMEL_SAM_I2C_TWI_40090000_CLOCK_FREQUENCY	100000
#define ATMEL_SAM_I2C_TWI_40090000_IRQ_0		23
#define ATMEL_SAM_I2C_TWI_40090000_IRQ_0_PRIORITY	0
#define ATMEL_SAM_I2C_TWI_40090000_LABEL		"I2C_1"
#define ATMEL_SAM_I2C_TWI_40090000_PERIPHERAL_ID	23
#define ATMEL_SAM_I2C_TWI_40090000_SIZE			296
#define I2C_1_BASE_ADDRESS				ATMEL_SAM_I2C_TWI_40090000_BASE_ADDRESS
#define I2C_1_CLOCK_FREQUENCY				ATMEL_SAM_I2C_TWI_40090000_CLOCK_FREQUENCY
#define I2C_1_IRQ					ATMEL_SAM_I2C_TWI_40090000_IRQ_0
#define I2C_1_IRQ_PRIORITY				ATMEL_SAM_I2C_TWI_40090000_IRQ_0_PRIORITY
#define I2C_1_LABEL					ATMEL_SAM_I2C_TWI_40090000_LABEL
#define I2C_1_PERIPHERAL_ID				ATMEL_SAM_I2C_TWI_40090000_PERIPHERAL_ID
#define I2C_1_SIZE					ATMEL_SAM_I2C_TWI_40090000_SIZE

/* interrupt-controller@e000e100 */
#define ARM_V7M_NVIC_E000E100_ARM_NUM_IRQ_PRIORITY_BITS		4
#define ARM_V7M_NVIC_E000E100_BASE_ADDRESS			0xe000e100
#define ARM_V7M_NVIC_E000E100_SIZE				3072

/* uart@400E0800 */
#define ATMEL_SAM_UART_400E0800_BASE_ADDRESS		0x400e0800
#define ATMEL_SAM_UART_400E0800_CURRENT_SPEED		115200
#define ATMEL_SAM_UART_400E0800_IRQ_0			8
#define ATMEL_SAM_UART_400E0800_IRQ_0_PRIORITY		1
#define ATMEL_SAM_UART_400E0800_LABEL			"UART_0"
#define ATMEL_SAM_UART_400E0800_PERIPHERAL_ID		8
#define ATMEL_SAM_UART_400E0800_SIZE			292
#define CONFIG_UART_CONSOLE_ON_DEV_NAME			"UART_0"
#define UART_0_BASE_ADDRESS				ATMEL_SAM_UART_400E0800_BASE_ADDRESS
#define UART_0_CURRENT_SPEED				ATMEL_SAM_UART_400E0800_CURRENT_SPEED
#define UART_0_IRQ					ATMEL_SAM_UART_400E0800_IRQ_0
#define UART_0_IRQ_PRIORITY				ATMEL_SAM_UART_400E0800_IRQ_0_PRIORITY
#define UART_0_LABEL					ATMEL_SAM_UART_400E0800_LABEL
#define UART_0_PERIPHERAL_ID				ATMEL_SAM_UART_400E0800_PERIPHERAL_ID
#define UART_0_SIZE					ATMEL_SAM_UART_400E0800_SIZE


/* Following definitions fixup the generated include */
/* This file is a temporary workaround for mapping of the generated information
 * to the current driver definitions.  This will be removed when the drivers
 * are modified to handle the generated information, or the mapping of
 * generated data matches the driver definitions.
 */

/* SoC level DTS fixup file */

#define CONFIG_NUM_IRQ_PRIO_BITS	ARM_V7M_NVIC_E000E100_ARM_NUM_IRQ_PRIORITY_BITS

#define CONFIG_I2C_0_BASE_ADDRESS	ATMEL_SAM_I2C_TWI_4008C000_BASE_ADDRESS
#define CONFIG_I2C_0_NAME		ATMEL_SAM_I2C_TWI_4008C000_LABEL
#define CONFIG_I2C_0_BITRATE		ATMEL_SAM_I2C_TWI_4008C000_CLOCK_FREQUENCY
#define CONFIG_I2C_0_IRQ		ATMEL_SAM_I2C_TWI_4008C000_IRQ_0
#define CONFIG_I2C_0_IRQ_PRI		ATMEL_SAM_I2C_TWI_4008C000_IRQ_0_PRIORITY
#define CONFIG_I2C_0_PERIPHERAL_ID	ATMEL_SAM_I2C_TWI_4008C000_PERIPHERAL_ID
#define CONFIG_I2C_1_BASE_ADDRESS	ATMEL_SAM_I2C_TWI_40090000_BASE_ADDRESS
#define CONFIG_I2C_1_NAME		ATMEL_SAM_I2C_TWI_40090000_LABEL
#define CONFIG_I2C_1_BITRATE		ATMEL_SAM_I2C_TWI_40090000_CLOCK_FREQUENCY
#define CONFIG_I2C_1_IRQ		ATMEL_SAM_I2C_TWI_40090000_IRQ_0
#define CONFIG_I2C_1_IRQ_PRI		ATMEL_SAM_I2C_TWI_40090000_IRQ_0_PRIORITY
#define CONFIG_I2C_1_PERIPHERAL_ID	ATMEL_SAM_I2C_TWI_40090000_PERIPHERAL_ID

#define CONFIG_UART_SAM_PORT_0_NAME	ATMEL_SAM_UART_400E0800_LABEL
#define CONFIG_UART_SAM_PORT_0_BAUD_RATE	ATMEL_SAM_UART_400E0800_CURRENT_SPEED
#define CONFIG_UART_SAM_PORT_0_IRQ	ATMEL_SAM_UART_400E0800_IRQ_0
#define CONFIG_UART_SAM_PORT_0_IRQ_PRIO	ATMEL_SAM_UART_400E0800_IRQ_0_PRIORITY

#define CONFIG_USART_SAM_PORT_0_NAME	ATMEL_SAM_USART_40098000_LABEL
#define CONFIG_USART_SAM_PORT_0_BAUD_RATE	ATMEL_SAM_USART_40098000_CURRENT_SPEED
#define CONFIG_USART_SAM_PORT_1_NAME	ATMEL_SAM_USART_4009C000_LABEL
#define CONFIG_USART_SAM_PORT_1_BAUD_RATE	ATMEL_SAM_USART_4009C000_CURRENT_SPEED
#define CONFIG_USART_SAM_PORT_2_NAME	ATMEL_SAM_USART_400A0000_LABEL
#define CONFIG_USART_SAM_PORT_2_BAUD_RATE	ATMEL_SAM_USART_400A0000_CURRENT_SPEED
#define CONFIG_USART_SAM_PORT_3_NAME	ATMEL_SAM_USART_400A4000_LABEL
#define CONFIG_USART_SAM_PORT_3_BAUD_RATE	ATMEL_SAM_USART_400A4000_CURRENT_SPEED

/* End of SoC Level DTS fixup file */

#endif

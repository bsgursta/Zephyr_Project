#ifndef ZEPHYR_DRIVERS_TSL2951
#define ZEPHYR_DRIVERS_TSL2951

#include <zephyr/drivers/i2c.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/sensor.h>

/* Register Macros*/

#define TSL2591_REG_ENABLE 0x00
#define TSL2591_REG_CONFIG 0x01

#define TSL2591_REG_AILTL  0x04
#define TSL2591_REG_AILTH  0x05
#define TSL2591_REG_AIHTL  0x06
#define TSL2591_REG_AIHTH  0x07
#define TSL2591_REG_NPAILTL	0x08
#define TSL2591_REG_NPAILTH 0x09
#define TSL2591_REG_NPAIHTL 0x0A
#define TSL2591_REG_NPAIHTH 0x0B

#define TSL2591_REG_PERSIST 0x0C
#define TSL2591_REG_PID	0x11
#define TSL2591_REG_ID 	   0x12
#define TSL2591_REG_STATUS 0x13

#define TSL2591_REG_C0DATAL 0x14
#define TSL2591_REG_C0DATAH 0x15
#define TSL2591_REG_C1DATAL 0x16
#define TSL2591_REG_C1DATAH 0x17

#define TSL2591_ADDRESS 0x29 

/* Sensor data */
struct tsl2591_data {
	uint16_t reg_val;
};

//Configuration data
struct tsl2951_config {
	struct i2c_dt_spec i2c;
	uint8_t resolution;
	
#ifdef CONFIG_TSL2591_TRIGGER
	struct gpio_dt_spec int_gpio; //GPIO for interrupt
#endif /* CONFIG_TSL2591_TRIGGER */
};

static DEVICE_API(sensor, tsl2591_api) = {
	.sample_fetch = tsl2591_sample_fetch, //FETCH -> get data from sensor and store in buffer
	.channel_get = tsl2591_channel_get,     //GET -> Non-blocking, get data from buffer formats in struct sensor_value
#ifdef CONFIG_TSL2591_TRIGGER //This must be triggered in the kconfig file
	.attr_set = tsl2591_attr_set,
	.trigger_set = tsl2591_trigger_set,
#endif /* CONFIG_TS$L2591_TRIGGER */
};

#endif

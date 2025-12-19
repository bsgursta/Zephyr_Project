#ifndef TSL2951
#define TSL2951

#include <zephyr/drivers/i2c.h>
#include <zephyr/drivers/gpio.h>

/* Register Macros*/
//All 8-bits

#define TSL2591_REG_ENABLE 0x00
#define TSL2591_REG_CONFIG 0x01
#define TSL2591_REG_ID 	   0x12
#define TSL2591_REG_STATUS 0x13


//Configuration struct
struct tsl2951_config {
	struct i2c_dt_spec sen;
	uint8_t resolution; //Bits of precision
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

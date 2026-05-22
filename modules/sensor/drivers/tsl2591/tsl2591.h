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

/* Command(CMD) Register */
#define CMD_SET				(0b01 << 7) /* Set to 1 for only CMD register */
#define CMD_TRANS_NORMAL 	(0b01 << 5)
#define CMD_TRANS_SF 		(0b11 << 5) /* Special Function */
#define CMD_SF_INTSET		(0b00100)
#define CMD_SF_CLR_ALS		(0b00110)
#define CMD_SF_CLR_ALS_INT	(0b00111)
#define CMD_SF_NO_PER_INT	(0b01010)

/* Enable Register (0x00) */
#define EN_NPIEN_EN			(U1 << 7)
#define EN_SAI_EN			(U1 << 6)
#define EN_AIEN_EN			(U1 << 4)
#define EN_AEN_EN			(U1 << 1)
#define EN_PON_EN			(U1 << 0)

/* Control Register (0x01) */

#define CTRL_SRESET_EN		(0b1 << 7)
#define CTRL_AGAIN_MAX_G	(0b11 << 4)
#define CTRL_AGAIN_HI_G		(0b10 << 4)
#define CTRL_AGAIN_MED_G	(0b01 << 4)
#define CTRL_AGAIN_LOW_G	(0b00 << 4)
#define CTRL_ATIME_600MS	(0b101 << 0)
#define CTRL_ATIME_500MS	(0b100 << 0)
#define CTRL_ATIME_400MS	(0b011 << 0)
#define CTRL_ATIME_300MS	(0b010 << 0)
#define CTRL_ATIME_200MS	(0b001 << 0)
#define CTRL_ATIME_100MS	(0b000 << 0)

/* Persist Register (0x0C) */
#define PERS_APERS_60VAL	(0b1111 << 0)
#define PERS_APERS_55VAL	(0b1110 << 0)
#define PERS_APERS_50VAL	(0b1101 << 0)
#define PERS_APERS_45VAL	(0b1100 << 0)
#define PERS_APERS_40VAL	(0b1011 << 0)
#define PERS_APERS_35VAL	(0b1010 << 0)
#define PERS_APERS_30VAL	(0b1001 << 0)
#define PERS_APERS_25VAL	(0b1000 << 0)
#define PERS_APERS_20VAL	(0b0111 << 0)
#define PERS_APERS_15VAL	(0b0110 << 0)
#define PERS_APERS_10VAL	(0b0101 << 0)
#define PERS_APERS_5VAL		(0b0100 << 0)
#define PERS_APERS_3VAL		(0b0011 << 0)
#define PERS_APERS_2VAL		(0b0010 << 0)
#define PERS_APERS_ANYVAL	(0b0001 << 0)
#define PERS_APERS_EVERYVAL	(0b0000 << 0)


/* Sensor data */
struct tsl2591_data {
	uint16_t reg_val;

#ifdef CONFIG_TSL2591_TRIGGER
	const struct device *dev;
	struct gpio_callback gpio_cb;
    struct k_work work;	
#endif /* CONFIG_TSL2591_TRIGGER */
};

/* Sensor Configuration Data*/
struct tsl2951_config {
	struct i2c_dt_spec i2c;
	uint8_t resolution;

};


/*
__subsystem struct sensor_driver_api {
	sensor_attr_set_t attr_set;
	sensor_attr_get_t attr_get;
	sensor_trigger_set_t trigger_set;
	sensor_sample_fetch_t sample_fetch;
	sensor_channel_get_t channel_get;
	sensor_get_decoder_t get_decoder;
	sensor_submit_t submit;
};
*/

/* Function ptr table */
static const struct 

static DEVICE_API(sensor, tsl2591_api) = {
	.sample_fetch = tsl2591_sample_fetch, //FETCH -> get data from sensor and store in buffer
	.channel_get = tsl2591_channel_get,     //GET -> Non-blocking, get data from buffer formats in struct sensor_value
#ifdef CONFIG_TSL2591_TRIGGER //This must be triggered in the kconfig file
	.attr_set = tsl2591_attr_set,
	.trigger_set = tsl2591_trigger_set,
#endif /* CONFIG_TS$L2591_TRIGGER */
};

#endif

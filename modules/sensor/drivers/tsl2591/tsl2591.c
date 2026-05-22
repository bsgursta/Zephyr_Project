#define DT_DRV_COMPAT adafruit_tsl2591 // Tie to devicetree compatible node

/*https://docs.zephyrproject.org/latest/hardware/peripherals/sensor/index.html*/

#include <errno.h>
#include <zephyr/logging/log.h> 
#include <zephyr/drivers/i2c.h>
#include <zephyr/include/zephyr/drivers/sensor.h>

#include "tsl2591.h"

LOG_MODULE_REGISTER(tsl2591,CONFIG_SENSOR_LOG_LEVEL); //Enable logging at CONFIG_LOG_DEFAULT_LEVEL <- This is a Kconfig variable


/* Forward Declarations */

static int tsl2591_reg_read(const struct device *dev,
                            uint8_t reg,
                            uint16_t *val);

static int tsl2591_reg_write(const struct device *dev, 
                            uint8_t reg, 
                            uint8_t val);

static int tsl2591_init(const struct device *dev);


/* Private Functions */

/* Read register values (8-bit)*/
static int tsl2591_reg_read(const struct device *dev,
                            uint8_t reg,
                            uint16_t *val)
{
    const struct tsl2591_config *cfg = dev->config;

    //Write then read register 
    int ret = i2c_write_read_dt(&cfg->i2c, &reg, sizeof(reg), val, sizeof(*val));
    if (ret == 0) {
		*val = sys_be16_to_cpu(*val);
	}

	return ret;
}


/*Write to registers (8-bit) */
int tsl2591_reg_write(const struct device *dev, 
                            uint8_t reg, 
                            uint8_t val) 
{
    const struct tsl2591_config *cfg = dev->config;
    uint8_t buf[2] = {
		reg,
		val,
	};
    //use generic write function to only write two sets of data NOTE: cfg should be used to apply the dt write
    return i2c_write_dt(&cfg->i2c, buf, sizeof(buf));

}


/* Enable procedure for TSL2591 sensor*/
int tsl2591_enable(const struct device *dev) {
    return tsl2591_reg_write_8bit(dev,TSL2591_REG_ENABLE,0x01);
}

/* Entry function for driver initialization */
static int tsl2591_init(const struct device *dev) {

    //*dev is not suppose to be assigned, it's already initialized by Zephyr, like Linux DD
    const struct tsl2591_config *cfg = dev->config;

    int ret = 0;
    LOG_DBG("Initializing TSL2591 Sensor");

    if(!device_is_ready(cfg->i2c.bus)){
        LOG_ERROR("Bus device is not ready");
        return -ENODEV;
    }
    
    //Attempt to enable sensor
    ret = tsl2591_enable(dev);
    if(ret) {
        LOG_ERR("Couldn't turn on the tsl2591 temp sensor");
        return ret;
    }

    //Set resolution
    ret = tsl2591_reg_write_8bit(dev,)
    if(ret) {
        LOG_ERR("Couldn't set resolution on tsl2591 sensor");
        return ret;
    }

    return ret;

}


/* Public Functions */

static int tsl2591_submit(const struct device *sensor, struct rtio_iodev_sqe *sqe){

}

static int tsl2591_decoder(const struct device *dev, const struct sensor_decoder_api **api) {

}


/* Devicetree Handling */
static const struct sensor_driver_api {
    .attr_set = NULL; // Change sensor settings
    .attr_get = NULL; //Read back sensor settings
    .trigger_set = NULL; //For GPIO alert triggers
    .sample_fetch = NULL;
    .channel_get = NULL;
    .get_decoder = tsl2591_decoder;
    .submit = tsl2591_submit;
};
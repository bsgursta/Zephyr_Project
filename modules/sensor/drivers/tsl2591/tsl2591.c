/*
    Key components
    1) Devicetree Binding -> describe hardware properties
    2) Kconfig -> Enable/disable software features
    3) Sensor Device API -> read sensor channels, get/set runtime attributes, enable/disable
*/

#define DT_DRV_COMPAT ams_tsl2591 // Tie to devicetree compatible node


#include <errno.h>
#include <zephyr/logging/log.h> 
#include <zephyr/drivers/i2c.h>

#include "tsl2591.h"

LOG_MODULE_REGISTER(tsl2591,CONFIG_SENSOR_LOG_LEVEL); //Enable logging at CONFIG_LOG_DEFAULT_LEVEL <- This is a Kconfig variable

/* Forward Declarations */

static int tsl2591_reg_read(const struct device *dev,
                            uint8_t reg,
                            uint16_t *val);

int tsl2591_reg_write_8bit(const struct device *dev, 
                            uint8_t reg, 
                            uint8_t val);

static int tsl2591_init(const struct device *dev);


/* Private Functions */

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

//Write to 8-bit registers, the TSL only has 8 bit registers
int tsl2591_reg_write_8bit(const struct device *dev, 
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

//Write to enable register
int tsl2591_enable(const struct device *dev) {
    return tsl2591_reg_write_8bit(dev,TSL2591_REG_ENABLE,0x01);
}

static int tsl2591_init(const struct device *dev) {
    //*dev is not suppose to be assigned, it's already initialized by Zephyr
    //cast to sensor config, assume that *dev parameter is being populated by zephyr
    const struct tsl2591_config *cfg = dev->config;
    int ret = 0;
    LOG_DBG("Initializing TSL2591 Sensor");

    //Check that the device is ready
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

//Fetch data from the sensor
static int tsl2591_sample_fetch(const struct device *dev, enum sensor_channel chan) {

}

//get data from internal buffer
static int tsl2591_channel_get() {
    
}

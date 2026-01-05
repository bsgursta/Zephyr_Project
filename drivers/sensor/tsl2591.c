/*
    Key components
    1) Devicetree Binding -> describe hardware properties
    2) Kconfig -> Enable/disable software features
    3) Sensor Device API -> read sensor channels, get/set runtime attributes, enable/disable
*/

#include <zephyr/drivers/i2c.h>
/*Tie 'compatible = "custom,tsl2591" node in devicetree and yaml, THIS IS THE COMPANY,NAME THING
    Device tree compatible
*/

#define DT_DRV_COMPAT custom_tsl2591 //SPELLING MUST BE EXACT, replace ',' with '_'

#include <errno.h> //Error Codes
#include <zephyr/logging/log.h> //Driver Logging
#include <zephyr/drivers/i2c.h>
#include "tsl2591.h"

LOG_MODULE_REGISTER(tsl2591); //Enable logging at CONFIG_LOG_DEFAULT_LEVEL <- This is a Kconfig variable

/* Forward Declarations */

static int tsl2591_init(const struct device *dev); //internal zephyr use


/* Private Functions */

//Write to 8-bit registers, the TSL only has this size
int tsl2591_reg_write_8bit(const struct device *dev, uint8_t reg, uint8_t val) {

    const struct jc42_config *cfg = dev->config;
    uint8_t buf[2] = {
		reg,
		val,
	};
    //use generic write function to only write two sets of data NOTE: cfg should be used to apply the dt write
    return i2c_write_dt(&cfg->i2c, buf, sizeof(buf));

}

//Write enable register and turn on the light sensor
int tsl2591_turn_on(const struct device *dev) {
    return tsl2591_reg_write_8bit(dev,TSL2591_REG_ENABLE,0x01);
}

//Initialize tsl
static int tsl2591_init(const struct device *dev) {
    //*dev is not suppose to be assigned, it's already initialized by Zephyr

    int ret = 0;

    //cast to sensor config, assume that *dev parameter is being populated by zephyr
    const struct tsl2591_config *cfg = dev->config;

    //Check that the device is ready
    if(!device_is_ready(cfg->i2c.bus)){
        LOG_ERROR("Bus device is not ready");
        return -ENODEV;
    }
    


    //Attempt to turn on the temp sensor
    ret = tsl2591_turn_on(dev);
    if(ret) {
        LOG_ERR("Couldn't turn on the tsl2591 temp sensor");
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

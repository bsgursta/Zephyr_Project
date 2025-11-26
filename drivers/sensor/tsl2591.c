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

//Initialize tsl
static int tsl2591_init(const struct device *dev) {
    //*dev is not suppose to be assigned, it's already initialized by Zephyr

    int ret;

    //cast to sensor config, assume that *dev parameter is being populated by zephyr
    const struct tsl2591_config *cfg = (const struct tsl2591_config*)dev->config;

    //Fill out the i2c spec
    const struct i2c_dt_spec *sen = &cfg->sen;

    //Check that the device is ready
    if(!device_is_ready(cfg->i2c.bus)){
        LOG_ERROR("Bus device is not ready");
        return -ENODEV;
    }
    
    //SOMETHING ELSE HERE, look at jc42

    return 0;

}

/* Public Functions */

//Fetch data from the sensor
static int tsl2591_sample_fetch(const struct device *dev, enum sensor_channel chan) {

}

//get data from internal buffer
static int tsl2591_channel_get() {

}

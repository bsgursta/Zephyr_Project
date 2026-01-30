#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>


//Get Device Tree Node Identifier
#define LED0_NODE DT_ALIAS(led0)
#define BUTTON0_NODE DT_ALIAS(sw0) //sw0 name found at the top of the DT

//gpio_dr_spec is another option
static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);
static const struct gpio_dt_spec button = GPIO_DT_SPEC_GET(BUTTON0_NODE, gpios);

int main() {
    int ret;
    if(!gpio_is_ready_dt(&led)) {
        return -1;
    }
    if(!gpio_is_ready_dt(&button)) {
        return -1;
    }

    //configure output
    ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE); 
    if(ret < 0) {
        return ret;
    }

    //configure input button
    ret = gpio_pin_configure_dt(&button, GPIO_INPUT); 
    if(ret < 0) {
        return ret;
    }


    while(1) {
        //wait for the button
        while(!gpio_pin_get_dt(&button));

        //toggle
        ret = gpio_pin_toggle_dt(&led);
        if(ret < 0) {
            return ret;
        }
        k_msleep(1000);

    }
    return 0;
}
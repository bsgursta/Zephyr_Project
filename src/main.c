#include <zephyr/random/random.h>


int main() {
    uint32_t rnd;

    while(1) {
        rnd = sys_rand32_get();
        printk("Random value: %u\r\n",rnd);
    
        k_sleep(10000);
    }
    return 0;
}
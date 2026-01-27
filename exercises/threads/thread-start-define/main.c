#include <stdio.h>
#include <zephyr/kernel.h>

#define STACK_SIZE 500
#define TASK_PRIORITY 4


void print_thread_entry( void *p1, void *p2, void *p3)
{
    printk("thread_a: thread started\n");
    while(1) {
        printk("thread_a: thread loop\n");
        k_sleep(K_MSEC(1000));
    }

}

//compile time thread, stack auto allocated
K_THREAD_DEFINE(my_tid, STACK_SIZE,
            print_thread_entry, NULL, NULL, NULL,
            TASK_PRIORITY, 0, 0);



int main() {

    while(1);
    return 0;
}
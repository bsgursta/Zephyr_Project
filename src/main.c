#include <stdio.h>
#include <zephyr/kernel.h>

#define LED_NODE DT_ALIAS(led0)

#define STACK_SIZE 500
#define TASK_PRIORITY 4

extern void print_thread_entry(void *, void *, void *);

//Define the stack for the thread, for supervisor threads
K_THREAD_STACK_DEFINE(my_stack_area,STACK_SIZE);

void print_thread_entry( void *p1, void *p2, void *p3)
{
    printk("thread_a: thread started\n");
    while(1) {
        printk("thread_a: thread loop\n");
        k_sleep(K_MSEC(1000));
    }

}

int main() {
    struct k_thread my_thread_data;

    k_tid_t my_tid = k_thread_create(&my_thread_data,my_stack_area,
                                        K_THREAD_STACK_SIZEOF(my_stack_area),
                                        print_thread_entry,
                                        NULL,NULL,NULL,
                                        TASK_PRIORITY,0,K_NO_WAIT);

    while(1) {

    }

    return 0;
}
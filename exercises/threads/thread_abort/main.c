#include <stdio.h>
#include <zephyr/kernel.h>

#define STACK_SIZE 500
#define TASK_PRIORITY 4


void print_thread_entry( void *p1, void *p2, void *p3)
{
    printk("thread_a: thread started\n");
    int i = 10;

    while(i > 0) {
        printk("thread_a: thread loop\n");
        i -=1;
        k_sleep(K_MSEC(1000));

    }
    //from the define call
        //Useful function
    k_thread_abort(k_current_get());

}

//my_tid is the thread struct we can use to abort
K_THREAD_DEFINE(my_tid, STACK_SIZE,
            print_thread_entry, NULL, NULL, NULL,
            TASK_PRIORITY, 0, 0);



int main() {
    //compile time thread

    while(1);
    return 0;
}
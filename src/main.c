#include <stdio.h>
#include <zephyr/kernel.h>

#define STACK_SIZE 500
#define TASK_PRIORITY 4


void print_thread_entry1( void *p1, void *p2, void *p3)
{
    printk("thread_a: thread started\n");
    while(1) {
        printk("thread_a: thread loop\n");
        printk("thread_a: thread loop\n");
        printk("thread_a: thread loop\n");
        printk("thread_a: thread suspended\n");
        k_thread_suspend(my_thread1);
    }
    //from the define call
        //Useful function
    k_thread_abort(k_current_get());

}

void print_thread_entry2( void *p1, void *p2, void *p3)
{
    printk("thread_b: thread started\n");
    while(1) {
        printk("thread_b: resuming thread_a\n");
        k_thread_resume(my_thread1);

    }
    //from the define call
        //Useful function
    k_thread_abort(k_current_get());

}

//my_tid is the thread struct we can use to abort
K_THREAD_DEFINE(my_thread1, STACK_SIZE,
            print_thread_entry1, NULL, NULL, NULL,
            TASK_PRIORITY - 1, 0, 0);

K_THREAD_DEFINE(my_thread2, STACK_SIZE,
            print_thread_entry2, NULL, NULL, NULL,
            TASK_PRIORITY, 0, 0);



int main() {
    //compile time thread

    while(1);
    return 0;
}
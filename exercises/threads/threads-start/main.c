#include <stdio.h>
#include <zephyr/kernel.h>

#define LED_NODE DT_ALIAS(led0)

int main() {
    #define STACK_SIZE 500
    #define TASK_PRIORITY 5

    //Define the stack for the thread, for supervisor threads
    K_THREAD_STACK_DEFINE(my_thread_stack,STACK_SIZE);

    return 0;
}
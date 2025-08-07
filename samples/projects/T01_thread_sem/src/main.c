#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>


/* size of stack area used by each thread */
#define MY_STACK_SIZE 500

/* scheduling priority used by each thread */
#define MY_PRIORITY1 5
#define MY_PRIORITY2 5

/* Statically define and initialize a semaphore. */
K_SEM_DEFINE(my_sem1, 0, 1);


void my_entry_point1(void)
{
    while (1) {
    printk("Thread 1: Started Thread 1, waiting for semaphore\n");
    k_sem_take(&my_sem1, K_FOREVER);
    printk("Thread 1: Get the semaphore\n");

    for (int i = 0; i < 5 ; i++) {
        printk("Thread 1: In progress....\n");
        k_msleep(1000);
    }

    printk("Thread 1: Finished Execution.\n");
}
}

void my_entry_point2(void)
{
    while (1) {
    printk("Thread 2: started.\n");
    k_msleep(5000);
    printk("Thread 2: Give sempahire now\n");
    k_sem_give(&my_sem1);
    printk("Thread 2: Stopping..\n");
}
}


/* Statically define and initialize a thread. */
K_THREAD_DEFINE(my_tid1, MY_STACK_SIZE,
                my_entry_point1, NULL, NULL, NULL,
                MY_PRIORITY1, 0, 0);

K_THREAD_DEFINE(my_tid2, MY_STACK_SIZE,
                my_entry_point2, NULL, NULL, NULL,
                MY_PRIORITY2, 0, 0);

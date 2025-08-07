#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>

/* size of stack area used by each thread */
#define MY_STACK_SIZE 500

/* scheduling priority used by each thread */
#define MY_PRIORITY 5

/* Statically define and initialize a semaphore. */
K_SEM_DEFINE(my_semA, 0, 1);
K_SEM_DEFINE(my_semB, 1, 1);
K_SEM_DEFINE(my_semC, 1, 1);

void TaskA(void) {
    
    printk("Task A: 1\n");
    k_sem_give(&my_semB);

    k_sem_take(&my_semA, K_FOREVER);
    printk("Task A: 4\n");
    k_sem_give(&my_semB);

    k_sem_take(&my_semA, K_FOREVER);
    printk("Task A: 7\n");
    k_sem_give(&my_semB);
}

void TaskB(void) {

    k_sem_take(&my_semB, K_FOREVER);
    printk("Task B: 2\n");
    k_sem_give(&my_semC);

    k_sem_take(&my_semB, K_FOREVER);
    printk("Task B: 5\n");
    k_sem_give(&my_semC);

    k_sem_take(&my_semB, K_FOREVER);
    printk("Task B: 8\n");
    k_sem_give(&my_semC);
}
void TaskC(void) {

    k_sem_take(&my_semC, K_FOREVER);
    printk("Task C: 3\n");
    k_sem_give(&my_semA);

    k_sem_take(&my_semC, K_FOREVER);
    printk("Task C: 6\n");
    k_sem_give(&my_semA);

    k_sem_take(&my_semC, K_FOREVER);
    printk("Task C: 9\n");
}


K_THREAD_DEFINE(my_tid1, MY_STACK_SIZE,
                TaskA, NULL, NULL, NULL,
                MY_PRIORITY, 0, 0);

K_THREAD_DEFINE(my_tid2, MY_STACK_SIZE,
                TaskB, NULL, NULL, NULL,
                MY_PRIORITY, 0, 0);

K_THREAD_DEFINE(my_tid3, MY_STACK_SIZE,
                TaskC, NULL, NULL, NULL,
                MY_PRIORITY, 0, 0);

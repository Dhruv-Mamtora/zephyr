#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>


/* Statically define and initialize a semaphore.
 * #define K_SEM_DEFINE(name,
 *                      initial_count, 
 *                      count_limit)
 * 
 * Parameters
 *      name:	        Name of the semaphore.
 *      initial_count:	Initial semaphore count.
 *      count_limit:	Maximum permitted semaphore count.
 * 
 * The semaphore can be accessed outside the module where it is defined using:
 * extern struct k_sem <name>; 
 */
K_SEM_DEFINE(my_sem1, 0, 1);



/* size of stack area used by each thread */
#define MY_STACK_SIZE 500

/* scheduling priority used by each thread */
#define MY_PRIORITY1 4
#define MY_PRIORITY2 5


// /* Initialize a semaphore. */
// int k_sem_init (struct k_sem *sem, unsigned int initial_count, unsigned int limit)

// /* Take a semaphore. */
// int k_sem_take (struct k_sem *sem, k_timeout_t timeout)

// /* Give a semaphore. */
// void k_sem_give (struct k_sem *sem)

/* k_sem_init()
 * int k_sem_init ( struct k_sem * sem, 
 *                  unsigned int initial_count,
 *                  unsigned int limit )
 * 
 * Initialize a semaphore.
 * This routine initializes a semaphore object, prior to its first use.
 * When we need to initialize a semaphore dynamically at runtime.
 * 
 * Parameters:
 *              sem:            Address of the semaphore.
 *              initial_count:  Initial semaphore count.
 *              limit:          Maximum permitted semaphore count.
 * 
 * Return values:
 *      0       Semaphore created successfully
 *      -EINVAL	Invalid values
*/

/* k_sem_take()
 * int k_sem_take( struct k_sem * sem,
 *                  k_timeout_t timeout )
 * 
 * Take a semaphore.
 * This routine takes sem.
 *
 * Parameters:
 *      sem     Address of the semaphore.
 *      timeout	Waiting period to take the semaphore, 
 *              or one of the special values K_NO_WAIT and K_FOREVER.
 * Return values:
 *      0   	Semaphore taken.
 *      -EBUSY	Returned without waiting.
 *      -EAGAIN	Waiting period timed out, or 
 *              the semaphore was reset during the waiting period.
*/

// void my_entry_point(int unused1, int unused2, int unused3)
// {
//     while (1) {
//         ...
//         if (<some condition>) {
//             return; /* thread terminates from mid-entry point function */
//         }
//         ...
//     }

//     /* thread terminates at end of entry point function */
// }
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




/*
 * Statically define and initialize a thread.
 * #define K_THREAD_DEFINE ( name, stack_size, entry,
 *                       p1, p2, p3, prio, options, delay)
 *
 * The thread may be scheduled for immediate execution or a delayed start.
 * Thread options are architecture-specific, and can include K_ESSENTIAL, K_FP_REGS, and K_SSE_REGS. Multiple options may be specified by separating them using "|" (the logical OR operator).
 * The ID of the thread can be accessed using:

 * Parameters
 *      name:       Name of the thread.
 *      stack_size: Stack size in bytes.
 *      entry:      Thread entry function.
 *      p1:         1st entry point parameter.
 *      p2:         2nd entry point parameter.
 *      p3:         3rd entry point parameter.
 *      prio:       Thread priority.
 *      options:    Thread options.
 *      delay:      Scheduling delay (in milliseconds), zero for no delay.
 */
K_THREAD_DEFINE(my_tid1, MY_STACK_SIZE,
                my_entry_point1, NULL, NULL, NULL,
                MY_PRIORITY1, 0, 0);

K_THREAD_DEFINE(my_tid2, MY_STACK_SIZE,
                my_entry_point2, NULL, NULL, NULL,
                MY_PRIORITY2, 0, 0);

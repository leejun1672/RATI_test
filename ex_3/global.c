/*
   file global.c
   update global variable by two tasks
*/

/* includes */
#include <linux/kernel.h>	/* decls needed for kernel modules */
#include <linux/module.h>	/* decls needed for kernel modules */
#include <linux/version.h>	/* LINUX_VERSION_CODE, KERNEL_VERSION() */
#include <linux/errno.h>	/* EINVAL, ENOMEM */

/*
  Specific header files for RTAI, our flavor of RT Linux
 */
#include "rtai.h"		/* RTAI configuration switches */
#include "rtai_sched.h"	/* RTAI scheduling */
#include <rtai_sem.h>   /* RTAI semaphores */

MODULE_LICENSE("GPL");

/* globals */
#define ITER 10

static RT_TASK t1;
static RT_TASK t2;
/* function prototypes */
void taskOne(long arg);
void taskTwo(long arg);

int global = 0;

static SEM task1_SEM;
static SEM task2_SEM;

void tasks(void)
{
    int retval;

    /* init the two tasks */
    retval = rt_task_init(&t1,taskOne, 0, 1024, 0, 0, 0);
    retval = rt_task_init(&t2,taskTwo, 0, 1024, 0, 0, 0);

    /* start the two tasks */
    retval = rt_task_resume(&t1);
    retval = rt_task_resume(&t2);
}


void taskOne(long arg)
{
    int i;
    for (i=0; i < ITER; i++)
    {
        rt_sem_wait(&task1_SEM);
        rt_printk("I am taskOne and global = %d................\n", ++global);
        rt_sem_signal(&task2_SEM);
    }
    //rt_sem_delete(&task1_SEM);
}

void taskTwo(long arg)
{
    int i;
    for (i=0; i < ITER; i++)
    {
        rt_sem_wait(&task2_SEM);
        rt_printk("I am taskTwo and global = %d----------------\n", --global);
        rt_sem_signal(&task1_SEM);
    }
    rt_sem_delete(&task1_SEM);
    rt_sem_delete(&task2_SEM);
}



int init_module(void)
{
    printk("start of init_module\n");

    rt_set_oneshot_mode();
    start_rt_timer(1);

    rt_typed_sem_init(&task1_SEM, 1, BIN_SEM | FIFO_Q);
    rt_typed_sem_init(&task2_SEM, 0, BIN_SEM | FIFO_Q);
    tasks();

    printk("end of init_module\n");
    return 0;
}


void cleanup_module(void)
{
    // task end themselves -> not necessary to delete them
    return;
}

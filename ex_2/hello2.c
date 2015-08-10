#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/version.h>
#include <linux/errno.h>

#include "rtai.h"
#include "rtai_sched.h"
#include <rtai_sem.h>

MODULE_LICENSE("GPL");

static RT_TASK print_task;

void print_func(long arg)
{
    rt_printk("Hello world! I am task %u.\n", rt_whoami());
    return;
}

int init_module(void)
{
    int retval;
    
    rt_set_oneshot_mode();

    start_rt_timer(1);

    retval = rt_task_init(&print_task,
                          print_func,
                          0,
                          1024,
                          RT_SCHED_LOWEST_PRIORITY,
                          0,
                          0);
    if (0 != retval) {
        if (-EINVAL == retval) {
            printk("task: task structure is invalid\n");
        } else {
            printk("task: error starting task\n");
        }
        return retval;
    }


    /*
    Start the RT task with rt_task_resume()
    */
    retval = rt_task_resume(&print_task); /* pointer to our task structure */
    if (0 != retval) {
        if (-EINVAL == retval) {
            /* task structure is already in use */
            printk("task: task structure is invalid\n");
        } else {
            /* unknown error */
            printk("task: error starting task\n");
         }
         return retval;
     }
    return 0;
}

void cleanup_module(void)
{
    // task end themselves -> not necessary to delete them
    return;
}

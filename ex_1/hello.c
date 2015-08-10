#include <linux/kernel.h>
#include <linux/module.h>
MODULE_LICENSE("GPL");

int init_module(void)
{
    printk("Hello world!\n");
    return 0;
}

void cleanup_module(void)
{
    printk("Goodbye world!\n");
    return;
}

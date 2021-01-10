#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h> /* printk() */


MODULE_LICENSE("GPL");
MODULE_VERSION("0.01");



static int init(void) {
 printk(KERN_INFO "Loading Driver\n");
 return 0;
}

static void exit(void) {
 printk(KERN_INFO "Unloading driver\n");
 return 0;
}

module_init(init);
module_exit(exit);

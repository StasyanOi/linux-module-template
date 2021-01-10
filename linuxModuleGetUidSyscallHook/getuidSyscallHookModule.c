#include <linux/init.h>

#include <linux/module.h>
#include <linux/kernel.h> /* printk() */
#include <linux/slab.h> /* kmalloc() */
#include <linux/fs.h> /* everything... */
#include <linux/errno.h> /* error codes */
#include <linux/types.h> /* size_t */
#include <linux/proc_fs.h>
#include <linux/fcntl.h> /* O_ACCMODE */
#include <linux/highmem.h>
#include <linux/kallsyms.h>
#include <asm/unistd.h>

MODULE_LICENSE("GPL");
MODULE_VERSION("0.01");


unsigned long **sys_call_table; //(unsigned long*)0xffffffff81a00240;

void pageWriteEnable(void) {
    write_cr0(read_cr0() & (~0x10000));
}

void pageWriteDisable(void) {
    write_cr0(read_cr0() | 0x10000);
}

//function pointer to original sys_open system call
asmlinkage int (*real_getuid)(void);

//Replacement of original call with modified system call
asmlinkage int hook(void) {
    printk(KERN_INFO "intercepted\n");
    return real_getuid();
}

static int init(void) {

    sys_call_table = (unsigned long **) kallsyms_lookup_name("sys_call_table");
    printk(KERN_INFO "sys_table %d", sys_call_table);
    pageWriteEnable();
    real_getuid = (void *) sys_call_table[__NR_getuid];
    sys_call_table[__NR_getuid] = (unsigned long *) hook;
    pageWriteDisable();

    printk(KERN_INFO
    "Loading Driver\n");
    return 0;
}

static void exit(void) {
    pageWriteEnable();
    sys_call_table[__NR_getuid] = (unsigned long *) real_getuid;
    pageWriteDisable();
    printk(KERN_INFO "Clean up\n");
    printk(KERN_INFO "Unloading driver\n");
    return 0;
}

module_init(init);
module_exit(exit);

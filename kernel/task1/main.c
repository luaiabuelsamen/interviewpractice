/*
This is Task 01 of the Eudyptula Challenge
------------------------------------------

Write a Linux kernel module, and stand-alone Makefile, that when loaded
prints to the kernel debug log level, "Hello World!"  Be sure to make
the module be able to be unloaded as well.

The Makefile should build the kernel module against the source for the
currently running kernel, or, use an environment variable to specify
what kernel tree to build it against.

Please show proof of this module being built, and running, in your
kernel.  What this proof is is up to you, I'm sure you can come up with
something.  Also be sure to send the kernel module you wrote, along with
the Makefile you created to build the module.

Remember to use your ID assigned to you in the Subject: line when
responding to this task, so that I can figure out who to attribute it
to.  You can just respond to the task with the answers and all should be
fine.

If you forgot, your id is "***".  But of course you have not
forgotten that yet, you are better than that.
*/

#include <linux/init.h> 
#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Luai Abuelsamen");
MODULE_DESCRIPTION("A simple Hello World Kernel Module");
MODULE_VERSION("1.0");

static int __init hello_init(void) {
    printk(KERN_DEBUG "Hello World!\n");
    return 0;
}

static void __exit hello_exit(void) {
    printk(KERN_DEBUG "Goodbye World!\n");
}

module_init(hello_init);
module_exit(hello_exit);

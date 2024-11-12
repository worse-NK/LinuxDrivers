#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/moduleparam.h>
#include <linux/errno.h>

static int count = 5; // Значение по умолчанию
module_param(count, int, S_IRUGO);
MODULE_PARM_DESC(count, "Number of times to print ZOV");

static int __init zov_module_init(void) {
    int i;

    if (count <= 0) {
        pr_err("Invalid count value: %d. Must be positive.\n", count);
        return -EINVAL; // Ошибка, если count <= 0
    }

    pr_info("ZOV module loaded with count=%d\n", count);

    // Печать "ZOV" указанное количество раз
    for (i = 0; i < count; i++) {
        pr_info("ZOV\n");
    }

    return 0;
}

static void __exit zov_module_exit(void) {
    pr_info("ZOV module unloaded\n");
}

module_init(zov_module_init);
module_exit(zov_module_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Nikimaru");
MODULE_DESCRIPTION("A simple module that prints 'ZOV' a specified number of times");

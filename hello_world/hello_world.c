#include <linux/module.h>  // Основные определения для модулей
#include <linux/kernel.h>  // Определения для KERN_INFO
#include <linux/init.h>    // Макросы для init и exit

// Функция, вызываемая при загрузке модуля
static int __init hello_init(void) {
    pr_info("Hello, world!\n");  // Используем pr_info вместо printk
    return 0;
}

// Функция, вызываемая при выгрузке модуля
static void __exit hello_exit(void) {
    pr_info("Goodbye, world!\n");
}

// Регистрируем функции инициализации и завершения
module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Nikimaru");
MODULE_DESCRIPTION("A simple Hello World Module");
MODULE_VERSION("1.0");

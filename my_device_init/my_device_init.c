#include <linux/module.h>
#include <linux/fs.h>
#include <linux/device.h>

static int my_major = 0;  // Устанавливаем мажорный номер на 0 для динамического выделения
static int my_minor = 0;

static int my_open(struct inode *inode, struct file *file)
{
    pr_info("My device opened.\n");
    return 0;
}

static struct file_operations my_fops = {
    .open = my_open,
};

static struct class *my_class;

static int __init my_driver_init(void)
{
    int ret;

    // Динамически регистрируем устройство
    ret = register_chrdev(my_major, "mydevice", &my_fops);
    if (ret < 0) {
        pr_err("Failed to register device\n");
        return ret;
    }

    // Получаем назначенный мажорный номер
    my_major = ret;
    pr_info("Device registered with major number %d\n", my_major);

    // Создаём класс для устройства (без использования THIS_MODULE)
    my_class = class_create("myclass");
    if (IS_ERR(my_class)) {
        unregister_chrdev(my_major, "mydevice");
        pr_err("Failed to create class\n");
        return PTR_ERR(my_class);
    }

    // Создаём файл устройства в /dev
    device_create(my_class, NULL, MKDEV(my_major, my_minor), NULL, "mydevice");

    return 0;
}

static void __exit my_driver_exit(void)
{
    device_destroy(my_class, MKDEV(my_major, my_minor));
    class_destroy(my_class);
    unregister_chrdev(my_major, "mydevice");

    pr_info("Device unregistered\n");
}

module_init(my_driver_init);
module_exit(my_driver_exit);

MODULE_LICENSE("GPL");

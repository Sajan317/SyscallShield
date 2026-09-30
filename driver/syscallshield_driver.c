#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

#define DEVICE_NAME "syscallshield"

static dev_t device_number;
static struct cdev syscallshield_cdev;
static struct class *syscallshield_class;

static int syscallshield_open(struct inode *inode,
                               struct file *file)
{
    pr_info("syscallshield: device opened\n");
    return 0;
}

static int syscallshield_release(struct inode *inode,
                                 struct file *file)
{
    pr_info("syscallshield: device closed\n");
    return 0;
}

static const struct file_operations syscallshield_fops = {
    .owner = THIS_MODULE,
    .open = syscallshield_open,
    .release = syscallshield_release,
};

static int __init syscallshield_init(void)
{
    int result;

    result = alloc_chrdev_region(
        &device_number,
        0,
        1,
        DEVICE_NAME
    );

    if (result < 0) {
        pr_err("syscallshield: failed to allocate device number\n");
        return result;
    }

    cdev_init(&syscallshield_cdev, &syscallshield_fops);

    result = cdev_add(
        &syscallshield_cdev,
        device_number,
        1
    );

    if (result < 0) {
        unregister_chrdev_region(device_number, 1);
        return result;
    }

    syscallshield_class =
        class_create(DEVICE_NAME);

    if (IS_ERR(syscallshield_class)) {
        cdev_del(&syscallshield_cdev);
        unregister_chrdev_region(device_number, 1);
        return PTR_ERR(syscallshield_class);
    }

    device_create(
        syscallshield_class,
        NULL,
        device_number,
        NULL,
        DEVICE_NAME
    );

    pr_info("syscallshield: driver loaded\n");

    return 0;
}

static void __exit syscallshield_exit(void)
{
    device_destroy(
        syscallshield_class,
        device_number
    );

    class_destroy(syscallshield_class);

    cdev_del(&syscallshield_cdev);

    unregister_chrdev_region(
        device_number,
        1
    );

    pr_info("syscallshield: driver unloaded\n");
}

module_init(syscallshield_init);
module_exit(syscallshield_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("SyscallShield");
MODULE_DESCRIPTION(
    "SyscallShield Linux security device driver"
);
MODULE_VERSION("0.1");

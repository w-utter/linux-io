#include <linux/init.h>
#include <linux/module.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/kernel.h>
#include <linux/uaccess.h>
#include <linux/fs.h>

#define DEVICE_COUNT 1
#define DEVICE_NAME "example_dev"

static int chardev_open(struct inode *inode, struct file *file);
static int chardev_release(struct inode *inode, struct file *file);
static long chardev_ioctl(struct file *file, unsigned int cmd, unsigned long arg);
static ssize_t chardev_read(struct file *file, char __user *buf, size_t count, loff_t *offset);
static ssize_t chardev_write(struct file *file, const char __user *buf, size_t count, loff_t *offset);

static const struct file_operations chardev_fops = {
    .owner      = THIS_MODULE,
    .open       = chardev_open,
    .release    = chardev_release,
    .unlocked_ioctl = chardev_ioctl,
    .read       = chardev_read,
    .write       = chardev_write
};

struct char_device_data {
    struct cdev cdev;
};

static int dev_major = 0;
static struct class *chardev_class = NULL;
static struct char_device_data chardev_data[DEVICE_COUNT];

static int chardev_uevent(struct device *dev, struct kobj_uevent_env *env) {
    add_uevent_var(env, "DEVMODE=%#o", 0666);
    return 0;
}

static int __init chardev_init(void) {
    printk(KERN_INFO "%s: Device mounting\n", DEVICE_NAME);

    int err, i;
    dev_t dev;

    err = alloc_chrdev_region(&dev, 0, DEVICE_COUNT, DEVICE_NAME);

    dev_major = MAJOR(dev);

    chardev_class = class_create(THIS_MODULE, DEVICE_NAME);
    chardev_class->dev_uevent = chardev_uevent;

    for (i = 0; i < DEVICE_COUNT; i++) {
        cdev_init(&chardev_data[i].cdev, &chardev_fops);
        chardev_data[i].cdev.owner = THIS_MODULE;

        cdev_add(&chardev_data[i].cdev, MKDEV(dev_major, i), 1);

        device_create(chardev_class, NULL, MKDEV(dev_major, i), NULL, "%s-%d", DEVICE_NAME, i);
    }
    return 0;
}

static void __exit chardev_exit(void) {
    printk(KERN_INFO "%s: Device unmounting\n", DEVICE_NAME);
    int i;

    for (i = 0; i < DEVICE_COUNT; i++) {
        device_destroy(chardev_class, MKDEV(dev_major, i));
    }

    class_unregister(chardev_class);
    class_destroy(chardev_class);

    unregister_chrdev_region(MKDEV(dev_major, 0), MINORMASK);
}

static int chardev_open(struct inode *inode, struct file *file) {
    printk(KERN_INFO "%s: Device open\n", DEVICE_NAME);
    return 0;
}

static int chardev_release(struct inode *inode, struct file *file) {
    printk(KERN_INFO "%s: Device close\n", DEVICE_NAME);
    return 0;
}

static long chardev_ioctl(struct file *file, unsigned int cmd, unsigned long arg) {
    printk(KERN_INFO "%s: Device ioctl\n", DEVICE_NAME);
    return 0;
}

static ssize_t chardev_read(struct file *file, char __user *buf, size_t count, loff_t *offset) {
    printk(KERN_INFO "%s: Reading device\n", DEVICE_NAME);
    return 0;
}

static ssize_t chardev_write(struct file *file, const char __user *buf, size_t count, loff_t *offset) {
    printk(KERN_INFO "%s: Writing device\n", DEVICE_NAME);
    return 0;
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("URT");

module_init(chardev_init);
module_exit(chardev_exit);

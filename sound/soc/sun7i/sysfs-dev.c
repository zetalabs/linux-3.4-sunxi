#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/kernel.h>
#include <linux/sysfs.h>
#include <linux/miscdevice.h>
#include <linux/device.h>
#include <linux/io.h>
//#include "sysfs-dev.h"

extern void open_linein(void);
extern void close_linein(void);

static struct miscdevice linein_flag_dev = {
	.minor =    MISC_DYNAMIC_MINOR,
	.name =     "linein_flag",
};

static ssize_t linein_flag_show(struct device* cd,struct device_attribute *attr, char* buf)
{
	return 0;
}

static ssize_t linein_flag_store(struct device *dev,struct device_attribute *attr,
		const char *buf, size_t size){

	char flag = *buf;
	if(flag == '1') {
		open_linein();
	}
	else if (flag == '0') {
		close_linein();
	}
	printk("linein---------flag = %c\n", flag);
	return flag;
}

static DEVICE_ATTR(linein_flag, 0666, linein_flag_show, linein_flag_store);

static struct attribute *linein_flag_attributes[] = {
	&dev_attr_linein_flag.attr,
	NULL
};

static struct attribute_group linein_flag_attribute_group = {
	.attrs = linein_flag_attributes
};


static __init int linein_init(void)
{
	misc_register(&linein_flag_dev);
	sysfs_create_group(&linein_flag_dev.this_device->kobj,&linein_flag_attribute_group);
}

static __exit void linein_clean(void)
{
	misc_deregister(&linein_flag_dev);
	sysfs_remove_group(&linein_flag_dev.this_device->kobj,&linein_flag_attribute_group);
}

module_init(linein_init);
module_exit(linein_clean);

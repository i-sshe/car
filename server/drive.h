#include <linux/module.h>
#include <linux/compat.h>
#include <linux/types.h>
#include <linux/errno.h>
#include <linux/smp_lock.h>
#include <linux/kernel.h>
#include <linux/major.h>
#include <linux/slab.h>
#include <linux/mm.h>
#include <linux/mman.h>
#include <linux/vt.h>
#include <linux/init.h>
#include <linux/linux_logo.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/console.h>
#include <linux/kmod.h>
#include <linux/err.h>
#include <linux/device.h>
#include <asm/uaccess.h>
#include <linux/io.h>


//
static int car_driver_open(struct inode *inode, struct file *file);



static ssize_t car_driver_write(struct file *file, const char __user *buf, 
							size_t count, loff_t *ppos);


static int car_driver_init(void);



static void car_driver_exit(void);



//一个重要的结构:
static struct file_operations driver_fops =
{
	.owner = THIS_MODULE,						//,gai;le
	.open = car_driver_open,
	.write = car_driver_write,
};


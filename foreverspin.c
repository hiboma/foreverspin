#include <linux/module.h>
#include <linux/debugfs.h>

MODULE_AUTHOR("hiroya");
MODULE_DESCRIPTION("foreverspin test");
MODULE_LICENSE("GPL");

static spinlock_t lock;
static struct dentry *foreverspin_file;

static void foreverspin(void)
{
	for(;;) { }
}

static ssize_t debugfs_foreverspin_read(struct file *file, char __user *userbuf,
				 size_t count, loff_t *ppos)
{
	spin_lock(&lock);
	foreverspin();
	spin_unlock(&lock);

	return 0;
} 

static struct file_operations fops = {
	.read  = debugfs_foreverspin_read,
};

static int __init foreverspin_init(void)
{
	foreverspin_file = debugfs_create_file("foreverspin", 0666, NULL, NULL, &fops);
	if (!foreverspin_file) {
		printk("Error foreverspin");
		return -ENODEV;
	}
	
	return 0;
}

static void __exit foreverspin_exit(void)
{
	debugfs_remove(foreverspin_file);
}

module_init(foreverspin_init);
module_exit(foreverspin_exit);


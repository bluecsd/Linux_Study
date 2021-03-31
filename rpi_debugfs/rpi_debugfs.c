/* (C) 2019 Austo Kim <austindh.kim@gmail.com>

This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * Author:
 * Austin Kim <austindh.kim@gmail>
 */ 
  
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/platform_device.h>
#include <linux/io.h>
#include <linux/init.h>
#include <linux/memblock.h>
#include <linux/slab.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/cpu.h>
#include <linux/delay.h>
#include <asm/setup.h>
#include <linux/input.h>
#include <linux/debugfs.h>

 uint32_t raspbian_debug_state = 0x1000;
 static struct dentry *raspbian_kernel_debug_debugfs_iface_root;

 static int raspbian_kernel_debug_iface_debugfs_get(void *data, u64 *val)
{
	    printk("===[%s][L:%d][val:%d]===\n", __func__, __LINE__, raspbian_debug_state);
		    *val = raspbian_debug_state;
			    
			    printk("[KERNEL]===[%s][L:%d]==\n", __func__, __LINE__);

				    return 0;
}

static int raspbian_kernel_debug_iface_debugfs_set(void *data, u64 val)
{
		raspbian_debug_state = (uint32_t)val;

			printk("[raspbian] [%s][L:%d], raspbian_debug_state[%lu],value[%lu]===\n", 
													__func__, __LINE__, (long unsigned int)raspbian_debug_state, (long unsigned int)val);
			    	return 0;
}


DEFINE_SIMPLE_ATTRIBUTE(raspbian_kernel_debug_iface_debugfs_fops, raspbian_kernel_debug_iface_debugfs_get, raspbian_kernel_debug_iface_debugfs_set, "%llu\n");

static struct platform_driver kernel_bsp_debug_driver = {
	    .driver     = {
			        .owner  = THIS_MODULE,
					        .name   = "raspbian_debug_iface",
							    },
};

static int __init raspbian_kernel_debug_init(void)
{
	    printk("===[%s][L:%d]===\n", __func__, __LINE__);

		    raspbian_kernel_debug_debugfs_iface_root = debugfs_create_dir("raspbian_debug_iface", NULL);
			    debugfs_create_file("val", S_IRUGO, raspbian_kernel_debug_debugfs_iface_root, NULL, &raspbian_kernel_debug_iface_debugfs_fops);
				     
				    return platform_driver_register(&kernel_bsp_debug_driver);
}

late_initcall(raspbian_kernel_debug_init);

MODULE_DESCRIPTION("raspberrypi debug interface driver");
MODULE_AUTHOR("Austin Kim <austindh.kim@gmail.com>");
MODULE_LICENSE("GPL");

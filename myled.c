/*
 * myled.c
 *
 * Copyright (C) 2017 Takaharu Nakajima <s1526084PQ@s.chibakoudai.jp>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <asm/uaccess.h>
#include <linux/io.h>
#define PIN_NUM 7
#define NUM_MAX 10

MODULE_AUTHOR("Takaharu Nakajima");
MODULE_DESCRIPTION("driver for LED control");
MODULE_LICENSE("GPL");
MODULE_VERSION("0.4");

static dev_t dev;
static struct cdev cdv;
static struct class *cls = NULL;
static volatile u32 *gpio_base = NULL;
static int gpioList[PIN_NUM] = {5, 6, 13, 19, 20, 21, 26};
static int numList[NUM_MAX][PIN_NUM] = {
    {0, 1, 2, 4, 5, 6},
    {2, 5},
    {0, 1, 3, 4, 5},
    {1, 2, 3, 4, 5},
    {2, 3, 5, 6},
    {1, 2, 3, 4, 6},
    {0, 1, 2, 3, 4, 6},
    {2, 4, 5, 6},
    {0, 1, 2, 3, 4, 5, 6},
    {1, 2, 3, 4, 5, 6}
};

static void clearDisplay(void);

static void numDisplay(int num)
{
    int i;

    clearDisplay();

    for(i = 0; i < PIN_NUM; i++) {
        gpio_base[7] = 1 << gpioList[numList[num][i]];
        printk(KERN_INFO "gpio %d on\n", gpioList[numList[num][i]]);
        if(numList[num][i+1] == 0)
            break;
    }

    printk(KERN_INFO "num %d\n", num);
}

static void clearDisplay(void)
{
    int i;
    for(i = 0; i < PIN_NUM; i++)
        gpio_base[10] = 1 << gpioList[i];
}

static ssize_t led_write(struct file* filp, const char* buf, size_t count, loff_t* pos)
{
    char c;
    if(copy_from_user(&c,buf,sizeof(char)))
        return -EFAULT;

    if(c == 'c')
        clearDisplay();
    else if(c-'0' >= 0 && c-'0' < NUM_MAX)
        numDisplay(c-'0');

    printk(KERN_INFO "receive %c\n",c);

    return 1;
}

static struct file_operations led_fops = {
    .owner = THIS_MODULE,
    .write = led_write
};

static int __init init_mod(void)
{
    int retval, i;

    gpio_base = ioremap_nocache(0x3f200000, 0xA0); //0x3f..:base address, 0xA0: region to map

    for(i = 0; i < PIN_NUM; i++){
        const u32 led = gpioList[i];
        const u32 index = led/10;//GPFSEL2
        const u32 shift = (led%10)*3;//15bit
        const u32 mask = ~(0x7 << shift);//11111111111111000111111111111111
        gpio_base[index] = (gpio_base[index] & mask) | (0x1 << shift);//001: output flag
        //11111111111111001111111111111111
    }

    retval =  alloc_chrdev_region(&dev, 0, 1, "myled");
    if(retval < 0){
        printk(KERN_ERR "alloc_chrdev_region failed.\n");
        return retval;
    }
    printk(KERN_INFO "%s is loaded. major:%d\n",__FILE__,MAJOR(dev));

    cdev_init(&cdv, &led_fops);
    retval = cdev_add(&cdv, dev, 1);
    if(retval < 0){
        printk(KERN_ERR "cdev_add failed. major:%d, minor:%d",MAJOR(dev),MINOR(dev));
        return retval;
    }
    printk(KERN_INFO "%s is loaded. major:%d\n",__FILE__,MAJOR(dev));
    cls = class_create(THIS_MODULE,"myled");
    if(IS_ERR(cls)){
        printk(KERN_ERR "class_create failed.");
        return PTR_ERR(cls);
    }
    device_create(cls, NULL, dev, NULL, "myled%d",MINOR(dev));
    return 0;
}

static void __exit cleanup_mod(void)
{
    cdev_del(&cdv);
    device_destroy(cls, dev);
    class_destroy(cls);
    unregister_chrdev_region(dev, 1);
    printk(KERN_INFO "%s is unloaded.\n",__FILE__);
}

module_init(init_mod);
module_exit(cleanup_mod);

/*
 * myled.h
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

static void numDisplay(int);
static void clearDisplay(void);
static ssize_t led_write(struct file*, const char*, size_t, loff_t*);
static int __init init_mod(void);
static void __exit cleanup_mod(void);

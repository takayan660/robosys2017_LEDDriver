#!/bin/bash

sudo rmmod myled

make
sudo insmod myled.ko

sudo mknod /dev/myled0 c 243 0
sudo chmod 666 /dev/myled0 

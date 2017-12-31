#!/bin/bash

MYLED_DIR='/dev/myled0'

modinfo myled.ko

lsmod | grep myled >> /dev/null
if [ $? = 0 ]; then
    sudo rmmod myled
fi

make
sudo insmod myled.ko

if [ -f $MYLED_DIR ]; then
    sudo mknod $MYLED_DIR c 243 0
fi

sudo chmod 666 $MYLED_DIR

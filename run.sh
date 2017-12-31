#!/bin/bash

if [ ! $1 ];then
    echo "NO NUM"
    exit 1
fi

MYLED_DIR='/dev/myled0'

lsmod | grep myled >> /dev/null
if [ $? = 1 ]; then
    ./install.sh
fi

echo $1 > $MYLED_DIR

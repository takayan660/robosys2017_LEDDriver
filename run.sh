#!/bin/bash

if [ ! $1 ];then
    echo "NO NUM"
    exit 1
fi

echo 0 > /dev/myled0
echo $1 > /dev/myled0

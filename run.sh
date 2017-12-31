#!/bin/bash

if [ ! $1 ];then
    echo "NO NUM"
    exit 1
fi

echo $1 > /dev/myled0

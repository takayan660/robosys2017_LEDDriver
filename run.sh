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

if [ $1 = 'r' ]; then
    MAX_REPEAT=300
    for i in `seq $MAX_REPEAT`; do
        echo $(expr $RANDOM / 3276) > $MYLED_DIR
        sleep $(expr $i / $MAX_REPEAT)
    done
    echo $(awk 'BEGIN{srand();print int(rand() * 10)}') > $MYLED_DIR
else
    echo $1 > $MYLED_DIR
fi

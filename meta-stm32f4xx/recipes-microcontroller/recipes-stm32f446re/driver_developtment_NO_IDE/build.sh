#!/bin/bash

#Very simple make

make clean

make all

if [ $? -eq 0 ]; then
    sudo st-flash write stm32f446re.bin 0x8000000
else
    echo "Not equal 0"
fi

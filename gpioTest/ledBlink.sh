#!/bin/bash
# 简单测试脚本（使用 gpioset 控制GPIO引脚高低切换）
CHIP=gpiochip1
LINE=10

for i in {1..10}; do
    sudo gpioset -m time $CHIP $LINE=1
    sleep 1
    sudo gpioset -m time $CHIP $LINE=0
    sleep 1
done

# 执行以下命令运行程序
# chmod +x ledBlink.sh
# ./ledBlink.sh

#
#!/bin/sh

UART_BAUD_RATE=9600

stty -F "/dev/ttyACM$1" cs8 $UART_BAUD_RATE ignbrk -brkint -icrnl -imaxbel -opost -onlcr -isig -icanon -iexten -echo -echoe -echok -echoctl -echoke noflsh -ixon -crtscts
tail -f "/dev/ttyACM$1"

# This script executed, you can send messages to the arduino using:
# echo "message" > /dev/ttyACM$1

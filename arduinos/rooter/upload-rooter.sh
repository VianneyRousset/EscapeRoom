#!/bin/sh

../../arduino-1.8.5/arduino --upload --board arduino:avr:uno --port /dev/ttyACM0 $@ main.cpp

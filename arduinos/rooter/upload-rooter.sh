#!/bin/sh

arduino --upload --board arduino:avr:uno --port /dev/ttyACM0 $@ main.cpp

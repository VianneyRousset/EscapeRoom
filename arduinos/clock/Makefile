ARDUINO_DIR = /usr/share/arduino
ARDMK_DIR = /usr/share/arduino
AVR_TOOLS_DIR = /usr
AVRDUDE_CONF = /etc/avrdude.conf
USER_LIB_PATH := $(realpath ../libs)
ARDUINO_LIBS += debug
ARDUINO_LIBS += communication
ARDUINO_LIBS += private
ARDUINO_LIBS += SoftwareSerial
ARDUINO_LIBS += Wire
#CPP_SOURCE_FILES += /home/antonin/Documents/EscapeRoom/arduinos/includes/* 

BOARD_TAG   = nano
BOARD_SUB   = atmega328
AVRDUDE_ARD_BAUDRATE = 115200
ISP_PORT = /dev/ttyUSB0

#CXXSRC += main.cpp rooting.cpp communication.cpp debug.c
#CPPFLAGS = -I../includes -I.
#CFLAGS = -I../includes -I.

SOURCE_FOLDERS = $(realpath ../includes)

include ${ARDUINO_DIR}/Arduino.mk


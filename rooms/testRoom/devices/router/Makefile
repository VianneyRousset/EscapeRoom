ARDUINO_DIR = /usr/share/arduino
ARDMK_DIR = /usr/share/arduino
AVR_TOOLS_DIR = /usr
AVRDUDE_CONF = /etc/avrdude.conf
USER_LIB_PATH := $(realpath ../../../../libs)

ARDUINO_LIBS += SoftwareSerial 
ARDUINO_LIBS += Wire

ARDUINO_LIBS += debug
ARDUINO_LIBS += communication
ARDUINO_LIBS += logger 
ARDUINO_LIBS += system 

#CPP_SOURCE_FILES += 

BOARD_TAG    = uno

#CXXSRC += main.cpp rooting.cpp communication.cpp debug.c
#CPPFLAGS = -I../includes -I.
#CFLAGS = -I../includes -I.

SOURCE_FOLDERS = $(realpath .)

include ${ARDUINO_DIR}/Arduino.mk


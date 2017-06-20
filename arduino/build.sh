#!/bin/bash
avr-gcc -std=gnu11 -Wall -Wextra -Wno-main -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o led.o ledblink/main.c
avr-gcc -mmcu=atmega328p led.o -o led
avr-objcopy -O ihex -R .eeprom led led.hex
avrdude -F -V -c arduino -p ATMEGA328P -P /dev/ttyUSB0 -b 115200 -U flash:w:led.hex



/*
efRC - library for simple reading the PPM signal from RC receiver.
Copyright (c) 2013 Ivan Efimov. (https://www.facebook.com/spb.limon.spb)
Firstly you should download this http://playground.arduino.cc//Main/PinChangeInt,
and copy it to libraries folder.

To start reading a PPM signal use the initEfRC(const byte * pins, byte count);
First argument is an array of PINs connected to receiver. "count" is a size of this array.

To get the delay time of HIGH signal from i PIN use getPPMDelay(byte i).
i - a number of PIN in pins array you called initEfRC.
*/

#ifndef efTx
#define efTx

#if defined(ARDUINO) && ARDUINO >= 100
  #include <Arduino.h>
  #include <new.h>
#else
  #include <WProgram.h>
  #include <pins_arduino.h>
  #ifndef   LIBCALL_PINCHANGEINT
    #include "../cppfix/cppfix.h"
  #endif
#endif

#define MAX_PIN_NUMBER 8

void initEfRc(const byte * pins, byte count);
unsigned int getPPMDelay(byte i);

#endif
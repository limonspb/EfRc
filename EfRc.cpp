#include "EfRc.h"

#include <../PinChangeInt/PinChangeInt.h>

unsigned long time = 0;
volatile byte ppm_pins[10] = {A0,A1,A2,A3,A4,2,3,4,5,6};
unsigned long risingT[MAX_PIN_NUMBER];
unsigned long fallingT[MAX_PIN_NUMBER];
volatile unsigned int ppm_delays[MAX_PIN_NUMBER];

byte ppm_pin_count = 5;

unsigned int getPPMDelay(byte i){
  return ppm_delays[i];
}

inline byte pin2order(byte pin){
  for (int i = 0; i<ppm_pin_count; i++){
    if (ppm_pins[i] == pin){
	  return i;
	}
  }
  return 255;
}

unsigned long dt;
byte order;

void efRCRising(){
  time = micros();
  order = pin2order(PCintPort::arduinoPin);
  risingT[order] = time;    
}

void efRCFalling(){
  time = micros();
  order = pin2order(PCintPort::arduinoPin);
  fallingT[order] = time;
  dt = fallingT[order] - risingT[order];
  if (dt > 500 && dt < 2500){
    ppm_delays[order] = dt;
  }
}

void initEfRc(const byte * pins, byte count){
  ppm_pin_count = count;
  for (int i = 0; i<ppm_pin_count; i++){
    ppm_pins[i] = pins[i];
    PCintPort::attachInterrupt(ppm_pins[i], efRCRising, RISING);
    PCintPort::attachInterrupt(ppm_pins[i], efRCFalling, FALLING);
    pinMode(ppm_pins[i], INPUT);
  }
}
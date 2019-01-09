/*
   LiVduino LCD test

   alfredc333
   2018
   MIT License
*/

#include <Arduino.h>

#include <Wire.h>
#include "SSD1306Ascii.h"
#include "SSD1306AsciiWire.h"

//OLED display
SSD1306AsciiWire oled;

#define LOOP_TIME 2000
long int loopCounter = 0; 

void setup() {
  //init serial port
  Serial.begin(9600);
  
  //init OLED
  Wire.begin();
  oled.begin(&Adafruit128x64, 0x3C);
  oled.setFont(System5x7);
  oled.set2X();
  oled.clear();
}

void loop() {
  displayData();
  delay(LOOP_TIME);
  loopCounter++;
}

void displayData() {
  oled.clear();
  oled.println("T:  " + String("temp."));
  oled.println("H:  " + String("humid."));
  oled.println("P: " + String("air p."));
  oled.println( "Loop: " + String(loopCounter));
}



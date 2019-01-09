/*
   LiVduino BME280 test
   
   alfredc333
   2018
   MIT License
*/

#include <Arduino.h>

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#define BME_SCK 13
#define BME_MISO 12
#define BME_MOSI 11
#define BME_CS 10
#define SEALEVELPRESSURE_HPA (1013.25)
Adafruit_BME280 bme; // I2C
//Adafruit_BME280 bme(BME_CS); // hardware SPI
//Adafruit_BME280 bme(BME_CS, BME_MOSI, BME_MISO, BME_SCK); // software SPI

long int loopCounter = 0;

void setup() {
  //init serial port
  Serial.begin(9600);

  //init I2C library
  // default settings
  // (you can also pass in a Wire library object like &Wire2)
  bool status;
  status = bme.begin();
  if (!status) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }  
}

void loop() {
  loopCounter++;
  Serial.print("******************\n");
  Serial.print("Loop no: " + String(loopCounter) + "\n");
  float t = -100;
  float h = -100;
  float ap = -100;

  readSensor(t, h, ap);
  Serial.println("temp :   " + String(t));
  Serial.println("hum :   " + String(h));
  Serial.println("air p. :   " + String(ap));
  delay(5000);
}

void readSensor(float &t, float &h, float &ap) {
  t  = bme.readTemperature();
  h  = bme.readHumidity();
  ap = (bme.readPressure()) / 100.0F;
}


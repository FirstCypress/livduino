/*
   LiVduino - nodeMCU

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

//#include <Wire.h>
#include "SSD1306Ascii.h"
#include "SSD1306AsciiWire.h"

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include "ThingSpeak.h"

//NodeMCU WiFi
ESP8266WiFiMulti WiFiMulti;
const char accessPointName[]     = "YOUR_ACESS_POINT_NAME";
const char accessPointPassword[] = "PASSWORD";

//OLED display
SSD1306AsciiWire oled;

//Thingspeak
int status  = WL_IDLE_STATUS;
WiFiClient  client;
unsigned long myChannelNumber = YOUR_CHANNEL_NUMBER;
const char * myWriteAPIKey = "WRITE_API_KEY";

//60000 is 60 sec
#define LOOP_TIME 120000
int loopCounter = 1;

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
  
  //init OLED
  Wire.begin();
  oled.begin(&Adafruit128x64, 0x3C);
  oled.setFont(System5x7);
  oled.set2X();
  oled.clear();

  //init WiFi
  WiFiMulti.addAP(accessPointName, accessPointPassword);

  //ThingSpeak
  WiFi.begin(accessPointName, accessPointPassword);
  ThingSpeak.begin(client);
}

void loop() {
  Serial.print("Loop no: " + String(loopCounter) + "\n");
  float t = -100;
  float h = -100;
  float ap = -100;

  readSensor(t, h, ap);
  displayData(t, h, ap, loopCounter);
  updateThingSpeak(t, h, ap);
  delay(LOOP_TIME);
  loopCounter++;
}

void readSensor(float &t, float &h, float &ap) {
  t  = bme.readTemperature();
  h  = bme.readHumidity();
  ap = (bme.readPressure()) / 100.0F;
  /** 
  t = 100;
  h = 200;
  ap = 300;
  **/
}

void displayData(float t, float h, float ap, int l) {
  oled.clear();
  oled.println("T:  " + String(t));
  oled.println("H:  " + String(h));
  oled.println("P: " + String(ap));
  oled.println( "Time: " + String( (l-1)*(LOOP_TIME/60000) )  );
}


void updateThingSpeak(float temp, float humid, float light) {
  Serial.println("Write data to ThingSpeak");
  ThingSpeak.setField(1, temp);
  ThingSpeak.setField(2, humid);
  ThingSpeak.setField(3, light);
  // Write the fields that you've set all at once.
  ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
}



/*
   LiVduino Thingspeak test
   alfredc333
   2018
   MIT License
*/

#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include "ThingSpeak.h"

//NodeMCU WiFi
ESP8266WiFiMulti WiFiMulti;
const char accessPointName[]     = "YOUR_ACCESS_POINT_NAME";
const char accessPointPassword[] = "PASSWORD";

//Thingspeak
int status  = WL_IDLE_STATUS;
WiFiClient  client;
unsigned long myChannelNumber = YOUR_CHANNEL_NUMBER;
const char * myWriteAPIKey = "YOUR_WRITE_API_KEY";

#define LOOP_TIME 120000
long int loopCounter = 0;
 
void setup() {
  
  //init serial port
  Serial.begin(9600);

  //init WiFi
  WiFiMulti.addAP(accessPointName, accessPointPassword);

  //init ThingSpeak
  WiFi.begin(accessPointName, accessPointPassword);
  ThingSpeak.begin(client);
}

void loop() {
  loopCounter++;
  updateThingSpeak();
  delay(LOOP_TIME);
}

void updateThingSpeak() {  
  Serial.println("Write data to ThingSpeak");
  ThingSpeak.setField(1, 100);
  ThingSpeak.setField(2, 200);
  ThingSpeak.setField(3, 300);
  // Write the fields that you've set all at once.
  ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
}


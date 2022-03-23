#define BLYNK_TEMPLATE_ID           "TMPLPNl_fI0M"
#define BLYNK_DEVICE_NAME           "Quickstart Device"
#define BLYNK_AUTH_TOKEN            "GN-2wNwz0_J_mnHFBG3bBTtmf3VyCGI0"

#define BLYNK_PRINT Serial

#define DHTTYPE DHT22
#define DHTPIN 4

#define ESP8266_BAUD 9600
#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>
#include <SoftwareSerial.h>
#include "DHT.h"

#include <Wire.h>
#include <BH1750.h>

//BH1750 GY302;

BlynkTimer timer;
SoftwareSerial EspSerial(2, 3); // RX, TX
 
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "beom6452";
char pass[] = "01027306452";
 

ESP8266 wifi(&EspSerial);

DHT dht(DHTPIN, DHTTYPE);

const int soilSensorPin = A0;


void setup()
{
  Serial.begin(9600);

  EspSerial.begin(ESP8266_BAUD);
  
  Blynk.begin(auth, wifi, ssid, pass);

  dht.begin();
  
  //GY302.begin();

  
  timer.setInterval(1000L, myTimerEvent1);
  timer.setInterval(1000L, myTimerEvent2);
  //timer.setInterval(1000L, myTimerEvent3);
  timer.setInterval(1000L, myTimerEvent4);
  
}

void myTimerEvent1()
{
  float h = dht.readHumidity();
  Blynk.virtualWrite(V1, h);
  Serial.print(h);
  Serial.print(" ");
}
 
void myTimerEvent2()
{
  float t = dht.readTemperature();
  Blynk.virtualWrite(V0, t);
  Serial.print(t);
  Serial.print(" ");
}


void myTimerEvent3()
{
  //uint16_t lux = GY302.readLightLevel();
  Serial.print("Light: ");
  //Serial.print(lux);
  Serial.println(" lx");

  delay(1000);
  //Blynk.virtualWrite(V2, lux);
}

void myTimerEvent4()
{
  Blynk.virtualWrite(V3, analogRead(soilSensorPin));
  Serial.println(analogRead(soilSensorPin));
}

void loop()
{

  Blynk.run();
  timer.run();
}

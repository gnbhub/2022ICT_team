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

//조도센서
#include <Wire.h>
#include <BH1750.h>
BH1750 lightMeter;

BlynkTimer timer;
SoftwareSerial EspSerial(2, 3); // RX, TX
 
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "beom6452";
char pass[] = "01027306452";

ESP8266 wifi(&EspSerial);
 
DHT dht(DHTPIN, DHTTYPE);
 
void setup()
{
  Serial.begin(9600);
  delay(10);
 
  EspSerial.begin(ESP8266_BAUD);
  delay(10);
 
  Blynk.begin(auth, wifi, ssid, pass);
  timer.setInterval(1000L, myTimerEvent1);
  timer.setInterval(1000L, myTimerEvent2);
  timer.setInterval(1000L, myTimerEvent3);
  dht.begin();
  lightMeter.begin();
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
  uint16_t lux = lightMeter.readLightLevel();
  Blynk.virtualWrite(V2, lux);
  Serial.println(lux);
}

void loop()
{
  Blynk.run();
  timer.run();
}

#define BLYNK_TEMPLATE_ID           "TMPLcS_h7atA"
#define BLYNK_DEVICE_NAME           "ict device"
#define BLYNK_AUTH_TOKEN            "gngABx23pDiDvurkvO2h77fG_Kt4ZK-z"

#define BLYNK_PRINT Serial

#define DHTTYPE DHT22
#define DHTPIN 4

#define ESP8266_BAUD 9600
#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>
#include <SoftwareSerial.h>
#include "DHT.h"

BlynkTimer timer;
SoftwareSerial EspSerial(2, 3); // RX, TX
 
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "GNB";
char pass[] = "gnb202109";
 
ESP8266 wifi(&EspSerial);

DHT dht(DHTPIN, DHTTYPE);

const int soilSensorPin = A0;

void setup()
{
  Serial.begin(9600);

  EspSerial.begin(ESP8266_BAUD);
  
  Blynk.begin(auth, wifi, ssid, pass);

  dht.begin();

  pinMode(12,OUTPUT);

  timer.setInterval(1000L, myTimerEvent1);
  timer.setInterval(1000L, myTimerEvent2);
  timer.setInterval(1000L, myTimerEvent4);
}

BLYNK_WRITE(V4) {
 int pinValue = param.asInt(); // Assigning incoming value from pin V3 to a variable
 if (pinValue == 1) {
    digitalWrite(12, HIGH); // Turn LED on.
    Serial.println("");
    Serial.println("LED ON");
  } else {
    digitalWrite(12, LOW); // Turn LED off.
    Serial.println("");
    Serial.println("LED OFF");
 }
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

void myTimerEvent4()
{
  Blynk.virtualWrite(V3, analogRead(soilSensorPin));
  Serial.println(analogRead(soilSensorPin));
}

void loop()
{
  Blynk.run();
  timer.run();//setup()에서 등록한 타이머 함수 반복
}

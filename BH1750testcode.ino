#include <Wire.h>
#include <BH1750FVI.h>

/*
ADDR_PIN 을 사용하는 로직
BH1750의 ADDR 핀을 13번에 연결해서 사용하는 방법
uint8_t ADDRESSPIN = 13;
BH1750FVI::eDeviceAddress_t DEVICEADDRESS = BH1750FVI::k_DevAddress_H;
BH1750FVI::eDeviceMode_t DEVICEMODE = BH1750FVI::k_DevModeContHighRes;

// Create the Lightsensor instance
BH1750FVI LightSensor(ADDRESSPIN, DEVICEADDRESS, DEVICEMODE);
*/
/*
동작 모드
      k_DevModeContHighRes     = 0x10 : 1lx 해상도, 측정 시간 : 120ms, 계속 측정
      k_DevModeContHighRes2    = 0x11 : 0.5lx 해상도, 측정 시간 : 120ms, 계속 측정
      k_DevModeContLowRes      = 0x13 : 4lx 해상도, 측정 시간 : 16ms, 계속 측정
      k_DevModeOneTimeHighRes  = 0x20 : 1lx 해상도, 측정 시간 : 120ms, 한번 측정하고 절전모드 진입
      k_DevModeOneTimeHighRes2 = 0x21 : 0.5lx 해상도, 측정 시간 : 120ms, 한번 측정하고 절전모드 진입
      k_DevModeOneTimeLowRes   = 0x23 : 4lx 해상도, 측정 시간 : 16ms, 한번 측정하고 절전모드 진입
*/
BH1750FVI::eDeviceMode_t DEVICEMODE = BH1750FVI::k_DevModeContHighRes;

// BH1750FVI 라이브러리 생성
BH1750FVI LightSensor(DEVICEMODE );

void setup() 
{
  //디버깅용 시리얼 시작
  Serial.begin(115200);
  //빛센서(BH1750) 시작
  LightSensor.begin();  
  Serial.println("Running...");
}

void loop()
{
  //현재 빛량을 가져오기
  uint16_t lux = LightSensor.GetLightIntensity();
  //출력 
  Serial.print("Light: ");
  Serial.println(lux);
  // 0.25초후 대기
  delay(250);
}

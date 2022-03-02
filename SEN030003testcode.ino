const int soilSensorPin = A0; //토양습도센서 아웃을 아두이노 A0로 설정
 
 
void setup()
{
    Serial.begin(9600); //시리얼포트 설정
}
 
void loop()
{
    Serial.println(analogRead(soilSensorPin)); //센서값을 시리얼모니터로 전송
    
    if (analogRead(soilSensorPin) > 780)   // 토양습도 값에 따른 경고음 울리기(자신의 센서 감도에 알맞게 조절필요)
    {                                     
        tone(13,5000,100); // 피에조 ON (주파수 5000으로 0.1초간 울리기)  
    }  
 
    delay(5000);  //반복Term 5초
}

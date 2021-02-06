#include <DS3231.h>

DS3231 clock(SDA, SCL);

int hour, minute;
int ledStart = 21;
int ledStop = 23;

int wLed = 9;
int rbLed = 10;

void wLedStart(){
  int fade = map(minute,0,59,1,255);
  analogWrite(wLed, fade);
}

void wLedStop(){
  int fade = map(minute,0,59,255,0);
  analogWrite(wLed, fade);
}

void setup()
{
  // Serial.begin(115200);
  clock.begin();
  pinMode(wLed, OUTPUT);
  pinMode(rbLed, OUTPUT);  

  // clock.setDOW(FRIDAY);
  // clock.setTime(00, 40, 0);
  // clock.setDate(5, 2, 2021);
}

void loop()
{
  String current_time = clock.getTimeStr();
  hour = current_time.substring(0,2).toInt();
  minute = current_time.substring(3,5).toInt();

  if(hour == ledStart){
    if(minute >= 0 && minute <= 59){
      wLedStart();
    }
    digitalWrite(rbLed, HIGH);
  }
  
  if(hour > ledStart && hour < ledStop - 1){
    digitalWrite(wLed, HIGH);
    digitalWrite(rbLed, HIGH);
  }
  
  if(hour < ledStart || hour > ledStop){
    digitalWrite(wLed, LOW);
    digitalWrite(rbLed, LOW);
  }
  
  if(hour == ledStop - 1){
    if(minute>=0 && minute<=59){
      wLedStop();
    }
  }

  if(hour == ledStop){
    digitalWrite(rbLed, LOW);
  }
}

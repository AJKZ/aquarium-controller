#include <DS3231.h>
#include "custom_pin_defines.h"

DS3231 clock(SDA, SCL);

const int T_HOUR_ON = 12;
const int T_HOUR_OFF = 18;
int hour, minute;

void fadeOn(int pin)
{
  int val = map(minute, 0, 59, 1, 255);
  analogWrite(pin, val);
}

void fadeOff(int pin)
{
  int val = map(minute, 0, 59, 255, 0);
  analogWrite(pin, val);
}

void setup()
{
  // Serial.begin(115200);
  clock.begin();
  pinMode(PIN_LED_CLOSE, OUTPUT);
  pinMode(PIN_LED_MIDDLE, OUTPUT);
  pinMode(PIN_LED_FAR, OUTPUT);
  pinMode(PIN_LED_R, OUTPUT);
  pinMode(PIN_LED_B, OUTPUT);

  // clock.setDOW(FRIDAY);
  // clock.setTime(00, 40, 0);
  // clock.setDate(5, 2, 2021);
}

void loop()
{
  String current_time = clock.getTimeStr();
  hour = current_time.substring(0,2).toInt();
  minute = current_time.substring(3,5).toInt();

  // first hour, fade on
  if(hour == T_HOUR_ON) {
    if(minute >= 0 && minute <= 59){
      fadeOn(PIN_LED_CLOSE);
      fadeOn(PIN_LED_MIDDLE);
      fadeOn(PIN_LED_FAR);
    }
  }
  
  // on
  if(hour > T_HOUR_ON && hour < T_HOUR_OFF - 1) {
    digitalWrite(PIN_LED_CLOSE, HIGH);
    digitalWrite(PIN_LED_MIDDLE, HIGH);
    digitalWrite(PIN_LED_FAR, HIGH);
    digitalWrite(PIN_LED_R, HIGH);
    digitalWrite(PIN_LED_B, HIGH);
  }
  
  // off
  if(hour < T_HOUR_ON || hour > T_HOUR_OFF) {
    digitalWrite(PIN_LED_CLOSE, LOW);
    digitalWrite(PIN_LED_MIDDLE, LOW);
    digitalWrite(PIN_LED_FAR, LOW);
    digitalWrite(PIN_LED_R, LOW);
    digitalWrite(PIN_LED_B, LOW);
  }
  
  // last hour, fade off
  if(hour == T_HOUR_OFF - 1) {
    if(minute >= 0 && minute <= 59) {
      fadeOff(PIN_LED_CLOSE);
      fadeOff(PIN_LED_MIDDLE);
      fadeOff(PIN_LED_FAR);
    }
    digitalWrite(PIN_LED_R, LOW);
    digitalWrite(PIN_LED_B, LOW);
  }
}

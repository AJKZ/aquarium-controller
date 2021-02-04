#include <DS3231.h>

DS3231 clock(SDA, SCL);

int minutes, hours;
int ledStart = 21;
int ledStop = 23;

int wLed = 9;
int rbLed = 10;

void setup()
{
  Serial.begin(115200);
  pinMode(wLed, OUTPUT);
  pinMode(rbLed, OUTPUT);  
  clock.begin();
}

void loop()
{
  String current_time = clock.getTimeStr();
  hours = current_time.substring(0,2).toInt();
  minutes = current_time.substring(3,5).toInt();
  
  Serial.println(current_time);
  delay(1000);
}
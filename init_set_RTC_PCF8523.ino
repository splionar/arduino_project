#include <RTClib.h>
#include <Wire.h>

RTC_PCF8523 rtc;

char buf1[20];

void setup() 
{
  Serial.begin(9600);
  Wire.begin();

  rtc.begin();
  rtc.adjust(DateTime(F(__DATE__),F(__TIME__)));

}

void loop()
{
  DateTime now = rtc.now();

  sprintf(buf1, "%02d/%02d/%02d %02d:%02d:%02d", now.day(), now.month(), now.year(),now.hour(), now.minute(), now.second());  
  
  Serial.print(F("Date/Time: "));
  Serial.println(buf1);

  delay(1000);
}

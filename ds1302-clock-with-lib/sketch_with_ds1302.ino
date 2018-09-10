#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <TimeLib.h>

#include "DS1302.h"

/*
 * CE   = RST
 * i/O  = DAT
 * SCLK = CLK
 */
#define DS1302_RST_PIN 8
#define DS1302_DAT_PIN 7
#define DS1302_CLK_PIN 6

/*
 * lcd i2c
 * sda - A4
 * scl - A5
 */
LiquidCrystal_I2C lcd(0x3F, 16, 2);

DS1302 RTC(DS1302_RST_PIN, DS1302_DAT_PIN, DS1302_CLK_PIN);

String dayAsString(const Time::Day day) {
  switch (day) {
    case Time::kSunday: return "Sun";
    case Time::kMonday: return "Mon";
    case Time::kTuesday: return "Tue";
    case Time::kWednesday: return "Wed";
    case Time::kThursday: return "Thu";
    case Time::kFriday: return "Fri";
    case Time::kSaturday: return "Sat";
  }
  return "---)";
}

void setup()
{
  Serial.begin(9600);
  
  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Clock");

  // Initialize a new chip by turning off write protection and clearing the
  // clock halt flag. These methods needn't always be called. See the DS1302
  // datasheet for details.
  RTC.writeProtect(false);
  RTC.halt(false);

  // Make a new time object to set the date and time.
  // Y, m, d, H, i, s, dow
  // Time t(2018, 8, 25, 17, 35, 00, Time::kSaturday);

  // Set the time and date on the chip.
  // RTC.time(t);
}

void loop()
{
  Time t = RTC.time();
  const String day = dayAsString(t.day);

  // lcd.clear();

  char buf[16];
  snprintf(buf, sizeof(buf), "%02d/%02d/%04d %s", t.date, t.mon, t.yr, day.c_str());

  lcd.setCursor(0, 0);
  lcd.print(buf);

  snprintf(buf, sizeof(buf), "%02d:%02d:%02d", t.hr, t.min, t.sec);

  lcd.setCursor(0, 1);
  lcd.print(buf);

  delay( 1000 );
}


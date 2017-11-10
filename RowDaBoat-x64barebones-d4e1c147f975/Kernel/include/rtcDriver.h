#ifndef RTC_DRIVER_H
#define RTC_DRIVER_H

#define RTC_SECONDS 0X00
#define RTC_MINUTES 0x02
#define RTC_HOURS	0x04
#define RTC_DAY		0x07
#define RTC_MONTH	0x08
#define RTC_YEAR	0x09

unsigned char getSeconds();
unsigned char getMinutes();
unsigned char getHours();
unsigned char getDay();
unsigned char getMonth();
unsigned char getYear();
void displayTime();

#endif
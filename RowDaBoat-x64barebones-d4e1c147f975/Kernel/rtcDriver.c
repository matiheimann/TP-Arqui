#include <textDriver.h>
#include <rtcDriver.h>

#define BCD_TO_BINARY(time) (time & 0x0F) + ((time / 16) * 10)

unsigned char getSeconds() {
	unsigned char seconds = get_rtc_data(RTC_SECONDS);
	seconds = BCD_TO_BINARY(seconds);
	return seconds;
}

unsigned char getMinutes() {
	unsigned char minutes = get_rtc_data(RTC_MINUTES);
   	minutes = BCD_TO_BINARY(minutes);
    return minutes;
}

unsigned char getHours() {
	char hours = get_rtc_data(RTC_HOURS);
	hours = BCD_TO_BINARY(hours)-3;
	if(hours<0)
		hours += 24;

	return hours;
}

unsigned char getDay() {
	unsigned char day = get_rtc_data(RTC_DAY);
	day = BCD_TO_BINARY(day);
	return day;
}

unsigned char getMonth() {
	unsigned char month = get_rtc_data(RTC_MONTH);
	month = BCD_TO_BINARY(month);
	return month;
}

unsigned char getYear() {
	unsigned char year = get_rtc_data(RTC_YEAR);
	year = BCD_TO_BINARY(year);
	return year;
}

unsigned char * dateToString() {
	unsigned char string[6];
	string[0] = getDay();
	string[1] = getMonth();
	string[2] = getYear();
	string[3] = getHours();
	string[4] = getMinutes();
	string[5] = getSeconds();

	return string;
}
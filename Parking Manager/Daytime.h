#pragma once
#define _CRT_SECURE_NO_WARNINGS 1 //this makes C functions warnings disappear
#include <math.h>
#include <time.h>
#include <iostream>
#include <sstream>
using namespace std;

//helper class to make time managment easy
class DayTime
{
private:
	unsigned int hours = 0;
	unsigned int minutes = 0;
	unsigned int seconds = 0;
public:
	DayTime(const unsigned int& hrs, const unsigned int& mins, const unsigned int& secs)
	{
		//modulo values, to make sure that they are not too big, we want to avoid throwing excpetions as much as possible
		hours = hrs % 24;
		minutes = mins % 60;
		seconds = secs % 60;
	}

	DayTime(){}

	int getHours() const { return hours;}
	int getMinutes() const { return minutes; }
	int getSeconds() const { return seconds; }

	void setSeconds(const unsigned int& secs)
	{
		if (secs > 60)
			return;
		seconds = secs; 
	}
	void setMinutes(const unsigned int& mins)
	{ 
		if (mins > 60)
			return;
		minutes = mins; 
	}
	void setHours(const unsigned int& hrs) 
	{ 
		if (hrs > 60)
			return;
		hours = hrs; 
	}

	double getHoursNum() const
	{
		int secs = minutes * 60 + seconds;

		return hours + (secs / 3600.0);
	}

	double getMinutesNum() const
	{
		return hours * 60 + minutes + (seconds / 60.0);
	}

	double getSecondsNum() const
	{
		return hours * 3600 + minutes * 60 + seconds;
	}

	static DayTime now()
	{
		time_t now = time(0);
		tm* local_time = localtime(&now);
		int hour = local_time->tm_hour;
		int minute = local_time->tm_min;
		int second = local_time->tm_sec;

		return DayTime(hour, minute, second);
	}

	DayTime operator-(const DayTime& other)
	{
		int secs = hours * 3600 + minutes * 60 + seconds;
		int other_seconds = other.hours * 3600 + other.minutes * 60 + other.seconds;

		//this way we can make calculations if times are in reverse order (smaller - bigger)
		int time_span = abs(secs - other_seconds);

		int hrs = time_span / 3600;
		time_span -= hrs * 3600;
		int mins = time_span / 60;
		time_span -= mins * 60;
		int sec = time_span;

		return DayTime(hrs, mins, sec);
	}

	DayTime operator+(const DayTime& other)
	{
		int seconds = hours * 3600 + minutes * 60 + seconds;
		int other_seconds = other.hours * 3600 + other.minutes * 60 + other.seconds;
		
		//we do not store days, months, etc, so we modulo that by seconds in the day, this way we do not have to care about it
		int time_span = (seconds + other_seconds) % (24 * 3600);

		int hrs = time_span / 3600;
		time_span -= hrs * 3600;
		int mins = time_span / 60;
		time_span -= mins * 60;
		int secs = time_span;

		return DayTime(hrs, mins, secs);
	}

	//assignment operator
	DayTime& operator=(const DayTime& other)
	{
		hours = other.hours;
		minutes = other.minutes;
		seconds = other.seconds;
	}

	friend ostream& operator<<(ostream& os, const DayTime& dt)
	{
		if(dt.hours < 10)
			os << "0" << dt.hours << ":";
		else
			os << dt.hours << ":";
		if (dt.minutes < 10)
			os << "0" << dt.minutes<<":";
		else
			os << dt.minutes<<":";

		if (dt.seconds < 10)
			os << "0" << dt.seconds;
		else
			os << dt.seconds;

		return os;
	}

	//string that has proper format to save (without :)
	string to_save_string() const
	{
		ostringstream oss{};
		oss << hours << " " << minutes << " " << seconds;

		return oss.str();
	}

	friend istream& operator>>(istream& is, DayTime& dt)
	{
		is >> dt.hours >> dt.minutes >> dt.seconds;
		return is;
	}

};

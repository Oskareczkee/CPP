//Written by Oskar Niedüwiedzki
//Report any bugs :)

/*
If you are struggling with use, here is my testing function

void TimerTest()
{
	CrackTimer Timer;

	Timer.StartTimer();
	Timer.EndTimer();
	double time=Timer.ShowTime(CrackTimer::NANOSECONDS);
	Timer.ZeroTimer();
	cout << "\n";
	cout << time;
	cout << "\n\n" << Timer.ReturnCallendarTimeString();
}
*/

#pragma once
#include <chrono>
#include <ctime>
#include <string>

using namespace std::chrono;
using namespace std;

/// <summary>
/// CrackTimer is easy to use class for measure time and convert it to other units
/// </summary>
class CrackTimer
{
private:
	time_point<high_resolution_clock> Start{}, End{};
	duration<double, seconds::period> ElapsedTime{};
public:
	/// <summary>
	/// Enumerator type for converting seconds to other types
	/// </summary>
	enum class TimeUnit {NANOSECONDS = 0, MICROSECONDS = 1, MILISECONDS = 2, SECONDS = 3, MINUTES = 4, HOURS = 5, DAY=6};

	/// <summary>
	/// Starts Timer
	/// </summary>
	void StartTimer()
	{
		Start = high_resolution_clock::now();
	}

	/// <summary>
	/// Ends Timer
	/// </summary>
	void EndTimer()
	{
		End = high_resolution_clock::now();
	}

	/// <summary>
	/// Shows how much time elapsed between start and end
	/// </summary>
	/// <param name="TimeUnit">In which unit to show the time. Base one is seconds, change it using CrackTimer::(TimeUnit)</param>
	/// <returns>Returns time converted to double</returns>
	double ShowTime(TimeUnit TimeUnit=TimeUnit::SECONDS)
	{
		ElapsedTime = End - Start;
		switch (TimeUnit)
		{
		case TimeUnit::NANOSECONDS:
			return ElapsedTime.count() * 1000000000;
			break;
		case TimeUnit::MICROSECONDS:
			return ElapsedTime.count() * 1000000;
			break;
		case TimeUnit::MILISECONDS:
			return ElapsedTime.count() * 1000;
			break;
		case TimeUnit::SECONDS:
			return ElapsedTime.count();
			break;
		case TimeUnit::MINUTES:
			return ElapsedTime.count()/60;
			break;
		case TimeUnit::HOURS:
			return ElapsedTime.count() / 3600;
			break;
		case TimeUnit::DAY:
			return ElapsedTime.count() / 86400;
			break;

        //if someone entered wrong value, just convert to seconds
		default:
			return ElapsedTime.count();
			break;
		}
	}

	/// <summary>
	/// Sets Start and End to zeroes
	/// </summary>
	void ZeroTimer()
	{
		Start = time_point<high_resolution_clock>();
		End = time_point<high_resolution_clock>();
	}

	/// <summary>
	/// Returns actual time in callendar format of time_t. Requires knowledge of ctime library to use
	/// </summary>
	/// <returns>Returns Callendar time in time_t structure</returns>
	time_t ReturnCallendarTime()
	{
		system_clock::time_point ActualTime = system_clock::now();
		time_t CallendarTime = system_clock::to_time_t(ActualTime);

		return CallendarTime;
	}

	/// <summary>
	/// Returns time_t actual callendar time converted to string. This is usefull for documentation of tests
	/// and does not need to worry about convering time_t to string (ahhh its awfull)
	/// </summary>
	/// <returns>String containing Actual time converted to string</returns>
	string ReturnCallendarTimeString()
	{
		system_clock::time_point ActualTime = system_clock::now();
		time_t CallendarTime = system_clock::to_time_t(ActualTime);

		try
		{
			//minimal size of buffer is 26, but i made it bigger, just for sure
			char TimeBuffer[30];
			auto errno_t = ctime_s(TimeBuffer, sizeof(TimeBuffer), &CallendarTime);
			string output = TimeBuffer;
			return output;
		}
		catch (exception ex)
		{
			string exception = ex.what();
			return exception;
		}
        
	}
};


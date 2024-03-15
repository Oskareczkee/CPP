#pragma once
#include <time.h>
#include <iostream>

struct Candle
{
	tm date{ 0 };
	double open = 0.0, high = 0.0, low = 0.0, close = 0.0;

	friend std::ostream& operator<<(std::ostream& os, const Candle& c)
	{
		if (!os)
			return os;

		char date_buffer[50];
		strftime(date_buffer, sizeof(date_buffer),"%Y-%m-%d", &c.date);
		os << "[" << date_buffer << "] " << c.open << " " << c.high << " " << c.low << " " << c.close << "\n";

		return os;
	}
};

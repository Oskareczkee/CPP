#pragma once
#include <iostream>

class Candle
{
public:
	double open, close,high, low;
	tm date;
	Candle(const double& _open, const double& _close, const double& _high, const double& _low) :
		open(_open), close(_close), high(_high), low(_low), date({0}) {}
	Candle():open(0.0), close(0.0),high(0.0),low(0.0), date({0}) {}

	friend std::ostream& operator<<(std::ostream& os, const Candle& c)
	{
		if (!os)
			return os;

		char timebuf[40];//buffer to convert time to string
		strftime(timebuf, sizeof(timebuf), "%Y/%m/%d", &c.date);

		os << "[ " << timebuf << " ] "
			<< "Open[" << c.open << "] High[" << c.high << "] Low[" << c.low << "] Close[" << c.close << "]\n";

		return os;
	}
};
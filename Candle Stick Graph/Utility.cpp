#include "Utility.h"

const char* GroupToString(const GraphGrouping& g)
{
	switch (g)
	{
	case GraphGrouping::DAY:
		return "Day";
	case GraphGrouping::WEEK:
		return "Week";
	case GraphGrouping::MONTH:
		return "Month";
	default:
		return "";
	}
}

tm make_time()
{
	const time_t t = time(0);
	tm output{ 0 };
	localtime_s(&output, &t);
	return output;
}

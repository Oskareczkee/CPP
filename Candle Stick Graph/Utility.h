#pragma once
#include <time.h>
enum class GraphGrouping
{
	DAY = 1,
	WEEK = 5,
	MONTH = 20
};
const char* GroupToString(const GraphGrouping& g);
tm make_time();
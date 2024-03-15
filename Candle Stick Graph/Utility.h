#pragma once
#include <time.h>

enum class CSGGrouping
{
	Day = 1,
	Week = 5,
	Month = 20
};

//converts given group to its string representation
//this function is static, otherwise some linker errors occurs
static const char* group_to_string(const CSGGrouping& group)
{
	switch (group)
	{
	case CSGGrouping::Day:   return "Day";
	case CSGGrouping::Week:  return "Week";
	case CSGGrouping::Month: return "Month";
	default:                 return "";
	}
}


/// <summary>
/// checks if date 1 is greater or equal to date 2
/// </summary>
/// <returns>true if t1 &gt;= t2, otherwise false </returns>
static bool time_greater_equal(tm& t1, tm& t2)
{
	long long ts1 = mktime(&t1);
	long long ts2 = mktime(&t2);

	return ts1 >= ts2;
}

/// <summary>
/// checks if date 1 is less or equal to date 2
/// </summary>
/// <returns>true if t1 &lt;= t2, otherwise false </returns>
static bool time_less_equal(tm& t1, tm& t2)
{
	long long ts1 = mktime(&t1);
	long long ts2 = mktime(&t2);

	return ts1 <= ts2;
}
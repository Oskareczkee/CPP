#pragma once
#include "Candle.h"
#include <time.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <math.h>
#include "Utility.h"

using namespace std;

class CSG
{
private:
	static const int BUFFER_SIZE = 50; //buffer size used for strings, change it if too small

	Candle* candles = nullptr; //all candles
	Candle* candles_grouped = nullptr; //grouped candles, managed by GroupCandles function
	int candle_count = 0;
	int candle_grouped_size = 0;
	int candle_grouped_max_size = -1; //max size of group, if < 0  there is no limit, used in generating slice of graph
	int candle_buffer_size = 10000; //max number of candles that can be stored

	const int padding_left = 10; //we need some additional space for y axis and values
	const int padding_bottom = 10; //space for x axis

	void Candles_Init();
	void Candles_Delete();
	void CandlesGrouped_Init();
	void CandlesGrouped_Delete();
	/// <summary>
	/// Returns array of candles grouped by actual grouping
	/// Sets size to array size
	/// </summary>
	void GroupCandles();
	/// <summary>
	/// Creates string representation of candle, buffer should be size of _width
	/// </summary>
	char* CreateCandleString(char* buffer, const int& size,const Candle& c);

	int _width = 0 + padding_left;
	int _height = 100 + padding_bottom;
	GraphGrouping grouping = GraphGrouping::DAY;

	tm time_begin = make_time(); //check Utility.cpp
	tm time_end = make_time(); //check Utility.cpp
	tm graph_time_begin = make_time(); //original value from which data begun
	tm graph_time_end = make_time(); //original value at which data end

	double unit_val = 0.0; //value of 1 unit on graph
	double value_min = 0; //min value on graph
	double value_max = 0; //max value on graph
	double value_range = 0.0; //range of values |min-max|

	//framebuffer used to draw graph to file, it is cleared every time and initialized every time graph is being drawn
	char** framebuffer = nullptr;
	void FramebufferInit();
	void FramebufferDelete();
	/// <summary>
	/// Draws given string reversed in the framebuffer
	/// </summary>
	void FramebufferDrawReversed(char* to_draw,const int& x_pos, const int& y_pos);
	void FramebufferDrawAxis(const char* x_axis_name, const char* y_axis_name);
	void FramebufferDrawGraph();
public:
	CSG() { Candles_Init(); FramebufferInit(); }
	CSG(const int& width, const int& height) :_width(width), _height(height) { Candles_Init(); FramebufferInit(); }
	~CSG() { Candles_Delete(); FramebufferDelete(); }
	void LoadFromFile(const char* filename);
	void SaveToFile(const char* filename);
	/// <summary>
	/// Draws a slice of graph in console
	/// </summary>
	void DrawSlice(const int& height, const int& width, const tm& begin, const tm& end, const GraphGrouping& grouping = GraphGrouping::DAY);

	int GetTotalWidth() { return _width; }
	int GetTotalHeight() { return _height; }
	int GetGraphWidth() { return _width - padding_left; }
	int GetGraphHeight() { return _height - padding_bottom; }
	int GetCandleCount() { return candle_count; }
	GraphGrouping GetGrouping() { return grouping; }
	tm GetTimeBegin() { return time_begin; }
	tm GetTimeEnd() { return time_end; }

	void SetWidth(const int& width);
	void SetHeight(const int& height);
	void SetGrouping(const GraphGrouping& group) { grouping = group; }
	void SetTimeBegin(const tm& time) { time_begin = time; }
	void SetTimeEnd(const tm& time) { time_end = time; }




	void print_candles()
	{
		for (int x = 0; x < candle_count; x++)
			cout << candles[x];
	}
};


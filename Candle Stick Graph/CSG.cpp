#include "CSG.h"

void CSG::Candles_Init()
{
	if (candles)
		Candles_Delete();

	candles = new Candle[candle_buffer_size];
	candle_count = 0;
}

void CSG::Candles_Delete()
{
	delete[] candles;
	candles = nullptr;
}

void CSG::CandlesGrouped_Init()
{
	if (candles_grouped)
		CandlesGrouped_Delete();

	candles_grouped = new Candle[candle_buffer_size];
	candle_grouped_size = 0;
}

void CSG::CandlesGrouped_Delete()
{
	delete[] candles_grouped;
	candles_grouped = nullptr;
}

void CSG::GroupCandles()
{
	int range_iter = 0;

	double range_highmax = INT_MIN;
	double range_lowmin = INT_MAX;
	//global
	double highmax = INT_MIN;
	double lowmin = INT_MAX;

	const int time_range_begin = mktime(&time_begin);
	const int time_range_end = mktime(&time_end);

	int curr_size = 0;
	CandlesGrouped_Init();
	int candles_iter = 0;
	Candle current;

	for (int x = 0; x < candle_count; x++)
	{
		//check if we do not have max_size, if max_size < 0, there is no limit
		if (candle_grouped_max_size > 0 && curr_size >= candle_grouped_max_size)
			break;

		int time = mktime(&candles[x].date);
		//check if time is in range, if not - skip it
		if (time < time_range_begin)
			continue;
		else if (time > time_range_end)//when we get to the range end, there is no need for further processing
			break;

		range_iter++;

		if (candles[x].high > range_highmax)
			range_highmax = candles[x].high;
		if (candles[x].low < range_lowmin)
			range_lowmin = candles[x].low;

		current.open += candles[x].open;
		current.close += candles[x].close;

		if (range_iter >= (int)grouping)
		{
			range_iter = 0;
			curr_size++;
			current.high = range_highmax;
			current.low = range_lowmin;
			current.date = candles[x].date;
			candles_grouped[candles_iter++] = current;

			//set global lowmin and highmax for proper generation
			if (current.low < lowmin)
				lowmin = current.low;

			if (current.high > highmax)
				highmax = current.high;

			current = Candle();

			range_highmax = INT_MIN;
			range_lowmin = INT_MAX;
			continue;
		}

	}

	value_min = lowmin;
	value_max = highmax;
	value_range = abs(lowmin - highmax);
	unit_val = value_range / GetGraphHeight();
	candle_grouped_size = curr_size;
}

char* CSG::CreateCandleString(char* buffer, const int& size, const Candle& c)
{
	bool rise = c.open < c.close;
	double body_val = abs(c.open - c.close);
	double close_avg = c.close / (int)grouping;
	double open_avg = c.open / (int)grouping;

	int upper_shadow_count = (rise ? c.high - close_avg : c.high - open_avg) / unit_val;
	int lower_shadow_count = (rise ? open_avg - c.low : close_avg - c.low) / unit_val;
	int body_count = abs(c.open - c.close) / unit_val;
	int buffer_index = 0;

	for (int x = 0; x < upper_shadow_count; x++)
		buffer[buffer_index++] = '|';
	for (int x = 0; x < body_count; x++)
		buffer[buffer_index++] = (rise ? 'O' : '#');
	for (int x = 0; x < lower_shadow_count; x++)
		buffer[buffer_index++] = '|';

	buffer[buffer_index] = '\0';//add terminating character at the end

	return buffer;
}

void CSG::FramebufferInit()
{
	framebuffer = new char* [_height];
	for (int x = 0; x < _height; x++)
		framebuffer[x] = new char[_width];

	//init buffer with spaces
	for (int x = 0; x < _height; x++)
		for (int y = 0; y < _width; y++)
			framebuffer[x][y] = ' ';
}

void CSG::FramebufferDelete()
{
	if (!framebuffer) //if buffer is not initialized, do not delete it
		return;

	for (int x = 0; x < _height; x++)
		delete[] framebuffer[x];

	delete[] framebuffer;
	framebuffer = nullptr;
}

void CSG::FramebufferDrawReversed(char* to_draw, const int& x_pos, const int& y_pos)
{
	for (int x = 0; to_draw[x] != '\0'; x++)
	{
		if (x + y_pos >= GetGraphHeight()) //prevent overflow, sometimes this happen due rounding errors
			break;
		framebuffer[x + y_pos][x_pos] = to_draw[x];
	}
}

void CSG::FramebufferDrawAxis(const char* x_axis_name, const char* y_axis_name)
{
	//y axis
	for (int x = 1; x < GetGraphHeight(); x++)
		framebuffer[x][padding_left] = '|';
	//x axis
	for (int x = padding_left + 1; x < _width-1; x++)
		framebuffer[GetGraphHeight()][x] = '-';

	//adding names
	for (int x = 0; x_axis_name[x] != '\0'; x++)
		framebuffer[GetGraphHeight() + 1][padding_left+ 2 + x] = x_axis_name[x];
	for (int x = 0; y_axis_name[x] != '\0'; x++)
		framebuffer[GetGraphHeight()- 2 - x][padding_left - 1] = y_axis_name[x]; //draw y_axis name horizontally

	char num_buf[10];
	int slen = 0; //string length

	//y_axis values, drawn every 5 tiles
	for (int x = 0; x < GetGraphHeight(); x+=5)
	{
		_gcvt_s(num_buf, sizeof(num_buf), value_min + (x * unit_val), 6); // gcvt - converts double to string in a C way
		slen = strlen(num_buf);
		for (int y = 0; num_buf[y] != '\0'; y++)
			framebuffer[GetGraphHeight() - x][padding_left - 2 - (slen - y)] = num_buf[y];
		framebuffer[GetGraphHeight() - x][padding_left] = '-';
	}

	//x_axis
	char date_buf[15];

	//x_axis values, drawn every 15 tiles
	for (int x = 0; x < GetGraphWidth()-15; x += 15)
	{
		strftime(date_buf, sizeof(date_buf), "%Y.%m.%d", &candles_grouped[x].date);
		slen = strlen(date_buf);
		for (int y = 0; date_buf[y] != '\0'; y++)
			framebuffer[GetGraphHeight() + 4][padding_left + x + y] = date_buf[y];

		framebuffer[GetGraphHeight()][padding_left + x + (slen / 2)] = '|';
	}

	//details
	framebuffer[0][padding_left] = '^';
	framebuffer[GetGraphHeight()][_width-1] = '>';
	framebuffer[GetGraphHeight()][padding_left] = '+';
}

void CSG::FramebufferDrawGraph()
{
	char* buffer = new char[GetGraphHeight()];
	GroupCandles();
	SetWidth(candle_grouped_size);
	FramebufferInit();

	//start from x = padding_left, on the left side is y_axis
	for (int x = padding_left; x < candle_grouped_size; x++)
	{
		int y_pos = (value_max - candles_grouped[x].high) / unit_val;
		CreateCandleString(buffer, sizeof(buffer), candles_grouped[x]);
		FramebufferDrawReversed(buffer, x, y_pos);
	}

	FramebufferDrawAxis("date", "value");

	delete[] buffer;
}

void CSG::LoadFromFile(const char* filename)
{
	//make candle buffer ready to go
	Candles_Delete();
	Candles_Init();

	ifstream file{ filename };

	if (!file)
	{
		cout << "File does not exist!\nData has not been loaded\n";
		return;
	}

	char buffer[BUFFER_SIZE];
	Candle current;

	//skip first line as it does not contain anything usefull
	file.getline(buffer, BUFFER_SIZE, '\n');
	while (file)
	{
		file >> get_time(&current.date, "%Y-%m-%d");
		//skip delimeter
		file.get();
		file >> current.open;
		file.get();
		file >> current.high;
		file.get();
		file >> current.low;
		file.get();
		file >> current.close;

		//skip last value, it is not used
		file.getline(buffer, BUFFER_SIZE, '\n');

		candles[candle_count++] = current;
	}

	time_begin = candles[0].date;
	time_end = candles[candle_count - 1].date;
}

void CSG::SaveToFile(const char* filename)
{

	ofstream file{ filename };

	if (!file)
	{
		cout << "File could not be created or opened!\n";
		return;
	}

	FramebufferDrawGraph();

	//write framebuffer to the file
	for (int x = 0; x < _height; x++)
	{
		for (int y = 0; y < _width; y++)
			file << framebuffer[x][y];
		file << "\n";
	}
}

void CSG::DrawSlice(const int& height,const int& width, const tm& begin, const tm& end, const GraphGrouping& group)
{
	tm begin_copy, end_copy;
	GraphGrouping grouping_copy;
	int height_copy;
	//make copies of actual values
	begin_copy = time_begin; end_copy = time_end; grouping_copy = grouping; 
	height_copy = _height;

	//clear buffer before drawing
	FramebufferDelete();

	//set temp values
	time_begin = begin; time_end = end; grouping = group;
	candle_grouped_max_size = width; //limit group max size
	SetHeight(height);

	FramebufferDrawGraph();//draw graph with temp values

	//draw it
	for (int x = 0; x < _height; x++)
	{
		for (int y = 0; y < _width; y++)
			cout << framebuffer[x][y];
		cout << "\n";
	}

	//clear buffer after drawing
	FramebufferDelete();

	//set values to the previous ones
	time_begin = begin_copy; time_end = end_copy; grouping = grouping_copy; 
	_height = height_copy;
	candle_grouped_max_size = -1;//delete the limit
}

void CSG::SetWidth(const int& width)
{
	if (width <= 0)
		return;
	_width = width + padding_left;
}

void CSG::SetHeight(const int& height)
{
	if (height <= 0)
		return;
	FramebufferDelete();
	_height = height + padding_bottom;
	FramebufferInit();
}

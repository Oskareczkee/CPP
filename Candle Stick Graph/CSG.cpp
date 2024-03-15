#pragma once
#include "CSG.h"

void CSG::init_buffer()
{
	for (int x = 0; x < _height; x++)
		for (int y = 0; y < _width; y++)
			framebuffer[x][y] = ' ';
}

void CSG::delete_buffer()
{
	for (int x = 0; x < _height; x++)
		delete[] framebuffer[x];
	delete[] framebuffer;

	framebuffer = nullptr;
}

void CSG::create_buffer()
{
	//framebuffer is not clear
	if (framebuffer)
		delete_buffer();

	framebuffer = new char*[_height];
	for (int x = 0; x < _height; x++)
		framebuffer[x] = new char[_width];
}

char* CSG::generate_candle(const Candle& c, char* buffer, int& ypos, int& nexty)
{
	int iter = 0;//buffer iterator
	int high_len = c.high / shadow_val;
	int low_len = c.low / shadow_val;
	int body_len = abs(c.open - c.close) / body_val;
	bool rise = c.open - c.close < 0;

	for (int x = 0; x < high_len; x++)
		buffer[iter++] = '|';
	for (int x = 0; x < body_len; x++)
		buffer[iter++] = (rise ? 'O' : '#');
	for (int x = 0; x < low_len; x++)
		buffer[iter++] = '|';

	nexty += (rise ? 0 : body_len - 1);

	if (nexty < 0) nexty = 0;
	else if (nexty > _height) nexty = _height - 1;

	ypos -= high_len;
	if (ypos < 0) ypos = 0;
	else if (ypos > _height) ypos = _height-1;

	buffer[iter] = '\0';//add terminator at the end of the string
	return buffer;
}

void CSG::buffer_draw_reverse(const char* s, const int& x_pos, const int& y_pos)
{
	for (int y = 0; s[y] != '\0'; y++)
	{
		if (y_pos + y >= _height)
			break;
		framebuffer[y_pos + y][x_pos] = s[y];
	}
}

CSG::CSG()
{
	framebuffer = new char*[_height];
	for (int x = 0; x < _height; x++)
		framebuffer[x] = new char[_width];

	_candles = new Candle[_width];

	init_buffer();
}

CSG::CSG(const int& width, const int& height) : _width(width), _height(height)
{
	framebuffer = new char* [height];
	for (int x = 0; x < height; x++)
		framebuffer[x] = new char[width];

	init_buffer();
}

CSG::~CSG()
{
	delete_buffer();
	delete[] _candles;
}

void CSG::load_from_file(const char* filename)
{
	std::ifstream file{ filename };

	if (!file)
		throw std::exception("File does not exist");

	//skip first line
	char dummy[BUFFER_SIZE];
	file.getline(dummy, sizeof(dummy), '\n');

	//used for scaling the graph
	double highmax = 0;
	double lowmin = INT_MAX;
	double openclosemax = 0;
	double openclosemin = 0;

	//grouping
	int group_size = (int)_grouping;
	int group_iter = 0;

	Candle candle;
	Candle group_candle;
	int iter = 0;
	_candle_count = 0;


	while (file && iter < _width)
	{
		char data[BUFFER_SIZE];
		char date[BUFFER_SIZE];

		file.getline(date, sizeof(date), ',');
		std::istringstream iss(date);
		iss >> std::get_time(&candle.date, "%Y-%m-%d");

		//checks whether given record is in proper time range, othwerwise skips it
		//if (!time_greater_equal(candle.date, time_range_begin) || !time_less_equal(candle.date, time_range_end))
			//continue;


		//open
		file.getline(data, sizeof(data), ',');
		candle.open = strtod(data,NULL);

		//high
		file.getline(data, sizeof(data), ',');
		candle.high = strtod(data, NULL);

		//low
		file.getline(data, sizeof(data), ',');
		candle.low = strtod(data, NULL);

		//close
		file.getline(data, sizeof(data), ',');
		candle.close=strtod(data, NULL);
		//skip volume
		file.getline(data, sizeof(data));

		//grouping things
		if (candle.high > group_candle.high)
			group_candle.high = candle.high;
		if (candle.low > group_candle.low)
			group_candle.low = candle.low;
		group_candle.close += candle.close;
		group_candle.open += candle.open;
		group_iter++;

		if (group_iter >= group_size)
		{
			_candles[_candle_count++]=group_candle;

			if (highmax < group_candle.high)
				highmax = group_candle.high;
			if (lowmin > group_candle.low)
				lowmin = group_candle.low;

			double openclose = group_candle.open - group_candle.close;
			if (openclose > openclosemax)
				openclosemax = openclose;
			if (openclose < openclosemin)
				openclosemin = openclose;

			iter++;
			group_candle = Candle(); //reset group candle
			group_iter = 0;
		}

	}

	shadow_val = abs(highmax - lowmin)/10;
	body_val = abs(highmax-lowmin)/100;
	//set proper width for framebuffer
	_width = _candle_count;
}

void CSG::load_from_stream(std::istream& stream)
{
}

void CSG::generate_chart(const char* outfile)
{

	//init new buffer for drawing
	delete_buffer();
	create_buffer();
	init_buffer();

	int ypos = _height/2;
	int nexty = _height/2;
	int xpos = 0;

	for (int x = 0; x < _candle_count; x++) {
		char buffer[BUFFER_SIZE];
		buffer_draw_reverse(generate_candle(_candles[x], buffer,ypos, nexty), xpos++, ypos);
		ypos = nexty;
	}

	std::ofstream of{ outfile };
	
	for (int x = 0; x < _height; x++)
	{
		for (int y = 0; y < _width; y++)
			of << framebuffer[x][y];
		of << "\n";
	}
}

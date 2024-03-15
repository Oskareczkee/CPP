#pragma once
#include <iomanip>
#include <fstream>
#include <sstream>
#include "Candle.h"
#include "Utility.h"

class CSG
{
private:
	static const int BUFFER_SIZE = 1000; //string buffer size used in program, change it if program crashes
									   //static is used, to make it compile time constant
	//scaling factors, shadow_val and body_val is set when loading
	double shadow_val = 10.0;
	double body_val = .5;
	double scale = 1;

	int _height = 1000;
	int _width = 7000;

	CSGGrouping _grouping = CSGGrouping::Day;

	int _candle_count = 0;
	Candle* _candles;
	
	//time range
	tm time_range_begin;
	tm time_range_end;


	char** framebuffer;

	//inits buffer with spaces
	void init_buffer();
	//deletes buffer
	void delete_buffer();
	//creates new buffer with _height and _width;
	void create_buffer();

	/*generates candle, saves it to the buffer, returns pointer to the buffer, generated string is proper C string with '\0'
	* ypos - used for drawing, pass it to calculate y coordinate to draw from
	* nexty - used for drawing, pass it to receive next y coordinate that will be used for drawing
	*/
	char* generate_candle(const Candle& c, char* buffer, int& ypos, int& nexty);
	//draws string reversed in the buffer
	void buffer_draw_reverse(const char* s, const int& x_pos, const int& y_pos);
public:
	CSG();
	CSG(const int& width, const int& height);
	~CSG();

	//loads from file, sets proper scaling factors
	void load_from_file(const char* filename);
	void load_from_stream(std::istream& stream);
	void generate_chart(const char* outfile);

	void change_scale(const int& new_scale) { scale = new_scale; }
	int get_candle_count() { return _candle_count; }
	double get_scale() { return scale; }
	int get_height() { return _height; }
	void set_height(const int& height) { _height = height; }
	int get_width() { return _width; }
	CSGGrouping get_grouping() { return _grouping; }
	void set_grouping(const CSGGrouping& grouping) { _grouping = grouping; }

	void printCandles()
	{
		for (int x=0;x<_candle_count;x++)
			std::cout << _candles[x];
	}
};

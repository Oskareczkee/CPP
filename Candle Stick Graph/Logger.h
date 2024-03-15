#pragma once
#include <string.h>
#include <fstream>
#include <time.h>
#include <iomanip>

using namespace std;

class Logger
{
private:
	const int outfile_max_len = 50;
	char* outfile;
public:
	Logger();
	Logger(const char* out);
	~Logger();
	void WriteLine(const char* log);
	void SetOutput(const char* filename);
};
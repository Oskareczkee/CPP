#include "Logger.h"

void Logger::WriteLine(const char* log)
{
	ofstream file{ outfile, ios::app };

	if (!file)//do not throw any exceptions for now
		return;

	char time_buffer[100];
	tm actual_time;
	time_t time_now = time(0);

	localtime_s(&actual_time, &time_now);
	file << put_time(&actual_time, "[%Y-%m-%d %T]");
	file <<"  "<< log << "\n";
}

Logger::Logger()
{
	outfile = new char[outfile_max_len];
	strcpy_s(outfile, outfile_max_len, "log.log");
}

Logger::Logger(const char* out)
{
	outfile = new char[outfile_max_len];
	strcpy_s(outfile, outfile_max_len, out);
}

Logger::~Logger()
{
	delete[] outfile;
}

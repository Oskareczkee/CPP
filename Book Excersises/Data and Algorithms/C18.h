#pragma once
#include <string>
#include <sstream>
using namespace std;

namespace Cfunc
{

char* strdup(const char* string)
{
	int size = strlen(string);
	char* output = new char[size+1];
	char* p=output;

	while (*string)
	{
		*output++ = *string++;
	}

	*output = '\0';
	
	return p;
}

int strcmp(const char* s1, const char* s2)
{
	while (*s1 && *s2)
	{
		if (*s1 < *s2)
			return -1;
		if (*s1 > *s2)
			return 1;

		s1++;
		s2++;
	}

	int s1len = strlen(s1);
	int s2len = strlen(s2);
	if (s1len == s2len)
		return 0;
	else if (s1len > s2len)
		return 1;
	return -1;
}

char* cat_dot(const char* s1, const char* s2, const char* sep=".")
{
	int s1len = strlen(s1);
	int s2len = strlen(s2);
	int seplen = strlen(sep);

	int length = s1len + s2len + seplen;

	char* output = new char[length + 1];
	char* p = output;

	while (*s1)
		*output++ = *s1++;
	while(*sep)
		*output++ = *sep++;
	while (*s2)
		*output++ = *s2++;

	*output = '\0';
	return p;
}

}

string cat_dot(const string& s1, const string& s2, const string& sep=".")
{
	ostringstream ss{ string() };
	ss << s1 << sep << s2;
	return ss.str();
}

bool is_palindrome(const char s[])
{
	int first = 0;
	int last = strlen(s)-1;

	while (first < last)
	{
		if (s[first] != s[last])
			return false;
		++first;
		--last;
	}

	return true;
}
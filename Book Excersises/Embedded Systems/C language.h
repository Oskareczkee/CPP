#pragma once
#include <stdlib.h>
#include <stdio.h>

extern "C" void HelloWorld()
{
	const char* hello = "Hello";
	const char* world = "World";
	printf("%s %s", hello, world);
}

extern "C" void func(const char* p, int x)
{
	printf("%s, %d", p, x);
}

extern "C" int my_strlen(const char* str)
{
	int len=0;
	while (*str++ != '\0')
		len++;
	return len;
}

extern "C" int my_strcmp(const char* str1, const char* str2)
{
	while (*str1!= '\0' && *str2!= '\0')
	{
		if (*str1 > *str2)
			return 1;
		else if (*str1 < *str2)
			return -1;
		str1++;
		str2++;
	}
	if (my_strlen(str1) > my_strlen(str2))
		return 1;
	else if (my_strlen(str1) < my_strlen(str2))
		return -1;
	return 0;
}

extern "C" char* my_strcpy(char* p, const char* q)
{
	while (*p++ = *q++){}
	return p;
}


//8
void lexicographic_order_check()
{
	char x = 0;
	while (x >= 0)
	{
		printf("%d: %c\n",x,x);
		x++;
	}
}


int ascending(void const* a, void const* b)
{
	return (*(char*)a - *(char*)b);
}

//9
void number_nine()
{
	char buffer[100];
	gets_s(buffer, 100);
	int len = strlen(buffer);
	qsort(buffer, len, sizeof(char), ascending);
	fprintf(stdout, buffer);
}

struct result
{
	int min, max;
	float average, median;
};

int int_cmp(void const* a, void const* b)
{
	return (*(int*)a > *(int*)b) - (*(int*)a < *(int*)b);
}

struct result get_results(int* table, int table_size)
{
	struct result output;

	qsort(table, table_size, sizeof(int), int_cmp);

	output.min = table[0];
	output.max = table[table_size - 1];

	int sum = 0;
	int x = 0;

	for (; x < table_size; x++)
		sum += table[x];

	output.average = sum / table_size;

	if ((table_size % 2) == 0)
		output.median = (table[(table_size - 1) / 2] + table[table_size / 2]) / 2.0;
	else
		output.median = table[table_size / 2];

	return output;
}
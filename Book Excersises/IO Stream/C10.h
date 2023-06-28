#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <string>

using namespace std;


struct Reading
{
	int hour;
	double temp;
};

void Print_Vector(const vector<Reading>& readings);
void concatenate_files(const string& file1, const string& file2, const string& output_name);
vector<int> find_numbers_in_file(const string& fileName);

void NumeroUno();
void Create_Readings();
vector<Reading>Load_Readings(const string& fileName);

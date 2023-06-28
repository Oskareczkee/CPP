#pragma once
#include "C10.h"
//There is no temperature store program, bcs i am pretty lazy and didn't want to rewrite code, didn't find raw version on the net


//operator for reading
istream& operator>>(istream& is, Reading& r)
{
	int h;
	double t;

	is >> h >> t;

	if (!is) return is;

	r = Reading{ h, t };

	return is;
}

ostream& operator<<(ostream& os, const Reading& r)
{
	return os << r.hour << " " << r.temp << "\n";
}

void NumeroUno()
{
	const string txtName = "NumeroUno.txt";

	ifstream ifs{ txtName };

	if (!ifs) throw exception("Cannot open file !");

	ifs.exceptions(ifs.exceptions() | ios_base::badbit);
	vector<int> numbers;
	int number = 0;

	//load till eof
	while (ifs >> number)
	{

		//propably format error occured
		if (ifs.fail())
		{
			//clear the state
			ifs.clear();

			char c;
			ifs >> c;
			//check if c is digit format (no terminating chars in this excersise)
			//tbh i don't have to check if c is digit, if ifs cant load number, then it has to be 100% wrong format
			//providing i will only load number (what i do in this exercise)
			if (!isdigit(c))
			{
				//format error, return char to stream, and set the state to fail
				ifs.unget();
				ifs.clear(ios_base::failbit);
			}
		}

		numbers.push_back(number);
	}

	int sum = 0;

	for (int i : numbers)
		sum += i;

	cout << "The sum of numbers in file is: " << sum << "\n";
}

int GenerateRandomInt(int left, int right)
{
	static random_device rd;
	static mt19937 mt(rd());
	uniform_real_distribution<double> dist(left, right);

	//generates double, safely casts it to int
	return { static_cast<int>(dist(mt)) };
}

void Create_Readings()
{
	string name;

	cout << "Write the name of readings file to create to: ";
	cin >> name;

	ofstream ofs{ name };

	if (!ofs) throw exception("Couldn't create readings file !");

	for (int x = 0; x < 50; x++)
	{
		ofs << GenerateRandomInt(1, 24) << " " << GenerateRandomInt(0, 32)<<"\n";
	}
}

vector<Reading> Load_Readings(const string& fileName)
{
	ifstream ifs{ fileName };
	ifs.exceptions(ifs.exceptions() | ios_base::badbit);

	if (!ifs) throw exception("Couldn't open file !");

	vector<Reading> output;
	Reading reading;

	while (ifs >> reading)
	{
		//wrong format
		//if fails, return failbit
		if (ifs.fail())
			ifs.clear(ios_base::failbit);
		output.push_back(reading);
	}
	return output;
}

void Print_Vector(const vector<Reading>& readings)
{
	for (auto& i : readings)
		cout << i;
}

void concatenate_files(const string& file1, const string& file2, const string& output_name)
{
	ifstream ifs1{ file1 };
	if (!ifs1) throw exception("Couldn't open file 1");
	ifstream ifs2{ file2 };
	if (!ifs2) throw exception("Couldn't open file 2");

	ifs1.exceptions(ifs1.exceptions() | ios_base::badbit);
	ifs2.exceptions(ifs2.exceptions() | ios_base::badbit);


	ofstream ofs{ output_name };
	if (!ofs) throw exception("Couldn't open/create output file");

	ofs.exceptions(ofs.exceptions() | ios_base::badbit);

	string temp;
	while (ifs1 >> temp)
	{
		if (ifs1.fail())
			ifs1.clear(ios_base::failbit);

		ofs << temp;

		if (ofs.fail())
			ofs.clear(ios_base::failbit);
	}

	temp = "";

	while (ifs2 >> temp)
	{
		if (ifs2.fail())
			ifs2.clear(ios_base::failbit);

		ofs << temp;

		if (ofs.fail())
			ofs.clear(ios_base::failbit);
	}
}

vector<int> find_numbers_in_file(const string& fileName)
{
	ifstream ifs{ fileName };
	if (!ifs) throw exception("Couldn't open file !");

	ifs.exceptions(ifs.exceptions() | ios_base::badbit);

	string temp;
	vector<int> numbers;

	while (ifs >> temp)
	{
		if (ifs.fail())
			ifs.clear(ios::failbit);

		try
		{
		int num = stoi(temp);
		numbers.push_back(num);
		}
		catch(...){}


	}

	return numbers;
}



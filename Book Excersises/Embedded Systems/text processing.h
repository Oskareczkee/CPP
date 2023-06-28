#pragma once
#include <regex>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

//5 find a way to test multimap and unordered_multimap containers


//12
//expected date format: mm/dd/rrrr
//separator doesn't matter
string changeToISO(const string& date)
{
	istringstream iss{ date };

	char separator = date[2];

	string year, month, day;

	getline(iss, month, separator);
	getline(iss, day, separator);
	getline(iss, year, separator);

	ostringstream output{ string() };
	output << year << "-" << month << "-" << day;

	return output.str();
}

//6

//format ISO rrrr-mm-dd
//			 mm-dd-rrrr
//			 rrrr/mm/dd
//			 mm/dd/rrrr
void findDates(istream& fileS = cin/*regex format*/)
{
	regex dateFormat{ R"(\d{2}(/|-| )?\d{2}(/|-| )?\d{4})" };

	string temp;
	while (getline(fileS, temp, '\n'))
	{
		smatch matches;
		if (regex_search(temp, matches, dateFormat))
			cout << changeToISO(matches[0]) << "\n";
	}
}


//7
void findCreditCardNumbers(istream& fileS = cin)
{
	regex cardFormat{ R"(\d{12,19})" };

	string temp;
	while (getline(fileS, temp, '\n'))
	{
		smatch matches;
		if (regex_search(temp, matches, cardFormat))
			cout << matches[0] << "\n";
	}
}

//8
void NumberEight()
{
	string fileName, pattern;

	cout << "Please give file name to read from\n";
	getline(cin, fileName, '\n');
	ifstream ifs{fileName};
	if (!ifs)
		throw exception("file not found !");

	cout << "Please write regex pattern to find in file\n";
	cin >> pattern;


	try
	{
		regex pat{ pattern };
		string temp;
		cout << "\n\nFound patterns: \n\n";
		while (getline(ifs, temp, '\n'))
		{
			smatch matches;
			if (regex_search(temp, matches, pat))
				cout << matches[0] << "\n";
		}
	}
	catch (regex_error& err)
	{
		cerr <<"\nRegex error:\n"<< err.what();
	}	
}

//13

//checks whether dot fits newline character ('\n)
void NewlineCheck()
{
	regex r{ R"(.)" };
	string s("\n");

	smatch match;
	if (regex_search(s, match, r))
		cout << "Newline fits to the dot!";
	else
		cerr << "newline does not fit dot !\n";
}

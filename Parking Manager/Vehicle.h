#pragma once
#include <string>
#include "Daytime.h"
#include <iostream>

using namespace std;

class Vehicle
{
protected:
	string registration_number;
	DayTime entry_time;
public:
	Vehicle(const string& registration_num, const DayTime& entry_t): registration_number(registration_num), entry_time(entry_t){}
	Vehicle(){}

	string get_registration_nubmer() const { return registration_number; }
	DayTime get_entry_time() const { return entry_time; }
	virtual double calculate_parking_cost(const DayTime& exit_time) = 0;
	virtual void print_info(ostream& os = cout) const
	{
		os << "Type: " << get_type() << "\n"
			<< "Registration number: " << registration_number << "\n"
			<< "Entry time: " << entry_time << "\n";
	}
	virtual void save_to_file(ostream& fileStream)const
	{
		fileStream << get_type()<<"\n"
			<< registration_number << "\n"
			<< entry_time.to_save_string() << "\n";
	}

	virtual string get_type() const = 0;
};
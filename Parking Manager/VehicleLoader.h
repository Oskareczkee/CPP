#pragma once
#include "VehicleIncludes.h"
#include <fstream>

class VehicleLoader
{
private:
	struct VehicleInfo
	{
		string registration_num;
		DayTime entry_time;
	};

	//usefull for brands, where name can be few words like alfa romeo
	static string load_string_line(ifstream& ifs)
	{
		string line;

		//optional to change
		//mixing standard >> operator and getline is a bad technique, they dont work so well together
		//problem here was, there was a \n at the end waiting, we have to take rid of it in this case
		//this may be error prone in the future, or in case of change of format, but is temporary solution
		ifs.get();

		getline(ifs, line, '\n');
		return line;
	}

	static VehicleInfo load_vehicle(ifstream& ifs)
	{
		VehicleInfo info;

		ifs >> info.registration_num >> info.entry_time;
		return info;
	}
public:

	static Car load_car(ifstream& ifs)
	{
		VehicleInfo info = load_vehicle(ifs);
		string brand;
		brand = load_string_line(ifs);

		return Car(brand, info.registration_num, info.entry_time);
	}

	static Truck load_truck(ifstream& ifs)
	{
		VehicleInfo info = load_vehicle(ifs);
		string brand;
		double length;
		brand = load_string_line(ifs);
		ifs >> length;

		return Truck(brand, length, info.registration_num, info.entry_time);
	}

	static Motorcycle load_motorcycle(ifstream& ifs)
	{
		VehicleInfo info = load_vehicle(ifs);
		string brand;
		brand = load_string_line(ifs);
		
		return Motorcycle(brand, info.registration_num, info.entry_time);
	}

};

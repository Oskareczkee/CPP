#pragma once
#include <list>
#include "VehicleIncludes.h"
#include "VehicleLoader.h"
#include <memory>
#include <algorithm>
#include <fstream>

using VehiclePtr = std::shared_ptr<Vehicle>;
using ParkingType = std::list<VehiclePtr>;

class Parking
{
private:
	int capacity = 0;
	ParkingType parking;
	double income = 0;
public:
	Parking(int _capacity): capacity(_capacity), parking(ParkingType()){}
	void register_vehicle(const VehiclePtr v);
	void unregister_vehicle(const std::string registration_num);
	double calculate_parking_cost(const VehiclePtr v);
	void display_parking_info();
	double get_income() const { return income; }
	void save_to_file(const std::string& fileName);
	void load_from_file(const std::string& fileName);
};

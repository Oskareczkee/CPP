#pragma once
#include "Vehicle.h"

class Car : public Vehicle
{
private:
	std::string car_brand;
	const int hour_cost = 10;
public:
	Car(const std::string& brand,
		const std::string& registation_number, 
		const DayTime& entry_time): Vehicle(registation_number, entry_time), car_brand(brand){}
	Car(){}

	virtual double calculate_parking_cost(const DayTime& exit_time) override
	{
		DayTime totalTime = entry_time - exit_time;
		double hrs = totalTime.getHoursNum();
		return hrs * hour_cost;
	}

	std::string get_car_brand() const { return car_brand; }

	virtual void print_info(ostream& os = cout)const override
	{
		Vehicle::print_info(os);
		os << "Brand: " << car_brand << "\n";
	}

	virtual void save_to_file(ostream& fileStream)const override
	{
		Vehicle::save_to_file(fileStream);
		fileStream << car_brand << "\n";
	}

	// Odziedziczono za poœrednictwem elementu Vehicle
	virtual string get_type() const override
	{
		return "Car";
	}
};

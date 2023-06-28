#pragma once
#include "Vehicle.h"

class Motorcycle : public Vehicle
{
private:
	std::string motor_brand;
	const int hour_cost = 5;
public:
	Motorcycle(const std::string& brand,
		const std::string& registation_number,
		const DayTime& entry_time) : Vehicle(registation_number, entry_time), motor_brand(brand) {}
	Motorcycle(){}

	// Odziedziczono za poœrednictwem elementu Vehicle
	virtual double calculate_parking_cost(const DayTime& exit_time) override
	{
		DayTime totalTime = entry_time - exit_time;
		double hrs = totalTime.getHoursNum();

		return hrs * hour_cost;
	}

	std::string get_motor_brand() const { return motor_brand; }

	virtual void print_info(ostream& os = cout) const override
	{
		Vehicle::print_info(os);
		os << "Brand: " << motor_brand << "\n";
	}

	virtual void save_to_file(ostream& fileStream)const override
	{
		Vehicle::save_to_file(fileStream);
		fileStream << motor_brand << "\n";
	}

	virtual string get_type() const override
	{
		return "Motorcycle";
	}
};
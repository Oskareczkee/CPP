#pragma once
#include "Vehicle.h"

class Truck : public Vehicle
{
private:
	std::string truck_brand;
	const int hour_cost = 15;
	double trailer_length = 0;
public:
	
	Truck(const std::string& brand,
		const double trailer_len,
		const std::string& registation_number, 
		const DayTime& entry_time) : Vehicle(registation_number, entry_time), truck_brand(brand), trailer_length(trailer_len) {}
	Truck(){}

	virtual double calculate_parking_cost(const DayTime& exit_time) override
	{
		DayTime totalTime = entry_time - exit_time;
		double hrs = totalTime.getHoursNum();
		return hrs * (hour_cost + trailer_length*0.1);
	}

	std::string get_truck_brand() const { return truck_brand; }
	double get_truck_length() const { return trailer_length; }

	virtual void print_info(ostream& os=cout) const override
	{
		Vehicle::print_info(os);
		os << "Brand: " << truck_brand << "\n";
		os << "Length " << trailer_length << "\n";
	}

	virtual void save_to_file(ostream& fileStream)const override
	{
		Vehicle::save_to_file(fileStream);
		fileStream << truck_brand << "\n"
			<< trailer_length << "\n";
	}

	virtual string get_type() const override
	{
		return "Truck";
	}
};
#include "Parking.h"

void Parking::register_vehicle(const VehiclePtr v)
{
	if (parking.size() < capacity)
		parking.push_back(v);
	else
	{
		cout << "Parking is already full\n";
		return;
	}

	cout << "Vehicle has been successfully registered\n";
}

void Parking::unregister_vehicle(const std::string registration_num)
{
	auto v = find_if(parking.begin(), parking.end(),
		[&registration_num](VehiclePtr ptr) {return ptr->get_registration_nubmer() == registration_num; });

	if (v == parking.end())
	{
		cout << "Vehicle with registration " << registration_num << " does not exist\n";
		return;
	}

	income += calculate_parking_cost(*v);
	parking.remove(*v);
	cout << "Vehicle with registration " << registration_num << " has been removed\n";
}

double Parking::calculate_parking_cost(const VehiclePtr v)
{
	return v->calculate_parking_cost(DayTime::now());
}

void Parking::display_parking_info()
{
	cout << "Parking capacity: " << capacity << "\n"
		<< "Empty slots: " << capacity - parking.size() << "\n";
	for (auto& v : parking)
	{
		v->print_info();
		cout << "Actual parking cost: " << calculate_parking_cost(v)<<"\n";
		cout << "\n";
	}
}

void Parking::save_to_file(const std::string& fileName)
{
	ofstream ofs{ fileName };
	for (auto& v : parking)
		v->save_to_file(ofs);

	cout << "Parking has been successfully saved\n";
}

void Parking::load_from_file(const std::string& fileName)
{
	ifstream ifs{ fileName };
	if (!ifs)
	{
		cout << "File has not been found";
		return;
	}

	string type;
	ParkingType new_parking;
	while (ifs)
	{
		if (new_parking.size() == capacity)
		{
			cout << "Cannot load all cars from file, parking is already full, consider making parking bigger for this file\n";
			parking = new_parking;
		}

		ifs >> type;
		
		if (!ifs)//this just means we got to the end of the file, type can get loaded, some junk at the end like \n or space may occur
			break;											//it also prevents from loading vehicle without any info

		if (type == "Car")
		{
			Car car = VehicleLoader::load_car(ifs);
			new_parking.push_back(make_shared<Car>(car));
		}
		else if (type == "Truck")
		{
			Truck truck = VehicleLoader::load_truck(ifs);
			new_parking.push_back(make_shared<Truck>(truck));
		}
		else if (type == "Motorcycle")
		{
			Motorcycle motor = VehicleLoader::load_motorcycle(ifs);
			new_parking.push_back(make_shared<Motorcycle>(motor));
		}
		else
		{
			cout << "Vehicle type cannot be found, please check file, parking not loaded...\n";
			return;
		}

	}

	cout << "Parking successfully loaded\n";
	parking = new_parking;
}

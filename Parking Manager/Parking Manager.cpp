#include <iostream>
#include <memory>
#include "Parking.h"
#include "Car.h"
#include "Truck.h"
#include "Motorcycle.h"
using namespace std;

void register_vehicle(Parking& p)
{
	int v_type = 0;
	cout << "Please choose vehicle type: \n"
		<< "1. Car\n2.Truck\n3.Motorcycle\n";
	cin >> v_type;

	if (v_type <= 0 || v_type > 3 || !cin)
	{
		cout << "Invalid value !\n";
		return;
	}

	string registration_num;
	cout << "Please enter registration number of vehicle";
	cin >> registration_num;

	DayTime register_time = DayTime::now();

	switch (v_type)
	{
	case 1:
	{
		string car_brand;
		cout << "Please enter car brand: ";
		cin >> car_brand;
		p.register_vehicle(make_shared<Car>(Car(car_brand, registration_num, register_time)));
		break;
	}
	case 2:
	{
		string truck_brand;
		double trailer_len = 0;
		cout << "Please enter truck brand: ";
		cin >> truck_brand;
		cout << "Please enter trailer length: ";
		cin >> trailer_len;
		p.register_vehicle(make_shared<Truck>(Truck(truck_brand, trailer_len, registration_num, register_time)));
		break;
	}
	case 3:
	{
		string moto_brand;
		cout << "Please enter motorcycle brand: ";
		cin >> moto_brand;
		p.register_vehicle(make_shared<Motorcycle>(Motorcycle(moto_brand, registration_num, register_time)));
		break;
	}
	default:
		break;
	}

}

int main()
{
	int parking_capacity = 0;
	while (true)
	{
		cout << "Please enter your parking capacity: ";
		cin >> parking_capacity;
		if (parking_capacity <= 0 || !cin)
		{
			cout << "Invalid value !\n";
			cin.ignore();
			cin.get();
			system("cls");
			continue;
		}

		break;
	}

	Parking parking(parking_capacity);
	cout << "Welcome to your parking manager!\nType help to check available commands\n";

	//simple commands
	string command;
	while (true)
	{
		cout << ">";
		cin >> command;
		if (command == "info")
			parking.display_parking_info();
		else if (command == "help")
			cout << "Available commands: \n"
			<< "-info\n-help\n-load\n-save\n-register\n-unregister\n-income\n-clear\n-exit\n";
		else if (command == "load")
		{
			string fileName;
			cout << "Enter file name: ";
			cin >> fileName;
			parking.load_from_file(fileName);
		}
		else if (command == "save")
		{
			string fileName;
			cout << "Enter file name: ";
			cin >> fileName;
			parking.save_to_file(fileName);
		}
		else if (command == "income")
			cout << "Your actual income is: " << parking.get_income() << "\n";
		else if (command == "unregister")
		{
			string registration_num;
			cout << "Please enter registration number of uregistered vehicle: ";
			cin >> registration_num;
			parking.unregister_vehicle(registration_num);
		}
		else if (command == "register")
			register_vehicle(parking);
		else if (command == "clear")
			system("cls");
		else if (command == "exit")
			return 0;
		else
			cout << "Invalid command !\n";
	}

	/*
	parking.register_vehicle(make_shared<Car>(Car("Alfa romeo", "WAA21832", DayTime(14, 52, 30))));
	parking.register_vehicle(make_shared<Car>("Ford", "WAA213213", DayTime(15, 32, 8)));
	parking.register_vehicle(make_shared<Car>("Citroen", "WAS2AGD2", DayTime(12, 12, 40)));
	parking.register_vehicle(make_shared<Truck>("Scania", 10.2, "AUX22431", DayTime(16, 32, 28)));
	parking.register_vehicle(make_shared<Motorcycle>("Yamaha", "WX2554", DayTime(18, 20, 21)));
	*/
	
	
	//parking.save_to_file("test.txt");
	//parking.load_from_file("test.txt");

	//parking.display_parking_info();
	//parking.unregister_vehicle("WAA21832");
	//parking.unregister_vehicle("sajdhdhj");

}

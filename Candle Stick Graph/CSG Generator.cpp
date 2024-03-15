#include "CSG.h"

using namespace std;

char file_input[50] = "intc_us_data.csv";
char file_output[50] = "chart.txt";

CSG csg;

void clean_cin()
{
	cin.clear();
	cin.ignore(INT_MAX, '\n');
}

void wait_for_enter()
{
	cin.ignore();
	cin.get();
}

void clear_screen()
{
	system("cls");
}

void option_change_output()
{
	clear_screen();
	cout << "New output file: ";
	cin >> file_output;
	cout << "Output has been succesfully changed!";
	wait_for_enter();
}

void option_change_input()
{
	clear_screen();
	cout << "New input file: ";
	cin >> file_input;
	cout << "Input has been succesfully changed!";
	wait_for_enter();
}

void option_change_height()
{
	clear_screen();
	cout << "New height: ";
	int height = 0;
	cin >> height;
	csg.set_height(height);
	cout << "Height has been successfully set!\n";
	wait_for_enter();
}

void option_change_grouping()
{
	clear_screen();
	cout << "Choose grouping: \n"
		<< "1. Day\n"
		<< "2. Week\n"
		<< "3. Month\n";
	int input = -1;
	cin >> input;

	switch (input)
	{
	case 1:
		csg.set_grouping(CSGGrouping::Day);
		break;
	case 2:
		csg.set_grouping(CSGGrouping::Week);
		break;
	case 3:
		csg.set_grouping(CSGGrouping::Month);
		break;
	default:
		cout << "Inproper input!";
		wait_for_enter();
		return;
	}

	cout << "Group has been succesfully changed";
	wait_for_enter();
}

int main()
{
	while (true)
	{
		clear_screen();
		cout << setw(15)<< "Input [" << file_input << "]\n"
			<< setw(15) << "Output [" << file_output << "]\n"
			<< setw(15) << "Candle count [" << csg.get_candle_count() << "]\n"
			<< setw(15) << "Grouping [" << group_to_string(csg.get_grouping()) << "]\n"
			<< setw(15) << "Height [" << csg.get_height() << "]\n"
			<< setw(15) << "Graph scale [" << csg.get_scale() << "]\n\n";

		cout << "Choose an option: \n"
			<< "g - load data\n"
			<< "o - change output file\n"
			<< "i - change input file\n"
			<< "j - change grouping\n"
			<< "h - change height\n"
			<< "q - quits the program\n";

		char input = ' ';
		cin.get(input);
		//make input case independent
		input = tolower(input);

		if (!cin)
		{
			cout << "Improper input!\n";
			system("cls");
			clean_cin();
		}

		switch (input)
		{
		case 'q':
			return 0;
		case 'g':
			csg.load_from_file(file_input);
			csg.generate_chart(file_output);
			clean_cin();
			break;
		case 'o':
			option_change_output();
			break;
		case 'i':
			option_change_input();
			break;
		case 'h':
			option_change_height();
			break;
		case 'j':
			option_change_grouping();
			break;
		default:
			break;
		}
	}
}
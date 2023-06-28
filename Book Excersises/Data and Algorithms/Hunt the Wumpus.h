#pragma once
#include <iostream>
#include <vector>
#include <random>
#include <sstream>

using namespace std;

namespace Hunt_the_wumpus
{


double GenerateRandomDouble(double left, double right)
{
	static random_device rd;
	static mt19937 mt(rd());
	uniform_real_distribution<double> dist(left, right);

	//generates double
	return { (dist(mt)) };
}

bool roll_dice(double chance)
{
	if (chance >= 100)
		return true;

	double roll = GenerateRandomDouble(0, 101);
	if (chance >= roll)
		return true;
	return false;
}

class Hunt_the_wumpus_game
{
public:
	void Play(istream& inputStream=cin);
private:
	struct Room
	{
		bool has_wumpus;
		bool has_pit;
		bool has_bats;
		int Room_num;
		vector<Room*>NearRooms = vector<Room*>(4);
	};

	const int rows = 6;
	const int cols = 6;
	const int max_Pits_num = 6;
	const int max_Bats_num = 3;
	int PlayerRoom = 0;
	int WumpusRoom = 0;
	bool isDead = false;
	bool isAwaken = false;
	bool Hunted = false;
	int Arrows = 5;

	vector<Room> Rooms;

	//Action keys
	const char MoveKey = 'm';
	const char ShootKey = 's';
	const char ClearScreen = 'c';

	//Generation
	void GenerateCave();
	void Place_Wumpus();
	void add_near_rooms();
	void Place_Player();

	//Gameplay
	void GameLoop();
	void MainMenu(istream& inputStream=cin);
	void MainMenuText();
	void Restart();

	//Movement
	void Move(const int& room_num);
	void Shoot(const int& room_num);
	bool IsNearbyRoom(const int& room_num);
	void WumpusMove();

	//Console
	void Log(const string& message)const;
	void PrintSituation();
	string GetInput(istream& stream);
	void ProcessInput(const string& inputOutput);
};

void Hunt_the_wumpus_game::Play(istream& inputStream)
{
	while (true)
	{
		MainMenu();
		Log("\n\nGame Ended... Do you wish to play one more time [Y\\N]\n");
		char command;
		if (inputStream >> command)
		{
			if (command == 'Y' || command == 'y')
			{
				system("cls");
				Restart();
				continue;
			}
			else
				break;
		}
	}
}

void Hunt_the_wumpus_game::Restart()
{
	PlayerRoom = 0;
	WumpusRoom = 0;
	isDead = false;
	isAwaken = false;
	Hunted = false;
	Arrows = 5;

	vector<Room> Rooms=vector<Room>();
}

void Hunt_the_wumpus_game::MainMenu(istream& inputStream)
{
	MainMenuText();
	Log("To start the game type \'Y\'\nType anything to close the game\n\n");
	char command;
	while (inputStream >> command)
	{
		if (command == 'Y' || command == 'y')
		{
			system("cls");
			GameLoop();
			break;
		}
		else
			break;
	}


}

void Hunt_the_wumpus_game::MainMenuText()
{
	Log( "Welcome to the Hunt The Wumpus !\n The Wumpus is a deadly creature living in the dark cave, there is no light\nand you lost your torch. But you are a great hunter, you can smell him\n"
		 "Your task is obviously to Hunt The Wumpus\n It won't be easy it's dark and Wumpus loves botomless pits, also giants bats live here uuugh...\n\n");

	Log("Game Rules:\nYou have only 5 arrows, so use them wisely\nWhen you shoot your arrow it will awake the Wumpus and he'll be hunting for you\nYou better do not enter his room, just kill him from distance"
		"if you are sure, where he is\nBats will carry you to random room\nBotomless pits are botomless and deadly, better don't enter them\n\n"
		"Type \'m\' [room number], to move to the room\nType \'s\' [room number], to shoot an arrow to this room !\n\n");
}

void Hunt_the_wumpus_game::GameLoop()
{
	GenerateCave();
	while (!isDead || Hunted)
	{
		PrintSituation();
		ProcessInput(GetInput(cin));
		WumpusMove();
	}
}



string Hunt_the_wumpus_game::GetInput(istream& stream)
{
	string output;
	stream >> output;

	return output;
}

void Hunt_the_wumpus_game::ProcessInput(const string& inputOutput)
{
	char action = inputOutput[0];
	
	string copy = inputOutput;
	copy.erase(0,1);

	if (action == ClearScreen)
	{
		system("cls");
		return;
	}

	int room_num = stoi(copy);

	if (!IsNearbyRoom(room_num))
		return;


	if (action == MoveKey)
		Move(room_num);
	if (action == ShootKey)
		Shoot(room_num);
}


bool Hunt_the_wumpus_game::IsNearbyRoom(const int& room_num)
{
	//check if room is connected with player room
	for (Room* r : Rooms[PlayerRoom - 1].NearRooms)
	{
		if (r->Room_num == room_num)
		{
			return true;
		}
	}
	Log("This room is not next to your actual room");
	return false;
}


void Hunt_the_wumpus_game::add_near_rooms()
{
	for (Room& room : Rooms)
	{
		//cout << room.Room_num << "\n";
		int roomUp=0;//upper
		int roomRight=0;//right
		int roomDown=0;//down
		int roomLeft=0;//left

		if (room.Room_num <= rows)
			roomUp = room.Room_num+(rows *(cols-1));
		else
			roomUp = room.Room_num - cols;

		if (room.Room_num % rows == 0)
			roomRight = room.Room_num - (cols - 1);
		else
			roomRight = room.Room_num + 1;

		if (room.Room_num > rows * (cols - 1))
			roomDown = room.Room_num - (rows * (cols - 1));
		else
			roomDown = room.Room_num + cols;

		if (room.Room_num % cols == 1)
			roomLeft = room.Room_num + (cols - 1);
		else
			roomLeft = room.Room_num - 1;


		room.NearRooms[0] = &Rooms[roomUp-1];
		room.NearRooms[1] = &Rooms[roomRight-1];
		room.NearRooms[2] = &Rooms[roomDown-1];
		room.NearRooms[3] = &Rooms[roomLeft-1];
	}
}
void Hunt_the_wumpus_game::GenerateCave()
{
	int room_count = rows * cols;

	for (int x = 1; x <= room_count; x++)
	{
			bool has_bat = roll_dice(20);
			if (has_bat)
			{
				Rooms.push_back(Room{ false,false,true, x});
				continue;
			}
			bool has_pit = roll_dice(30);
			if (has_pit)
			{
				Rooms.push_back(Room{ false,true,false,x});
				continue;
			}
			Rooms.push_back(Room{ false,false,false,x});
	}

	add_near_rooms();
	Place_Wumpus();
	Place_Player();
}

void Hunt_the_wumpus_game::Place_Wumpus()
{
	int roll = (int)GenerateRandomDouble(0,((double)cols * rows));

	//if room has pit, delete it
	Rooms[roll].has_pit = false;
	Rooms[roll].has_wumpus = true;
	WumpusRoom = roll;
}

void Hunt_the_wumpus_game::Place_Player()
{
	while (true)
	{
		int roll = (int)GenerateRandomDouble(0, ((double)cols * rows));
	
		if (Rooms[roll].has_pit || Rooms[roll].has_bats || Rooms[roll].has_wumpus)
			continue;
		PlayerRoom = roll;
		break;
	}
}

void Hunt_the_wumpus_game::Log(const string& message) const
{
	cout << message << "\n";
}


void Hunt_the_wumpus_game::Move(const int& room_num)
{
	if (!IsNearbyRoom(room_num))
		return;

	if (Rooms[room_num-1].has_pit)
	{
		isDead = true;
		Log("You fell down to botomless pit filled with slime ! You try to cry for help, but no one can hear you... except Wumpus");
		return;
	}


	else if (Rooms[room_num-1].has_wumpus)
	{
		isDead = true;
		Log("Wumpus has eaten you. He never had so tasty feast ! Ha Ha Ha");
		return;
	}


	else if (Rooms[room_num-1].has_bats)
	{
		Rooms[room_num - 1].has_bats = false;
		PlayerRoom = static_cast<int>(GenerateRandomDouble(1, (double)Rooms.size()+1));
		Log("Unbelievably great bats carried you to random room");
		return;
	}
	else
		PlayerRoom = room_num;
}

void Hunt_the_wumpus_game::Shoot(const int& room_num)
{
	if (!IsNearbyRoom(room_num))
		return;

	if (Arrows == 0)
	{
		Log("It looks like you are out of arrows\n\nYou stand no chances to fight Wumpus without arrows\nYou sit and wait for your fate...");
		isDead = true;
		return;
	}

	if (Rooms[room_num].has_wumpus)
	{
		Hunted = true;
		Arrows--;
		return;
	}
	else
	{
		if (!isAwaken)
		{
			Arrows--;
			isAwaken = true;
			Log("Wumpus heard that shot. And it looks like it annoyed him. Now you are being hunted !");
			return;
		}
		Arrows--;
		return;
	}
}

void Hunt_the_wumpus_game::WumpusMove()
{
	if (!isAwaken)
		return;

	//check if wumpus is surrounded by pits, if so, player wins
	int count = 0;
	for (Room* r : Rooms[WumpusRoom - 1].NearRooms)
	{
		if (r->has_pit)
			count++;
	}

	if (count == 4)
	{
		Log("Wumpus awakens and want to hunt you...\nBut he screams instead\nIt looks like he is surrounded by pits !\nHa ha ha well done hunter");
		Hunted = true;
	}

	while (true)
	{
	int room = (int)GenerateRandomDouble(0, 4);
	if (Rooms[WumpusRoom-1].NearRooms[room]->has_pit)
		continue;
	Rooms[WumpusRoom-1].has_wumpus = false;
	WumpusRoom = Rooms[WumpusRoom-1].NearRooms[room]->Room_num;
	Rooms[WumpusRoom-1].has_wumpus = true;
		break;
	}

	Log("You heard noise. It sounded like Wumpus ! He's hunting for you !");
}

void Hunt_the_wumpus_game::PrintSituation()
{
	//"You are in room: ";
	ostringstream ss{ string() };
	ss << "You are in room: " << PlayerRoom;
	Log(ss.str());

	ostringstream nearbyRooms{ string() };

	for (Room* r : Rooms[PlayerRoom-1].NearRooms)
	{
		nearbyRooms<< r->Room_num<<"  ";
	}

	ostringstream ss1{ string() };
	ss1 << "Nearby are rooms: " << nearbyRooms.str();
	Log(ss1.str());

	for (Room* r : Rooms[PlayerRoom-1].NearRooms)
	{
		if (r->has_bats)
			Log("You can hear bats !");
		if (r->has_pit)
			Log("You feel a breeze !");
		if (r->has_wumpus)
			Log("You smell Wumpus ! Uuuh he stinks ");
	}
}
}
#pragma once
#include <iostream>
#include <fstream>
#include <conio.h>

#include "mapLoader.h"
#include "map.h"
#include "Enumerators.h"


class Sokoban 
{
	private:
		Map map;
		int moveCount = 0;
		string levelName;
	private:

		void showMenu()
		{
			while (true)
			{
				system("cls");
				mapLoader::printImage("main-menu-text.txt");
				cout <<"1. Continue\n"
					 <<"2. Choose Level\n"
					 << "3. Retry Level\n"
					 << "4. Exit Game\n";
				int choose = 0;
				cin >> choose;
				switch (choose)
				{
				case 1:
					return;
				case 2:
					cout << "2";
					break;
				case 3:
					loadLevel(levelName);
					return;
				case 4:
					exit(0);
				default:
					break;
				}
			}
		}

		void loadLevel(const string& levelName)
		{
			map= mapLoader::loadMap(levelName);
			moveCount = 0;
		}

		Input getInput()
		{
			char c = _getch();
			c=tolower(c);
			return charToInput(c);
		}

		bool isValidMove(const Coords& move)
		{
			//order of this if does matter, if we swap order we might get out of bounds, so do not change order
			if (move.x<0 || move.x>map.size-1 || move.y<0 || move.y>map.map[move.x].size()-1)
				return false;
			if (map.map[move.x][move.y] == (char)GameSymbols::Wall || map.map[move.x][move.y] == (char)GameSymbols::BoxOnPlace)
				return false;

			return true;
		}

		bool isMovingBox(const Coords& move)
		{
			if (map.map[move.x][move.y] == (char)GameSymbols::Box)
				return true;
			return false;
		}


		/// <summary>
		/// moves box
		/// </summary>
		/// <returns>true if box could be moved, false if not</returns>
		bool moveBox(const Coords& boxCoords, const Coords& offset)
		{
			Coords newPosition = Coords{boxCoords.x + offset.x, boxCoords.y + offset.y};

			if (!isValidMove(newPosition))
				return false;

			map.map[boxCoords.x][boxCoords.y] = ' ';
			if (map.map[newPosition.x][newPosition.y] == (char)GameSymbols::Target)
			{
				map.map[newPosition.x][newPosition.y] = (char)GameSymbols::BoxOnPlace;
				map.boxCount--;
			}
			else
				map.map[newPosition.x][newPosition.y] = (char)GameSymbols::Box;
			return true;
		}

		void processInput()
		{
			switch (getInput())
			{
			case Input::Up:
				move(Coords{-1,0});
				break;
			case Input::Down:
				move(Coords{ 1,0 });;
				break;
			case Input::Right:
				move(Coords{ 0,1 });
				break;
			case Input::Left:
				move(Coords{ 0,-1 });
				break;
			case Input::OFFSET_UP:
				map.changeOffset(Coords{ 1,0 });
				break;
			case Input::OFFSET_DOWN:
				map.changeOffset(Coords{ -1,0 });
				break;
			case Input::OFFSET_LEFT:
				map.changeOffset(Coords{ 0,-1 });
				break;
			case Input::OFFSET_RIGHT:
				map.changeOffset(Coords{ 0,1 });
				break;
			case Input::Menu:
				showMenu();
				break;
			default:
				break;
			}
		}

		void move(const Coords& positionOffset)
		{
			Coords& player = map.player;
			Coords newCoords = Coords{ player.x + positionOffset.x, player.y +positionOffset.y };

			if (!isValidMove(newCoords))
				return;

			if (isMovingBox(newCoords))
				if (!moveBox(newCoords, positionOffset))
					return;

			map.map[player.x][player.y] = ' ';
			map.map[newCoords.x][newCoords.y] = (char)GameSymbols::Player;
			player = newCoords;
			moveCount++;
		}

		bool hasMoves()
		{
			if (moveCount == map.maxMoves)
				return false;
			return true;
		}

		bool hasWon()
		{
			if (map.boxCount==0)
				return true;
			return false;
		}

		void printInfo()
		{
			cout << "You have: " << map.maxMoves - moveCount << (map.maxMoves - moveCount == 1 ? " move": " moves")<<" left\n"
				<< "There "<<(map.boxCount==1? "is ": "are ") << map.boxCount << (map.boxCount == 1 ? " box " : " boxes ")  <<"left\n";
		}
public:

		Sokoban(const string& firstMap) : map(mapLoader::loadMap(firstMap)), levelName(firstMap) {}

		void loop()
		{
			while (true)
			{
				system("cls");

				cout << map;
				printInfo();

				if (!hasMoves())
				{
					cout << "Sorry you don't have any moves" << endl;
					break;
				}
				if (hasWon())
				{
					cout << "You won" << endl;
					break;
				}

				processInput();
			}
		}

};

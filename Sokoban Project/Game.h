#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <conio.h>

#include "mapLoader.h"
#include "map.h"
#include "Enumerators.h"
#include "imageLoader.h"
#include "simpleStack.h"
#include "modelLoader.h"


constexpr int SOKOBAN_LEVEL_COUNT = 3;

const wstring sokobanLevels[SOKOBAN_LEVEL_COUNT]{
	L"tutorial.txt",
	L"level1.txt",
	L"level2.txt"
};

void wait()
{
	wcin.ignore();
	wcin.get();
}

class Sokoban 
{
	private:
		Map map;
		//preload model to the memory
		Model playerModel = modelLoader::loadFromFile("player-model.txt");
		int unlocked_levels = 1;
		int map_index = 0;

		//we have many loops, thats why we need that bool, no direct way to exit main loop to main menu
		bool exit_to_main_menu = false;

		Stack<Map, 15> undoStack;
		Stack<Map, 15> redoStack;
	private:

		void showLevelsMenu()
		{
			while (true)
			{
				system("cls");
				imageLoader::printImage(L"choose-level.txt");
				wcout << L"0. quit menu\n";
				for (int x = 0; x < SOKOBAN_LEVEL_COUNT; x++)
					wcout << x + 1 << ". " <<sokobanLevels[x]<<endl;

				int choose = 0;
				wcin >> choose;

				if (choose == 0)
					return;

				if (choose > SOKOBAN_LEVEL_COUNT || choose < 1)
					continue;

				if (choose > unlocked_levels)
				{
					wcout << "You have not unlocked this level yet!\n";
					wait();
					continue;
				}

				map_index = choose - 1;
				loadLevel(sokobanLevels[map_index]);
				return;
			}
		}

		void showMenu()
		{
			while (true)
			{
				system("cls");
				imageLoader::printImage(L"main-menu-text.txt");
				wcout << "\n\n\n";
				wcout << "1. Continue\n"
					<< "2. Choose Level\n"
					<< "3. Retry Level\n"
					<< "4. Exit To Main Menu\n"
					<< "5. Exit Game\n";
				int choose = 0;
				wcin >> choose;
				switch (choose)
				{
				case 1:
					return;
				case 2:
					showLevelsMenu();
					return;
				case 3:
					loadLevel(sokobanLevels[map_index]);
					return;
				case 4:
					exit_to_main_menu=true;
					return;
				case 5:
					exit(0);
				default:
					break;
				}
			}
		}

		void mainMenu()
		{
			while (true)
			{
				system("cls");
				imageLoader::printImage(L"main-menu-text.txt");
				wcout << "\n\n\n";
				wcout << "1. Start game\n"
					<< "2. Author\n"
					<< "3. Exit\n";
				int choose = 0;
				wcin >> choose;
				switch (choose)
				{
				case 1:
					return;
				case 2:
					system("cls");
					imageLoader::printImage(L"author.txt");
					wait();
					break;
				case 3:
					exit(0);
				default:
					break;
				}
			}
		}

		void loadLevel(const wstring& levelName)
		{
			map = mapLoader::loadMap(levelName);
			undoStack.clear();
			redoStack.clear();
		}

		Input getInput()
		{
			char c = _getch();
			c=tolower(c);
			return charToInput(c);
		}

		void undo()
		{	
			if (undoStack.isEmpty())
				return;
			redoStack.push(undoStack.pop());
			map = redoStack.getTop();
		}

		void redo()
		{
			if (redoStack.isEmpty())
				return;
			undoStack.push(redoStack.pop());
			map = undoStack.getTop();
		}

		bool isValidMove(const Coords& object, const Coords& offset)
		{
			//order of this if does matter, if we swap order we might get out of bounds, so do not change order
			Coords moveCoords = { object.x + offset.x, object.y + offset.y };
			wchar_t objectChar = map.map[moveCoords.x][moveCoords.y];

			if (moveCoords.x<0 || moveCoords.x>map.size-1 || moveCoords.y<0 || moveCoords.y>map.map[moveCoords.x].size()-1)
				return false;
			if (isImmovable(objectChar))
				return false;

			if (objectChar == (wchar_t)GameSymbols::Box)
				return moveBox(moveCoords, offset);

			return true;
		}



		/// <summary>
		/// moves box
		/// </summary>
		/// <returns>true if box could be moved, false if not</returns>
		bool moveBox(const Coords& boxCoords, const Coords& offset)
		{
			if (!isValidMove(boxCoords, offset))
				return false;

			Coords newPosition = Coords{boxCoords.x + offset.x, boxCoords.y + offset.y};

			map.map[boxCoords.x][boxCoords.y] = L' ';
			if (map.map[newPosition.x][newPosition.y] == (wchar_t)GameSymbols::Target)
			{
				map.map[newPosition.x][newPosition.y] = (wchar_t)GameSymbols::BoxOnPlace;
				map.boxCount--;
			}
			else
				map.map[newPosition.x][newPosition.y] = (wchar_t)GameSymbols::Box;
			return true;
		}

		void processInput()
		{
			switch (getInput())
			{
			case Input::Up:
				movePlayer(map.player, Coords{-1,0});
				break;
			case Input::Down:
				movePlayer(map.player, Coords{ 1,0 });;
				break;
			case Input::Right:
				movePlayer(map.player, Coords{ 0,1 });
				break;
			case Input::Left:
				movePlayer(map.player, Coords{ 0,-1 });
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
			case Input::UNDO:
				undo();
				break;
			case Input::REDO:
				redo();
				break;
			default:
				break;
			}
		}

		bool move(const Coords& object, const Coords& positionOffset)
		{
			if (!isValidMove(object, positionOffset))
				return false;

			Coords newCoords = Coords{ object.x + positionOffset.x, object.y + positionOffset.y };
			wchar_t objectChar = map.map[object.x][object.y];

			map.map[object.x][object.y] = L' ';
			map.map[newCoords.x][newCoords.y] = objectChar;
			return true;
		}

		//complete buffering for models would be better if i would have created new map rendering, rendering map, then models, that wouldn't need buffer then

		/*
		void createModelBuffer(Model& model)
		{
			for (int x = 0; x < model.offsetsCount; x++)
			{
				Coords Position = { model.position.x + model.modelOffsets[x].x, model.position.y + model.modelOffsets[x].y };
				if (isBufferable(map.map[Position.x][Position.y]))
					model.buffer[x] = map.map[Position.x][Position.y];
				else
					model.buffer[x] = ' ';
			}
		}
		*/

		bool moveModel(const Coords& firstCoord, Model& model, const Coords& movementOffset)
		{
			if (!checkModelCollision(firstCoord, model, movementOffset))
				return false;

			//createModelBuffer(model);

			//clear whatever was at the model position
			for (int x = 0; x < model.offsetsCount; x++)
			{
				Coords Position = { firstCoord.x + model.modelOffsets[x].x, firstCoord.y + model.modelOffsets[x].y};
				map.map[Position.x][Position.y] = ' '; //model.buffer[x];
			}

			for (int x = 0; x < playerModel.offsetsCount; x++)
			{
				Coords nextPosition = { firstCoord.x + model.modelOffsets[x].x + movementOffset.x, firstCoord.y + model.modelOffsets[x].y +movementOffset.y };
				map.map[nextPosition.x][nextPosition.y] = model.model[x];
			}
			return true;
		}

		bool checkModelCollision(const Coords& firstCoord, Model& model, const Coords& movementOffset)
		{
			for (int x = 0; x < model.offsetsCount;x++)
			{
				if (!isValidMove(Coords{firstCoord.x+ model.modelOffsets[x].x, firstCoord.y+ model.modelOffsets[x].y }, Coords{movementOffset.x,movementOffset.y}))
					return false;
			}

			return true;
		}

		void movePlayer(Coords& player, const Coords& positionOffset)
		{
			//create buffer, if next position is target. Only target is bufferable for now

			//if move won't happen we won't push actual state to the stack
			Map oldState = map;

			if (!moveModel(player, playerModel, positionOffset))
				return;

			player= Coords{player.x + positionOffset.x, player.y + positionOffset.y};
			//quick fix
			map.moveCount++;

			//put one state before of the map to the stack
			undoStack.push(oldState);
			redoStack.clear();
		}

		bool hasMoves()
		{
			if (map.moveCount == map.maxMoves)
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
			wcout << "You have: " << map.maxMoves - map.moveCount << (map.maxMoves - map.moveCount == 1 ? " move": " moves")<<" left\n"
				<< "There "<<(map.boxCount==1? "is ": "are ") << map.boxCount << (map.boxCount == 1 ? " box " : " boxes ")  <<"left\n";
		}
public:

	Sokoban() : map(mapLoader::loadMap(sokobanLevels[0])){}

		void loop()
		{
			mainMenu();
			//load first map
			loadLevel(sokobanLevels[0]);

			//wcout << playerModel.offsetsCount << "\n" << playerModel.model << "\n";
			//wait();
			while (true)
			{
				if (exit_to_main_menu)
				{
					//just exited to main menu
					exit_to_main_menu = false;
					break;
				}

				system("cls");

				wcout << map;
				printInfo();

				if (!hasMoves())
				{
					wcout << "Sorry you don't have any moves" << endl;
					wait();
					loadLevel(sokobanLevels[map_index]);
				}
				if (hasWon())
				{
					wcout << "You won" << endl;

					if (unlocked_levels < SOKOBAN_LEVEL_COUNT && map.levelName==sokobanLevels[unlocked_levels])
						unlocked_levels++;

					map_index++;
					if (map_index == SOKOBAN_LEVEL_COUNT)
					{
						wcout << "Congratulations you have completed the game!\n";
						map_index = 0;
					}

					wait();
					loadLevel(sokobanLevels[map_index]);
					continue;
				}

				processInput();
			}
		}
};
#pragma once
#include <iostream>
#include "Game.h"

using namespace std;

int main()
{
	try
	{
		Sokoban game("test.txt");
		game.loop();

	}
	catch (const std::exception& e)
	{
		cerr << e.what();
	}


}


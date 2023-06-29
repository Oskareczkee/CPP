#pragma once
#include <iostream>
#include <io.h>
#include <fcntl.h>
#include "Game.h"
#include <locale>
#include <codecvt>

using namespace std;



int main()
{
	//sets utf-8
	//now we can only use "wide" output and input, using cout or cin will ruin our program
	auto out = _setmode(_fileno(stdout), _O_U8TEXT);
	std::locale::global(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t>));

	try
	{
		Sokoban game;
		while (true)
		{
			game.loop();
		}
	}
	catch (const std::exception& e)
	{
		wcerr << e.what();
	}


}


#include <Window.hpp>
#include <Graphics.hpp>
#include <iostream>
#include "Shapes.h"
#include "Program Consts.h"
#include "Abstraction.h"
#include "Functions.h"
#include <math.h>
using namespace sf;

double sin_cos(double x)
{
	return sin(x) + cos(x);
}

int main()
{
	RenderWindow win(VideoMode(winWidth, winHeight), "Window");
	ContextSettings settings;
	settings.antialiasingLevel=8;

	try
	{

	while (win.isOpen())
	{
		Event event;

		while (win.pollEvent(event))
		{
			if (event.type == Event::Closed)
				win.close();
		}

		win.clear(Color::Black);

		win.display();
	}
	}
	catch (std::exception& e)
	{
		std::cerr << e.what()<<"\n";
	}

	return 0;
}
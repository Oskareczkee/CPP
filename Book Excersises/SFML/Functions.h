#pragma once
#include <Window.hpp>
#include <Graphics.hpp>
#include <vector>
#include <iostream>
#include "Shapes.h"
#include "Program Consts.h"
#include "Abstraction.h"

using namespace std;
using namespace sf;

typedef double Fct(double val);

class Function
{
public:
	Function(Fct f, double left, double right, Vector2f origin, int count = 100, double xscale = 25, double yscale = 25)
		:F(f),leftInterval(left), rightInterval(right), Origin(origin), pointCount(count), XScale(xscale), YScale(yscale)
	{
		if (right - left <= 0) throw exception("Function class: constructor, arguments left and right are incorrect");
		if (count <= 0) throw exception("Function class: constructor, count has to be greater than 0");
		double dist = (right - left) / count;
		double r = left;

		for (int i = 0; i < count; i++)
		{
			Vector2f Point;
			Point.x = origin.x + (r * xscale);
			Point.y = origin.y - (f(r) * yscale);

			Points.push_back(Point);
			r += dist;
		}
	}
	//this class does not derives from object nor from shape class, function is not shape, and is not constructed from shapes (line does not derive from shape in SFML)
	//draw vertex lines instead of shapes

	void draw(RenderWindow& win)const
	{
		for (int x = 1; x < Points.size() - 1; x++)
		{
			Vertex line[] =
			{
				Vertex(Points[x-1], color),
				Vertex(Points[x], color)
			};
			win.draw(line, 2, sf::Lines);
		}
	}

	void set_funtion(Fct* f) { F = f; }
	void set_left(double l) { leftInterval = l; }
	void set_right(double r) { rightInterval = r; }
	void set_origin(Vector2f o) { Origin = o; }
	void set_count(int c) { pointCount = c; }
	void set_xscale(double x) { XScale = x; }
	void set_yscale(double y) { YScale = y; }
	void set_color(Color c) { color = c; }

	double get_left()const { return leftInterval; }
	double get_right()const { return rightInterval; }
	Vector2f get_origin()const { return Origin; }
	int get_count()const { return pointCount; }
	double get_xscale()const { return XScale; }
	double get_yscale()const { return YScale; }
	Color get_color()const { return color; }

	void reset(Fct* f, double left, double right, Vector2f origin, int count = 100, double xscale = 25, double yscale = 25)
	{
		F = f;
		leftInterval = left;
		rightInterval = right;
		Origin = origin;
		pointCount = count;
		XScale = xscale;
		YScale = yscale;
	}

private:
	Fct* F;
	vector<Vector2f> Points;
	double leftInterval;
	double rightInterval;
	Vector2f Origin;
	int pointCount;
	double XScale;
	double YScale;
	Color color=Color::Red;
};
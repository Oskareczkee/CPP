#pragma once
#include <Window.hpp>
#include <Graphics.hpp>
#include <cmath>
#include <vector>
#include "Program Consts.h"


using namespace sf;

//sign function
double sgn(double d)
{
	if (d > 0) return 1;
	if (d < 0) return -1;
	return 0;
}

ConvexShape SuperElipsis(int a, int b, double m, double n, unsigned int accuracy)
{
	if (m <= 0 || n <= 0)
		throw std::exception("M or N paramater of superelipsis has to be greater than 0");

	ConvexShape elipsis;
	std::vector<Vector2f> Points;

	for (double angle = 0.0; angle < 2 * PI; angle += 2 * PI / accuracy)
	{
		double x = pow(abs(cos(angle)), 2 / m) * a * sgn(cos(angle));
		double y = pow(abs(sin(angle)), 2 / n) * b * sgn(sin(angle));

		Points.push_back(Vector2f(x + xCenter, y + yCenter));
	}

	elipsis.setPointCount(Points.size());

	int x = 0;
	for (auto& Point : Points)
	{
		elipsis.setPoint(x, Point);
		x++;
	}

	return elipsis;
}

ConvexShape RoundedRectangle(int a, int b)
{
	return SuperElipsis(a, b, 5, 5, 100);
}

class Arrow : public Shape
{
public:
	explicit Arrow()
	{
		shape.setPointCount(PointCount);
		shape.setPoint(0, Vector2f(50, 0));
		shape.setPoint(1, Vector2f(100, 86.6));
		shape.setPoint(2, Vector2f(62.5, 86.6));
		shape.setPoint(3, Vector2f(62.5, 170));
		shape.setPoint(4, Vector2f(37.5, 170));
		shape.setPoint(5, Vector2f(37.5, 86.6));
		shape.setPoint(6, Vector2f(0, 86.6));

		update();
	}

	virtual std::size_t  getPointCount()const
	{
		return PointCount;
	}

	virtual sf::Vector2f getPoint(std::size_t index) const
	{
          return shape.getPoint(index);
	}

private:
	ConvexShape shape;
	static constexpr int PointCount = 7;
};

class RegularPolygon : public Shape
{
public:
	explicit RegularPolygon(unsigned int size = 10, int polygonCount = 3) : crlcl(CircleShape(size, polygonCount)), PolygonCount(polygonCount)
	{
		if (polygonCount < 3)
			throw std::exception("Regular Polygon polygonCount is less than 3 !");

		update();
	}


	virtual std::size_t  getPointCount()const
	{
		return PolygonCount;
	}

	virtual sf::Vector2f getPoint(std::size_t index) const
	{
		return crlcl.getPoint(index);
	}

private:
	CircleShape crlcl;
	int PolygonCount = 3;

};

class Elipsis : public Shape
{
public:
	explicit Elipsis(const Vector2f& radius, const int& accuracy=30): Radius(radius), Accuracy(accuracy)
	{
		if (Accuracy < 3)
			throw std::exception("Elipsis accuracy cannot be lower than 3 !");
		update();
	}

	const Vector2f GetRadius() const
	{
		return Radius;
	}


	void setRadius(const Vector2f& newRadius)
	{
		Radius = newRadius;
		update();
	}

	virtual std::size_t  getPointCount()const
	{
		return Accuracy;
	}

	virtual sf::Vector2f getPoint(std::size_t index) const
	{
		float angle = index * 2 * PI / getPointCount() - PI / 2;
		float x = std::cos(angle) * Radius.x;
		float y = std::sin(angle) * Radius.y;

		return sf::Vector2f(Radius.x + x, Radius.y + y);
	}

private:
	Vector2f Radius;
	int Accuracy;

};

Vector2f* CalculateFocals(Elipsis el)
{
	Vector2f pos = el.getPosition();
	Vector2f radius = el.GetRadius();
	Vector2f center = { pos.x + radius.x, pos.y + radius.y };

	int c = sqrt(abs(pow(radius.x / 2, 2) - pow(radius.y / 2, 2)));

	Vector2f Focal1 = Vector2f(center.x + c, center.y);
	Vector2f Focal2 = Vector2f(center.x - c, center.y);

	Vector2f* Focals = new Vector2f[2]{ Focal1, Focal2 };

	return Focals;
}

void ShowElipsisFocals(Elipsis el, RenderWindow& win)
{
	CircleShape f1(5);
	CircleShape f2(5);

	Vector2f* Focals = CalculateFocals(el);


	f1.setFillColor(Color::Red);
	f2.setFillColor(Color::Red);
	
	f1.setPosition(Focals[0]);
	f2.setPosition(Focals[1]);

	win.draw(f1);
	win.draw(f2);
}


void DrawLine(const Vector2f& p1, const Vector2f& p2, RenderWindow& win)
{
	Vertex line[] =
	{
		Vertex(p1),
		Vertex(p2)
	};

	win.draw(line, 2, sf::Lines);
}


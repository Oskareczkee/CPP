//i haven't done most of the excercises that required me to create shape classes, as i created many of them
//using inheritance by the way in previous chapter (Shapes.h)

#pragma once
#include <iostream>
#include <Window.hpp>
#include <Graphics.hpp>
#include <cmath>
#include <vector>
#include "Program Consts.h"

using namespace sf;
using namespace std;

//exc 9 done btw, but i had to name this class Group instead

class Object
{
public:
	virtual void draw(RenderWindow& win) const{
		//draw shapes
		for (Shape* s : shapes)
		{
			win.draw(*s);
			//bad alloc without this
			delete s;
		}

		//draw objects
		for (Object* o : objects)
		{
			o->draw(win);
			//bad alloc without this
			delete o;
		}

		//draw texts
		for (ObjectText t : texts)
		{
			//set the font right before drawing
			t.text.setFont(t.font);
			win.draw(t.text);
		}
	}

	virtual void move(const Vector2f& pos) {
		for (Shape* s : shapes)
			s->move(pos);
	};

	string Name()const { return name; }
	void set_name(const string& Name) { name = Name; }
	int shape_count()const { return shapes.size(); }

	Object(const Object&) = delete;
	Object& operator=(const Object&) = delete;

	virtual ~Object() {};
protected:

	//struct to store text and its font, font is not saved within the text, thats why we need to hold text and its font together
	struct ObjectText
	{
		Text text;
		Font font;
	};

	Object(const string& Name="Object"): name(Name) {};
	Object(initializer_list<Shape*>Shapes, const string& Name="Object") :shapes(Shapes), name(Name) {};

	void add_shape(Shape* shape) { shapes.push_back(shape); }
	void add_text(const ObjectText& text) { texts.push_back(text); }
	void set_shape(const int& index, Shape* shape)
	{

		if (index >= shapes.size())
		{
			string exc = "set_shape: Object " + Name() + " shape index was out of range\n";
			throw exception(exc.c_str());
		}
			shapes[index] = shape;
	}

	void add_object(Object* object) { objects.push_back(object); }

	void add_shapes(const vector<Shape*>& Shapes) 
	{
		for (auto s : Shapes)
			shapes.push_back(s);
	}

	void add_texts(const vector<ObjectText>& Texts)
	{
		for (auto t : Texts)
			texts.push_back(t);
	}


private:
	vector<Shape*> shapes;
	vector<Object*> objects;

	//text does not derive from shapes, so we need to hold it here
	vector<ObjectText> texts;
	string name;
};

class Smiley : public Object
{
public:
	Smiley() : Object()
	{
		CircleShape* eye1= new CircleShape(20);
		CircleShape* eye2=new CircleShape(20);
		Elipsis* lip = new Elipsis(Vector2f(50, 25));

		eye1->setFillColor(Color::Green);
		eye2->setFillColor(Color::Green);
		lip->setFillColor(Color::Red);

		eye2->setPosition(Vector2f(100, 0));
		lip->setPosition(Vector2f(25, 100));

		add_shape(eye1);
		add_shape(eye2);
		add_shape(lip);

		delete eye1, eye2, lip;
	}
};

//this should not be derived from object interface but rather from shape interface, but it is only a excercise
// 
//this circle cannot be moved
class Immobile_Circle : public Object
{
public:

	Immobile_Circle(const Vector2f& Pos, int Radius, string name) : Object(name), pos(Pos), radius(Radius)
	{
		if (radius <= 0)
			throw InvalidRadiusException();
		CircleShape* circle = new CircleShape(radius);
		circle->setPosition(pos);
		add_shape(circle);
		delete circle;
	}
	Immobile_Circle() : Object(), pos(Vector2f(0, 0)), radius(1) 
	{
		add_shape(new CircleShape(radius)); 
	}

	int get_radius()const { return radius; }
	Vector2f get_position()const { return pos; }

	void set_radius(int rad)
	{
		if (rad <= 0)
			throw InvalidRadiusException();
		radius = rad;
		CircleShape* circle = new CircleShape(radius);
		circle->setPosition(pos);

		set_shape(0, circle);
		delete circle;
	}

	//i think i couldn't do this better, object interface provides move function, which is very functional overall, but this is a unique case
	//Move function should not be used it will throw exception as this circle is immobile 
	void move(const Vector2f& pos) { throw ImmobileCircleException(); };
private:
	struct InvalidRadiusException { InvalidRadiusException() { throw exception("Radius has to be greater than 0 !"); } };
	struct ImmobileCircleException { ImmobileCircleException() { throw exception("This circle is immobile !"); } };
	int radius;
	Vector2f pos;
};

class Controler
{
public:
	virtual void on() = 0;
	virtual void off() = 0;
	virtual void set_level(int lvl) { level = lvl; };
	virtual void show() {};

	int get_level() { return level; };

	virtual ~Controler() {};
private:
	int level=0;
};

class Test_Controler : public Controler
{
public:
	void show()override
	{
		cout << "Controler state: " << (is_active() ? "active" : "not active") << "\nActual level: " << get_level() << "\n";
	}
	bool is_active() { return isActive; };

	void on()override { if (!isActive) isActive = true; };
	void off()override  { if (isActive) isActive = false; };

private:
	bool isActive = false;
};

class Shape_Controler : public Controler
{
public:
	Shape_Controler(Shape* shape) : ControlledShape(shape) { set_level(255); }

	void on()override 
	{
		Color color = ControlledShape->getFillColor();
		color.a = get_level();
		ControlledShape->setFillColor(color);
	}
	void off()override 
	{
		Color color = ControlledShape->getFillColor();
		color.a = 0;
		ControlledShape->setFillColor(color);
	}

	//Shape controler has its unique show function
	void show(RenderWindow& win)
	{
		win.draw(*ControlledShape);
	}

	//Controler derived show function is not used, but still available, it does nothing unless overrided

private:
	Shape* ControlledShape;
};

class Axis : public Object
{
public:
	enum class Orientation{x,y};
	Axis(Orientation o, Vector2f origin, int length, string label="", int notches_number = 0);
private:
	vector<Shape*> notches;
	Text label;
};


//constructor
Axis::Axis(Orientation o, Vector2f origin, int length, string label, int notches_number)
{
	if (length < 0) throw exception("incorrect axis length");

	switch (o)
	{
	case Axis::Orientation::x:
	{
		//add axis
		RectangleShape* axisLine = new RectangleShape(Vector2f(length, 2));
		axisLine->setPosition(origin);
		add_shape(axisLine);

		//add text
		Text text;
		Font font;
		if (!font.loadFromFile("arial.ttf"))
			throw exception("arial.ttf has not been found, please make sure, that font is included in files !");
		text.setPosition(origin.x, origin.y+20);
		text.setString(label);
		text.setFillColor(Color::White);
		text.setCharacterSize(12);

		ObjectText ot{ text, font };

		add_text(ot);

		//add notches
		if (notches_number > 0)
		{
			int dist = length / notches_number;
			int x = origin.x;

			//+1, to draw notch at the end of the axis
			for (int i = 0; i < notches_number+1; i++)
			{
				RectangleShape* rect = new RectangleShape(Vector2f(1, 10));
				rect->setPosition(Vector2f(x, origin.y));
				notches.push_back(rect);
				x += dist;
			}
		}
		add_shapes(notches);

		break;
	}
	case Axis::Orientation::y:
	{
		//add axis
		RectangleShape* axisLine = new RectangleShape(Vector2f(length, 2));
		axisLine->setPosition(origin);
		axisLine->setRotation(90);
		add_shape(axisLine);

		//add text
		Text text;
		Font font;
		if (!font.loadFromFile("arial.ttf"))
			throw exception("arial.ttf has not been found, please make sure, that font is included in files !");
		text.setPosition(origin.x-20, origin.y-20);
		text.setString(label);
		text.setFillColor(Color::White);
		text.setCharacterSize(12);

		ObjectText ot{ text, font };

		add_text(ot);

		//add notches
		if (notches_number > 0)
		{
			int dist = length / notches_number;
			int y = origin.y;

			//+1, to draw notch at the end of the axis
			for (int i = 0; i < notches_number+1; i++)
			{
				RectangleShape* rect = new RectangleShape(Vector2f(1, 10));
				rect->setPosition(Vector2f(origin.x, y));
				rect->setRotation(90);
				notches.push_back(rect);
				y += dist;
			}
		}
		add_shapes(notches);

		break;
	}
	default:
		throw exception("Wrong orientation of Axis !");
	}
}
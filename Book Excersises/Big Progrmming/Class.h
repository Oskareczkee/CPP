#pragma once
#define CLASS_H

using namespace std;

class vectorInt
{
public:
	vectorInt();
	vectorInt(unsigned int length);
	~vectorInt();
	vectorInt(const vectorInt& other);
	int getValue(unsigned int index);
	bool setValue(unsigned int index, int value);//returns true if everything went ok
	bool push_back(int value);
	vectorInt* get_new_node_ptr(int value);
	int length() { return elementCount; };

	vectorInt& operator= (const vectorInt& other);

private:
	int value;
	static unsigned int elementCount;
	//I forgot to add head, so its implementation was a bit trickier, but it works like normal vector
	vectorInt* next;
	vectorInt(int value, bool create_node=false);//i had to added this bool, otherwise this constructor could be received as constructor with lenght
};

unsigned int vectorInt::elementCount = 0;

vectorInt::vectorInt()
{
	while (elementCount <= 31)
	{
		value = 0;
		elementCount++;
		next = new vectorInt();
	}

}
vectorInt::vectorInt(unsigned int length)
{
	while (elementCount <= length)
	{
		value = 0;
		elementCount++;
		next = new vectorInt();
	}
}
vectorInt::vectorInt(int value, bool create_node)
{
	if (!create_node)
	{
		delete this;
		return;
	}
	this->value = value;
	this->next = NULL;
}

vectorInt::~vectorInt()
{
	delete next;
}

vectorInt::vectorInt(const vectorInt& other)
{
	vectorInt* temp = other.next;

	value = other.value;
	elementCount = 0;

	while (temp != NULL)
	{
		push_back(temp->value);
		temp = temp->next;
	}
}

vectorInt& vectorInt::operator=(const vectorInt& other)
{
	if (this == &other)
		return *this;
	delete next;
	next = NULL;

	vectorInt* temp = other.next;

	this->value = other.value;
	this->elementCount = 0;

	while (temp!=NULL)
	{
		push_back(temp->value);
		temp = temp->next;
	}
	return *this;
}

vectorInt* vectorInt::get_new_node_ptr(int value)
{
	vectorInt* temp = new vectorInt(value, true);
	return temp;
}


int vectorInt::getValue(unsigned int index)
{
	int actualIndex = 0;
	vectorInt* temp = this;

	while (actualIndex != index)
	{
		temp = temp->next;
		actualIndex++;
		if (actualIndex > elementCount)
			return NULL;
	}
	return temp->value;
}

bool vectorInt::setValue(unsigned int index, int value)
{
	int actualIndex = 0;

	vectorInt* temp = this;

	while (actualIndex != index)
	{
		actualIndex++;
		temp = temp->next;
	}
	temp->value = value;
	return true;
}

bool vectorInt::push_back(int value)
{
	vectorInt* temp = this;

	while (temp->next != NULL)
	{
		temp = temp->next;
	}
	temp->next = get_new_node_ptr(value);
	this->elementCount++;
	return true;
}



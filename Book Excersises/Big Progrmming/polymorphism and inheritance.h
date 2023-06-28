#pragma once
#include <iostream>
#include <time.h>
#define POLIMORPHYZM_AND_INHERITANCE

class IStringConvertable
{
public:
	virtual ~IStringConvertable() {};
private:
	virtual string ConvertToString() = 0;

};

struct user
{
	user(string name, string password) : Name(name), Password(password) {};
	string Name;
	string Password;
};

class Login : IStringConvertable
{
public:
	Login(user user) : User(user) {};
	virtual bool LogIn();
	virtual void setUser(user user) { User = user; };
private:
	virtual string ConvertToString();
	user User;
};

string Login::ConvertToString()
{
	//WTF is this C like library

	char Buffer[32];
	tm* ConvertedTime= new tm;

	time_t Time = time(NULL);
	errno_t err2=localtime_s(ConvertedTime, &Time);
	if (err2)
	{
		cout << "An error occured during local time conversion !\nError code: " + err2;
		return NULL;
	}
	errno_t err = asctime_s(Buffer, 32, ConvertedTime);
	if (err)
	{
		cout << "An error occured during time conversion !\nError code: " + err;
		return NULL;
	}

	string output;
	output += "Username: "+User.Name +"\nLogin Time: ";


	output += Buffer;

	return output;
}

bool Login::LogIn()
{
	string name, password;

	cout << "Name: ";
	cin >> name;
	cout << "\nPassword: ";
	cin >> password;
	if (name == User.Name && password == User.Password)
	{
		cout << "\n\nLogged in succesfully\n\n"+ ConvertToString();
		return 1;
	}
	else
	{
		cout << "\n\nUser name or password wrong !";
		return 0;
	}
}


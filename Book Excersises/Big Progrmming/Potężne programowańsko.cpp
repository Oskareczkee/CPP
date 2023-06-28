#pragma once

#include <iostream>
#include "Class.h"
#include "polymorphism and inheritance.h"
#include "IO Stream.h"
#include "templates.h"
#include <cstdlib>
#include <time.h>

using namespace std;

void Class_H_test()
{
#ifndef CLASS_H
    cout << "Class header file has not been included !";
    return;
#endif
    cout << "\nClass header file has been included !\n";
    vectorInt Vector;
    vectorInt Vector2;
    Vector.setValue(32, 15);
    cout<<"Value at index: "<<Vector.getValue(32)<<endl;
    Vector.push_back(30);
    cout << "Pushed back value: "<< Vector.getValue(Vector.length())<<endl;
    cout <<"length: "<< Vector.length()<<endl;

    Vector2 = Vector;
    cout << "\n\nCopied Vector2\n\n";
    cout << "length: " << Vector2.length() << endl;
    //Vector2.setValue(32, 15);
    cout << "Value at index: " << Vector2.getValue(32) << endl;
    //Vector2.push_back(30);
    cout << "Pushed back value: " << Vector2.getValue(Vector2.length()) << endl;

    vectorInt Vector3(Vector);
    cout << "\n\nCopied Vector3\n\n";
    cout << "length: " << Vector3.length() << endl;
    //Vector2.setValue(32, 15);
    cout << "Value at index: " << Vector3.getValue(32) << endl;
    //Vector3.push_back(30);
    cout << "Pushed back value: " << Vector3.getValue(Vector3.length()) << endl;
}

void Polimorphyzm_And_Inheritance_H_test()
{
#ifndef POLIMORPHYZM_AND_INHERITANCE
    cout << "Polimorphyzm and Inheritance header file has not been included !";
    return;
#endif
    cout << "Polimorphyzm and Inheritance header file has been included !\n";
    user User("Stasiek", "WielkiHuj123");
    Login UserLogin(User);
    UserLogin.LogIn();

}

void IO_Stream_H_test()
{
#ifndef IO_STREAM
    cout << "IO Stream header file has not been included !";
    return;
#endif
    cout << "IO Stream header file has been included !\n";
    //Add_Score();
    //Read_Score();
    //HTML_Analyzer();
}

void Templates_test()
{
#ifndef TEMPLATES
    cout << "Templates header file has not been included !";
    return;
#endif
    cout << "Templates header file has been included !\n";
    /*
    vector<int>siema;
    for (int x = 0; x < 10; x++)
    {
        siema.push_back(x);
    }

    cout << Sum_Vector(siema) << "\n";
    */

    /*
    Vector<int> Vector2;
    Vector<int> Vector1;

    Vector1.setValue(1, 15);
    cout << "Value at index: " << Vector1.getValue(1) << endl;
    Vector1.push_back(30);
    cout << "Pushed back value: " << Vector1.getValue(Vector1.length()) << endl;
    cout << "length: " << Vector1.length() << endl;

    Vector2 = Vector1;
    cout << "\n\nCopied Vector2\n\n";
    cout << "length: " << Vector2.length() << endl;
    //Vector2.setValue(32, 15);
    cout << "Value at index: " << Vector2.getValue(1) << endl;
    //Vector2.push_back(30);
    cout << "Pushed back value: " << Vector2.getValue(Vector2.length()) << endl;

    Vector<int>Vector3(Vector1);
    cout << "\n\nCopied Vector3\n\n";
    cout << "length: " << Vector3.length() << endl;
    //Vector2.setValue(32, 15);
    cout << "Value at index: " << Vector3.getValue(1) << endl;
    //Vector3.push_back(30);
    cout << "Pushed back value: " << Vector3.getValue(Vector3.length()) << endl;
    */

    /*
    vector<double> hej;
    for (int x = 0; x < 10; x++)
    {
        hej.push_back(x*0.75);
    }

    vector<string> buic;
    buic.push_back("wielkolud");

    cout<<FindInVector(buic, "wielkolud");
    cout << FindInVector(hej, 0.75);
    */

    vector<int> siema;
    vector<string> stringVec = { "siema", "hej", "Adam", "Baczek", "huj" };
    for (int x = 0; x < 10; x++)
    {
        siema.push_back(rand() % (100 - 0 + 1) + 0);
        cout << siema[x]<<"\n";
    }
    SortVector(stringVec);

    cout << "\n\n";

    /*
    for (int x = 0; x < 10; x++)
    {
        cout << siema[x]<<"\n";
    }
    */
    for (vector<string>::iterator itr = stringVec.begin(); itr != stringVec.end(); ++itr)
    {
        cout << *itr << "\n";
    }

}

int main()
{
    srand(time(NULL));

    cout << "Hello World!\n";
    Templates_test();
}

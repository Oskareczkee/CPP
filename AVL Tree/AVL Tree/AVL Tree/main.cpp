#include <iostream>
#include "AVL Tree.h"
#include <fstream>
#include <random>

using namespace std;

AVLTree<int> tree;

static ofstream os{};

void readFromFile(const string& file)
{
    ifstream ifs{ file };

    if (!ifs)
        throw exception("File has not been found!");

    int num = 0;
    while (ifs >> num)
        tree.insert(num);
}

void generateRandomNumbers(const int leftRange, const int rightRange, const int& howMany, const string& saveFile)
{
    static random_device rd;
    static mt19937 mt(rd());
    static uniform_int_distribution<int> dist(leftRange, rightRange);

    ofstream of{ saveFile };

    for (int x = 0; x < howMany; x++)
    {
        int num = dist(mt);
        of << num << "\n";
        tree.insert(num);
    }
}


int main()
{
    try
    {
        while (true)
        {
            string command;


            cin >> command;

            if (command == "read")
                readFromFile("InTest1.txt");
            else if (command == "random")
                generateRandomNumbers(-1000, 1000, 30, "OutTest2.txt");
            else if (command == "save")
                tree.saveToFile("OutTest3.txt");
            else if (command == "add")
            {
                int num = 0;
                cout << "Insert number: ";
                cin >> num;
                tree.insert(num);
                cout << "Number has been added!\n";
            }
            else if (command == "delete")
            {
                int num = 0;
                cout << "Delete number: ";
                cin >> num;

                if (tree.find(num) != nullptr)
                {
                    tree.deleteNode(num);
                    cout << "Number has been successfully deleted!\n";
                }
                else
                    cout << "Number could not be found!\n";
            }

            else if (command == "find")
            {
                int num = 0;
                cout << "Find number: ";
                cin >> num;
                auto output = tree.find(num);
                if (output == nullptr)
                    cout << "Number has not been found!\n";
                else
                    cout << output->content<<" Balance: " << tree.calculateBalanceFactor(output) <<"Height: "<< tree.getTreeHeight() - tree.calculateHeight(output) << "\n";
            }
            else if (command == "print")
                tree.printContent();
            else if (command == "quit")
                break;
        }
    }
    catch (const std::exception& e)
    {
        cerr << e.what();
    }
}


#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>

using namespace std;

int main()
{
	int f = 1;
	cout << "Name: ";
	string name;
	cin >> name;
	while (f)
	{
		ofstream server;
		server.open("D:\\C++ projects\\server.txt");
		server << name << ' ';
		int tmp;
		cout << "First mark: ";
		cin >> tmp;
		server << tmp << ' ';
		cout << "Second mark: ";
		cin >> tmp;
		server << tmp << ' ';
		cout << "Third mark: ";
		cin >> tmp;
		server << tmp << ' ';
		cout << "Fourth mark: ";
		cin >> tmp;
		server << tmp << ' ';
		server.close();

		Sleep(1);

		cout << endl;
		tmp = 0;
		ifstream res;
		res.open("D:\\C++ projects\\" + name + ".txt");
		res >> tmp;
		if (tmp)
		{
			cout << tmp << " faild exams" << endl;
		}
		else
		{
			cout << "all exams passed" << endl;
		}
		res.close();

		int f2 = 1;
		while (f2)
		{
			cout << "Exit Y/N?" << endl;
			cin >> name;

			if (name == "y" || name == "Y")
			{
				f = 0;
				f2 = 0;
			}
			else if (name == "n" || name == "N")
			{
				f2 = 0;
			}
			else
			{
				cout << "Wrong input." << endl;
				f2 = 1;
			}
		}
		
	}
	return 0;
}
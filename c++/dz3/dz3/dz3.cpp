// dz3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <string>

using namespace std;

int main()
{
	string str;
	getline(cin, str);
	int count[10] = { 0 };
	cout << count[0] << endl;
	int len = str.length();
	for (int i = 0; i < len; i++)
	{
		switch (str[i]){
		case '0': count[0]++; break;
		case '1': count[1]++; break;
		case '2': count[2]++; break;
		case '3': count[3]++; break;
		case '4': count[4]++; break;
		case '5': count[5]++; break;
		case '6': count[6]++; break;
		case '7': count[7]++; break;
		case '8': count[8]++; break;
		case '9': count[9]++; break;
		}
	}
	cout << "0: " << count[0] << endl;
	cout << "1: " << count[1] << endl;
	cout << "2: " << count[2] << endl;
	cout << "3: " << count[3] << endl;
	cout << "4: " << count[4] << endl;
	cout << "5: " << count[5] << endl;
	cout << "6: " << count[6] << endl;
	cout << "7: " << count[7] << endl;
	cout << "8: " << count[8] << endl;
	cout << "9: " << count[9] << endl;

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

// sm1_2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>

using namespace std;

int main()
{
	float eps, a;
	cout << "cube root of ";
	cin >> a;
	cout << "approximation: ";
	cin >> eps;
	float x1 = 0, x2 = a;
	do
	{
		x1 = x2;
		x2 = (float)1 / 3 * (2 * x1 + a / x1 /x1);
	} while (abs(x1-x2) > eps);
	cout << "answer is " <<x2;
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

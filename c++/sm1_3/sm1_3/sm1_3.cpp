// sm1_3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
using namespace std;

int main()
{
	double x, eps;
	cout << "input value of cos ";
	cin >> x;
	cout << "approximation ";
	cin >> eps;
	double sum = 1;
	double el=1;
	int i=1;
	do
	{
		el *= -1.0 * x * x / ((2.0*i - 1.0) * (2.0*i));
		sum += el;
		i++;
	} while (abs(el) > eps);
	cout << "answer is " << sum;
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

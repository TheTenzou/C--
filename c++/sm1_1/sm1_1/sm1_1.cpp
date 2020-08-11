// sm1_1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>

using namespace std;
int main()
{	
	float x, x1;
	int count = 1, max_count = 0;
	cout << "input number ";
	cin >> x1;
	for (cin >> x; x; x1=x, cout << "input new number ", cin >> x)
	{
		if (x1 > x)
		{
			count++;
		}
		else
		{
			if (max_count < count)
			{
				max_count = count;
				count = 1;
			}
		}
	}
	if (max_count) 
	{
		max_count = count;
	}
	cout <<"lenth of longest decreasing sequence "<< max_count;
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

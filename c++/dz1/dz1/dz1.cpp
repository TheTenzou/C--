// dz1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
//#include "stdafx.h"
#include <iostream>
#include <string>

using namespace std;

bool check_sim(string str)
{
	int len = str.length();
	for (int i = 0; i < len / 2; ++i)
	{
		if (str[i] != str[len - i - 1])
		{
			return false;
		}
	}
	return true;
}

int main()
{	
	int n;
	cin >> n;
	string arr_str[10];
	//string str;
	for (int i = 0; i < n; i++)
	{
		cin >> arr_str[i];
	}

	cout << endl;
	int count = 0;
	for (int i = 0; i < n; i++)
	{
		if (check_sim(arr_str[i]))
		{
			count++;
		}
	}
	cout << count;
	return 0;
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

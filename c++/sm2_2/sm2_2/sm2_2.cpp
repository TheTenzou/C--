// sm2_2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <time.h>

using namespace std;

int main()
{
	srand(time(0));
	int n;
	cin >> n;
	int **a = new int*[n];
	for (int i = 0; i < n; i++)
	{
		a[i] = new int[n];
	}


	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			a[i][j] = rand() % 100;
		}
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout.width(3);
			cout << a[i][j];
		}
		cout << endl;
	}

	int max = a[0][0];
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < i; j++)
		{
			if (a[i][j] > max)
			{
				max = a[i][j];
			}
		}
	}

	int sum = 0;

	for (int i = 0; i < n; i++)
	{
		for (int j = i; j < n; j++)
		{
			if (a[i][j] > max)
			{
				sum += a[i][j];
			}
		}
	}
	cout << "max " << max << endl << "sum " << sum;
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

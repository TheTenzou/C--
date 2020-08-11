// Determinant.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

float* gauss(float** a, float* y, int n)
{
	float* x, max;
	int k, index;
	const float eps = 0.00001;
	x = new float[n];
	k = 0;
	while (k < n)
	{
		max = abs(a[k][k]);
		index = k;
		for (int i = k + 1; i < n; i++)
		{
			if (abs(a[i][k]) > max)
			{
				max = abs(a[i][k]);
				index = i;
			}
		}

		if (max < eps)
		{
			cout << "no solutions ";
			return 0;
		}
		for (int j = 0; j < n; j++)
		{
			float temp = a[k][j];
			a[k][j] = a[index][j];
			a[index][j] = temp;
		}
		float temp = y[k];
		y[k] = y[index];
		y[index] = temp;
		for (int i = k; i < n; i++)
		{
			float temp = a[i][k];
			if (abs(temp) < eps) continue;
			for (int j = 0; j < n; j++)
				a[i][j] = a[i][j] / temp;
			y[i] = y[i] / temp;
			if (i == k)  continue;
			for (int j = 0; j < n; j++)
				a[i][j] = a[i][j] - a[k][j];
			y[i] = y[i] - y[k];
		}
		k++;
	}
	for (k = n - 1; k >= 0; k--)
	{
		x[k] = y[k];
		for (int i = 0; i < k; i++)
			y[i] = y[i] - a[i][k] * x[k];
	}
	return x;
}



int main()
{
	cout << "enter file name" << endl; 
	string filename;
	cin >> filename;
	ifstream file;
	file.open(filename + ".txt");

	string line; //строчка для считывания из флага
	//float arr[3][4]; //матрица
	float ** ar, * sv, *ans;
	int i = 0; //строка
	int j = 0; //столбец
	int n = 0;

	if (file.is_open()) // если файл открылся то читаем
	{
		getline(file, line);
		n = stoi(line);
		ar = new float* [n];
		sv = new float[n];
		for (int i = 0; i < n; ++i)
		{
			ar[i] = new float[n];
		}

		while (getline(file, line)) 
		{	
			size_t posBegin = line.find(' ', 0); //начало первого числа
			j = 0;
			size_t posl = line.find('|', 0);

			sv[i] = stof(line.substr(posl + 2, line.find(' ', posl + 2) - 1));

			while ((posBegin < posl)) //пока положение указателя меньше разделителя считываем
			{
				size_t posEnd = line.find(' ', posBegin + 1); // позиция конца числа
				if (posEnd < posl) // проверка на выходы за граници
				{
					ar[i][j] = stof(line.substr(posBegin + 1, posEnd - posBegin - 1)); //считали число
					++j; 
				}
				posBegin = line.find(' ', posBegin + 1);// начало следуюшего числа
			}
			++i;
		}
		file.close();
		cout << "====" << endl;
		for (int i = 0; i < n; ++i)
		{
			for (int j = 0; j < n; ++j)
			{
				cout << ar[i][j]<< ' ' ;
			}
			cout <<sv[i] << endl;
		}
		
		ans = gauss(ar, sv, n);;

		cout << "====" << endl;
		for (int i = 0; i < n; ++i)
		{
			cout << ans[i] << endl;
		}
	}
	else
	{
		cout << "file doesn't exist" << endl;
	}
	system("pause");
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

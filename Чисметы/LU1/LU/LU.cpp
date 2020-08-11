// LU.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int input(string fileName, float ** &A, int &n)
{
	ifstream file;
	file.open(fileName + ".txt");
	int i = 0; //строка
	int j = 0; //столбец
	string line;

	if (file.is_open()) // если файл открылся то читаем
	{
		getline(file, line);
		n = stoi(line);
		A = new float* [n];
		for (int i = 0; i < n; ++i)
		{
			A[i] = new float[n];
		}

		while (getline(file, line))
		{
			size_t posBegin = line.find(' ', 0); //начало первого числа
			j = 0;

			while ((posBegin < line.length())) //пока положение указателя меньше разделителя считываем
			{
				size_t posEnd = line.find(' ', posBegin + 1); // позиция конца числа
				if (posEnd < line.length()) // проверка на выходы за граници
				{
					A[i][j] = stof(line.substr(posBegin + 1, posEnd - posBegin - 1)); //считали число
					++j;
				}
				posBegin = line.find(' ', posBegin + 1);// начало следуюшего числа
			}
			++i;
		}
		file.close();
		return 1;
	}
	else
	{
		cout << "file doesn't exist" << endl;
		return 0;
	}
}

void show(float** A, int n)
{
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			cout << A[i][j] << ' ';
		}
		cout << endl;
	}
}

void LU(float**& A, float**& L, float**& U, int n)
{
	L = new float* [n];
	U = new float* [n];
	for (int i = 0; i < n; ++i)
	{
		L[i] = new float[n] {0};
		U[i] = new float[n] {0};
	}
	for (int i = 0; i < n; ++i)
	{
		U[i][i] = 1;
	}

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			if (i < j)
			{
				float sum = 0;
				for (int s = 0; s < i; ++s)
				{
					sum = L[i][s] * U[s][j] + sum;
				}
				U[i][j] = 1 / L[i][i] * A[i][j] - sum;
			}
			else
			{
				float sum = 0;
				for (int s = 0; s < j; ++s)
				{
					sum = L[i][s] * U[s][j] + sum;
				}
				L[i][j] = A[i][j] - sum;
			}

		}
	}
}


void solve(float** L, float** U, float* ans, int n)
{
	float* Y = new float[n] {0};

	for (int i = 0; i < n; ++i)
	{
		float sum = 0;
		for (int j = 0; j < i; ++j)
		{
			sum += L[i][j] * Y[j];
		}
		Y[i] =  ( 0 - sum) / L[i][i];
	}
	for (int i = n - 1; i > 0; --i)
	{
		float sum = 0;
		for (int j = i + 1; j < n; ++j)
		{
			sum += U[i][j] * ans[j];
		}
		ans[i] = Y[i] - sum;
	}
}


int main()
{
	cout << "enter file name" << endl;
	string filename;
	cin >> filename;
	float** A, ** L{ 0 }, ** U{ 0 }, ** R{ 0 }, * ans;
	int n;
	if (input(filename, A, n))
	{
		cout << "====" << endl;
		for (int i = 0; i < n; ++i)
		{
			for (int j = 0; j < n; ++j)
			{
				cout << A[i][j] << ' ';
			}
			cout << endl;
		}

		
		LU(A, L, U, n);
		cout << "U" << endl;
		show(U, n);
		cout << "L" << endl;
		show(L, n);
		float* ans = new float[n] {0};
		solve(L, U, ans, n);
		cout << "====" << endl;
		for (int i = 0; i < n; ++i)
		{
			cout << ans[i] << endl;
		}
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

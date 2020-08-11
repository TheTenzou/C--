#include <iostream>
#include <fstream>

int t;

using namespace std;

double fnc(double x)
{
	if (t == 1)
	{
		return sin(x);
	}
	else if (t == 2)
	{
		return x * sin(x*x) + 1;
	}
	else if (t == 3)
	{
		return pow((x - 1), 3);
	}
}

int main()
{
	ofstream output;
	output.open("ans.txt");
	double x;
	double b;
	double h = 0.01;
	cout << "Function #: ";
	cin >> t;
	cout << "A: ";
	cin >> x;
	cout << "B: ";
	cin >> b;
	output << "x y d_n=1 d_n=3" << endl;
	while (x < b)
	{
		cout << "x = " << x << ' ';
		output << x << ' ';
		output << fnc(x) << ' ';
		cout << "n = 1: ";
		cout << (fnc(x + h) - fnc(x)) / h << ' ';
		output << (fnc(x + h) - fnc(x)) / h << ' ';
		cout << "n = 3: ";
		cout << (- 11 * fnc(x) + 18 * fnc(x + h) - 9 * fnc(x + 2 * h) + 2 * fnc(x + 3 * h)) / (6 * h) << endl;
		output << (-11 * fnc(x) + 18 * fnc(x + h) - 9 * fnc(x + 2 * h) + 2 * fnc(x + 3 * h)) / (6 * h) << endl;
		x += h;
	}
	output.close();
	system("pause");
	return 0;
}
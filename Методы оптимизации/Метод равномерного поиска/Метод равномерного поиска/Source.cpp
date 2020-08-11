#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

double func(double x)
{
	return x * x - 72 * x + 14;
}

int main()
{
	setlocale(LC_ALL, "rus");
	ofstream output;
	output.open("ans.txt");
	vector<pair<double, double>> x;
	double a, b, l, e;
	cout << "a = ";
	cin >> a;
	cout << "b = ";
	cin >> b;
	cout << "e = ";
	cin >> e;

	int n = ceil((b - a) / e - 1);

	cout << "n = " << n << endl;

	l = b - a;
	output << "1) L_0 = " << l << endl;

	double tmp = a;
	for (int i = 1; i <= n; ++i) {
		tmp = a + i * (b - a) / (n + 1);
		x.push_back(make_pair(tmp, func(tmp)));
	}

	for (int i = 0; i < x.size(); ++i)
	{
		output << "   x_" << i + 1 << " = " << x[i].first << endl;
	}

	for (int i = 0; i < x.size(); ++i)
	{
		output << "   f(x_" << i + 1 << ") = " << x[i].second << endl;
	}

	int i_min = 0;
	double min = x[0].second;
	for (int i = 1; i < x.size(); ++i)
	{
		if (x[i].second < min)
		{
			min = x[i].second;
			i_min = i;
		}
	}

	output << "4) min f(x_i) = " << " f(x_" << i_min + 1 << ") = " << " f(" << x[i_min].first << ") = " << min << endl;
	output << " Ответ: " << x[i_min].first << " +- " << (b - a) / (n + 1);
	output.close();
	system("pause");
	return 0;
}
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int f;

//2*x*x - x*y - 5*x +1
//y*x - 2*x + y
double function_1_f(double x, double y)
{
	if (f == 1)
		return 2 * x * x - x * y - 5 * x + 1;
	else if (f == 2)
		return x * x - y;
}

//x + 3*log10(x) - y*y;
//log(x) - y*y/x
double function_2_f(double x, double y)
{
	if (f == 1)
		return x + 3 * log10(x) - y * y;
	else if (f == 2)
		return x - y * y;
}


//2*x*x - x*y - 5*x +1
double function_1(double x, double y)
{
	if (f == 1)
		return sqrt((x * (y + 5) - 1) / 2);
	else if (f == 2)
		return sqrt(y);
}

//return x + 3*log10(x) - y*y;
double function_2(double x, double y)
{
	if (f == 1)
		return sqrt(x+3*log10(x));
	else if (f == 2)
		return sqrt(x);
}


pair<double,double> zeidel(double x, double y)
{
	double tmp_x;
	double tmp_y;
	double eps = 0.1;
	int i = 0;
	do
	{
		
		tmp_x = x;
		tmp_y = y;
		x = function_1(x, y);
		y = function_2(x, y);
		cout << ++i << "  " << x << ' ' << y << '\n';
	} while ((tmp_x - x) * (tmp_x - x) + (tmp_y - y) * (tmp_y - y) > eps);
	cout << "=========" << endl;
	return make_pair(x, y);
}

void obr_mat(double a[2][2])
{
	double det, tmp;
	det = a[0][0] * a[1][1] - a[0][1] * a[1][0];
	tmp = a[0][0];
	a[0][0] = a[1][1] / det;
	a[1][1] = tmp / det;
	tmp = a[0][1];
	a[0][1] = a[1][0] / det;
	a[1][0] = tmp / det;
}

pair<double, double> newton(pair<double,double> xy)
{
	double dx, dy, a[2][2], h = 0.01, eps = 0.00000001;
	double tmp_x;
	double tmp_y;
	double t;
	int i = 0;
	//for (int i = 0; i < 10; ++i)
	do
	{
		tmp_x = xy.first;
		tmp_y = xy.second;
		a[0][0] = (function_1_f(xy.first + h, xy.second) - function_1_f(xy.first - h, xy.second)) / (2 * h);
		a[0][1] = (function_1_f(xy.first, xy.second + h) - function_1_f(xy.first, xy.second - h)) / (2 * h);
		a[1][0] = (function_2_f(xy.first + h, xy.second) - function_2_f(xy.first - h, xy.second)) / (2 * h);
		a[1][1] = (function_2_f(xy.first, xy.second + h) - function_2_f(xy.first, xy.second - h)) / (2 * h);
		obr_mat(a);
		double tmp1 = function_1_f(xy.first, xy.second);
		double tmp2 = function_2_f(xy.first, xy.second);
		dx = -(a[0][0] * function_1_f(xy.first, xy.second) + a[0][1] * function_2_f(xy.first, xy.second));
		dy = -(a[1][0] * function_1_f(xy.first, xy.second) + a[1][1] * function_2_f(xy.first, xy.second));
		xy.first += dx;
		xy.second += dy;
		cout << ++i << ' ' << xy.first << ' ' << xy.second << endl;
		t = ((tmp_x - xy.first) * (tmp_x - xy.first) + (tmp_y - xy.second) * (tmp_y - xy.second));
	} while ( t> eps);
	cout << "=========" << endl;
	return xy;
}

int main()
{
	cin >> f;
	if (f == 1 || f == 2)
	{
		//pair<double, double> k = zeidel(200000, 100);
		pair<double, double> k = newton(zeidel(20000, 30000));
		//pair<double,double> k = newton(make_pair(11, 4));
		cout << k.first << ' ' << k.second << endl;
	}
	return 0;
}
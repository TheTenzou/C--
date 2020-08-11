#include <iostream>
#include <string>
#include <fstream>
#include <cmath>

using namespace std;

double func(double x) {
	return 2 * x * x - 12 * x + 19;
}

int main() {
	setlocale(LC_ALL, "rus");
	ofstream output;
	output.open("ans.txt");

	double a = 1;
	double b = 10;
	double e = 1;
	double l = b - a;

	output << "1) L_0 = [" << a << "," << b << "] - начальный интеpвал неопpеделенности." << endl << endl;

	int k = 0;
	output << "2) k = 0" << endl << endl;
	
	double x = a + (3 - sqrt(5)) / 2 * (b - a);
	double y = a + b - x;

	output << "3) Вычислить y_0 = " << y << endl;
	output << "             x_0 = " << x << endl << endl;

	double f_x = func(x);
	double f_y = func(y);

	output << "4) Вычислить f(y_0) = " << f_y << endl;
	output << "             f(x_0) = " << f_x << endl << endl;


	while (l>2*e) {
		//cout << "a = " << a << " f(a) = " << func(a) << endl;
		//cout << "x = " << x << " f(x) = " << func(x) << ' ' << f_x << endl;
		//cout << "y = " << y << " f(y) = " << func(y) << ' ' << f_y << endl;
		//cout << "b = " << b << " f(b) = " << func(b) << endl;
		//cout << "================" << endl;

		output << "5) Сравниваем f(x_" << k << ") и f(y_" << k << ")" << endl;

		if (f_x > f_y) {
			output << "а) f(x_" << k << ") > f(y_" << k << ")" << endl;

			a = x;
			x = y;
			f_x = f_y;
			y = a + b - x;
			f_y = func(y);

			output << "   a_" << k + 1 << " = x_" << k << " = " << a << endl;
			output << "   b_" << k + 1 << " = b_" << k << " = " << b << endl;
			output << "   x_" << k + 1 << " = y_" << k << " = " << x << endl;
			output << "   y_" << k + 1 << " = " << y << endl << endl;
		}
		else {
			output << "а) f(x_" << k << ") < f(y_" << k << ")" << endl;

			b = y;
			y = x;
			f_y = f_x;
			x = a + b - y;
			f_x = func(x);

			output << "   a_" << k + 1 << " = a_" << k << " = " << a << endl;
			output << "   b_" << k + 1 << " = y_" << k << " = " << b << endl;
			output << "   y_" << k + 1 << " = x_" << k << " = " << y << endl;
			output << "   x_" << k + 1 << " = " << x << endl << endl;
		}
		l = b - a;

		output << "6) l = " << l << endl;
		if (l < 2 * e) {
			output << "a) Процес поиска завершен" << endl; 
			output << "   Точка минимума x* принадлежит интервалу [" << a << "," << b << "]" << endl;
			output << "   В качестве пpиближенного pешения можно взять x* = " << (a + b) / 2 << endl;
		}
		else {
			k++;
			output << "б) Переходим к шагу 5" << endl;
			output << "   k = k + 1 = " << k << endl << endl;
		}
	}
	system("pause");
	output.close();
	return 0;
}

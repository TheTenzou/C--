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

	double a = 0;
	double b = 10;
	double e = 0.01;
	double l = b - a;
	output << "1) L_0 = [" << a << "," << b << "] - начальный интеpвал неопpеделенности." << endl;
	output << "   l = " << e << " допустимая длина конечного интеpвала." << endl << endl;


	// вычисляем номер нужного число фибоначи
	

	// вычисляем само число фибоначи
	int n = 0;
	int first = 1;
	int second = 0;
	int third = 0;
	while (third < l/e) {
		third = second + first;
		first = second;
		second = third;
		n++;
	}
	
	output << "2) Количество вычислений функции N = " << n << endl;
	output << "   И числа фибоначи F_n = " << second << endl;
	output << "                    F_n-1 = " << first << endl << endl;
	
	int k = 0;
	output << "3) k = 0" << endl << endl;

	int fib1 = second;
	int fib2 = first;


	// вы числяес внутрение точки

	double y = a + (double)fib2 / fib1 * (b - a);
	double x = a + b - y;

	output << "4) Вычислить y_0 = " << y << endl;
	output << "             x_0 = " << x << endl << endl;

	double f_y = func(y);
	double f_x = func(x);

	output << "5) Вычислить f(y_0) = " << f_y << endl;
	output << "             f(x_0) = " << f_x << endl << endl;
	
	while(k < n - 3) {
		output << "6) Сравниваем f(x_" << k << ") и f(y_" << k << ")" << endl;
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
		k++;
		output << "7) Пpовеpка выполнение условия окончания" << endl;
		if (k == n - 3) {
			output << "   отсутсвует точка нового вычисления функции" << endl << endl;
		}
		else {
			output << "   k =/= N - 3 переходим к шагу 6" << endl << endl;
		}
	}
	output << "   Установим x_n-2 = x_n-2 - e*1e-5" << endl;
	x -= e * 1e-5;
	f_x = func(x);
	output << "   Сравниваем f(x_n-2) и f(y_n-2)" << endl;
	if (f_x > f_y) {
		output << "   Точка минимума x* принадлежит интервалу [" << x << "," << b << "]" << endl;
		output << "   x* = " << (x + b) / 2 << endl;
	}
	else {
		output << "   Точка минимума x* принадлежит интервалу [" << a << "," << y << "]" << endl;
		output << "   x* = " << (a + y) / 2 << endl;
	}
	output.close();
	return 0;
}

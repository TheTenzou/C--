#include <iostream>
#include <fstream>

using namespace std;

double func(double x) {
	//return 2 * x * x - 12 * x + 19;
	return x * x + 48 * x + 19;
}

int main() {

	setlocale(LC_ALL, "rus");
	ofstream output;
	output.open("ans.txt");

	//Первый этап
	double x = 0;
	double t = 1;
	double delt;
	double x_n;
	double a = x - t;
	double b = x + t;
	int powerOfTwo = 2;

	output << "1) Задаем следуюшие параметры:" << endl;
	output << "   x_0 = " << x << endl;
	output << "   t = " << t << " > 0" << endl << endl;

	//Второй этап
	int k = 0;

	output << "2) k = 0" << endl << endl;

	//Третий этап
	double f_x_right = func(x - t);
	double f_x = func(x);
	double f_x_left = func(x + t);

	output << "3) Вычислим заначения функции вточках f(x_0-t) = " << f_x_right << endl;
	output << "                                      f(x_0)   = " << f_x << endl;
	output << "                                      f(x_0+t) = " << f_x_left << endl << endl;

	//Четвертый этап
	output << "4) Проверем условия окончания" << endl;
	if ((f_x_right >= f_x) && (f_x <= f_x_left)) {
		output << "a) f(x_0-t) >= f(x_0) <= f(x_0+t) то начальный интервал найден" << endl;
		output << "   [a,b] = [" << x - t << "," << x + t << "]" << endl << endl;
	}
	else if ((f_x_right <= f_x) && (f_x >= f_x_left)) {
		output << "б) f(x_0-t) <= f(x_0) >= f(x_0+t) то" << endl;
		output << "   Функция не унимодальная" << endl << endl;
	}
	else {
		output << "в) Условие окончание не выполнено переходи к шагу 5" << endl << endl;

		//Пятый этап

		output << "5) Определи велечину delt" << endl;
		if ((f_x_right >= f_x) & (f_x >= f_x_left)) {
			output << "а) f(x_0-t) >= f(x_0) > f(x_0+t)" << endl;
			delt = t;
			a = x;
			x_n = x + t;
			k = 1;
			output << "   delt = " << delt << endl;
			output << "   a_0 = " << a << endl;
			output << "   x_1 = " << x_n << endl;
			output << "   k = " << k << endl;
		}
		else {
			output << "б) f(x_0-t) <= f(x_0) < f(x_0+t)" << endl;
			delt = -t;
			b = x;
			x_n = x - t;
			k = 1;
			output << "   delt = " << delt << endl;
			output << "   b_0 = " << b << endl;
			output << "   x_1 = " << x_n << endl;
			output << "   k = " << k << endl;
		}
		for (;;) {
			//Шестой этап
			x = x_n;
			x_n = x_n + powerOfTwo * delt;
			powerOfTwo *= 2;

			output << "6) Найдем x_" << k + 1 << " = x_" << k << " + 2^k * delt = " << x_n << endl << endl;
			
			//Седмой этап
			output << "7) Проверим условие убывание" << endl;
			if (func(x_n) < func(x)) {
				if (delt == t) {
					output << "a) f(x_" << k + 1 << ") < f(x_" << k << ") и delt == t" << endl;
					a = x;
					output << "   то a_0 = " << a << endl << endl;
				}
				else {
					output << "a) f(x_" << k + 1 << ") < f(x_" << k << ") и delt == -t" << endl;
					b = x;
					output << "   то b_0 = " << b << endl << endl;
				}
			}
			else {
				output << "б) f(x_" << k + 1 << ") > f(x_" << k << ")" << endl;
				output << "   алгоритм завершается" << endl;
				if (delt == t) {
					b = x_n;
				}
				else {
					a = x_n;
				}
				output << "   [a,b] = [" << a << "," << b << "] - искомы начальный интервал неопределености" << endl;
				break;
			}
		}
	}

	output.close();
	return 0;
}
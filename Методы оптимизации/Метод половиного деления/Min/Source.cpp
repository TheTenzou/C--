#include <iostream>
#include <fstream>

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
	double a, b, x, y, z, l, f_x, f_y, f_z, e;
	int k = 0;
	cout << "a = ";
	cin >> a;
	cout << "b = ";
	cin >> b;
	cout << "e = ";
	cin >> e;

	output << "f(x) = x^2 - 72x+14" << endl;
	output << "e = " << e << endl << endl;


	output << "1." << k << ") Задается начальный интервал неопределености и требуемая точность точность" << endl;
	output << "     a." << k << " = " << a << endl;
	output << "     b_" << k << " = " << b << endl;
	l = abs(a - b);
	output << "     L_" << k << " = " << l << endl << endl;

	output << "2." << k << ") Устанаовливаем счетчик итераций" << endl << "     k = " << k << endl << endl;

	x = (a + b) / 2;
	f_x = func(x);

	output << "3." << k << ") Вычисляем середину отрезка и значение в этой точке" << endl;
	output << "     x_" << k << " = " << x << endl;
	output << "     f(x_" << k << ") = " << f_x << endl << endl;

	while (l > 2*e)
	{
		y = a + l / 4;
		output << "4." << k << ") Вычисляем Y и Z и значения в этих точках" << endl;
		output << "     y_" << k << " = " << y << ' ';
		f_y = func(y);
		output << "f(y_" << k << ") = " << f_y << endl;
		z = b - l / 4;
		output << "     z_" << k << " = " << z << ' ';
		f_z = func(z);
		output << "f(z_" << k << ") = " << f_z << endl << endl;

		if (f_y < f_x)
		{
			output << "5." << k << ") f(x_" << k << ") > f(y_" << k << ") Х принадлежит отрезку [" << a << ", " << x << "]" << endl;
			a = a;
			output << "     a_" << k + 1 << " = a_" << k << " = " << a << endl;
			b = x;
			output << "     b_" << k + 1 << " = x_" << k << " = " << x << endl;
			x = y;
			f_x = f_y;
			output << "     x_" << k + 1 << " = y_" << k << " = " << y << endl << endl;

			output << "     Перезодим на шаг 7" << endl << endl;
		}
		else
		{
			output << "5." << k << ") f(x_" << k << ") <= f(y_" << k << ") Перезодим на шаг 6" << endl << endl;

			if (f_x > f_z)
			{
				output << "6." << k << ") f(x_" << k << ") > f(z_" << k << ") Х принадлежит отрезку [" << x << ", " << b << "]" << endl;
				a = x;
				output << "     a_" << k + 1 << " = x_" << k << " = " << x << endl;
				b = b;
				output << "     b_" << k + 1 << " = b_" << k << " = " << b << endl;
				x = z;
				f_x = f_z;
				output << "     x_" << k + 1 << " = z_" << k << " = " << z << endl << endl;
			}
			else
			{
				output << "6." << k << ") f(x_" << k << ") <= f(z_" << k << ") Х принадлежит отрезку [" << y << ", " << z << "]" << endl;
				a = y;
				output << "     a_" << k + 1 << " = y_" << k << " = " << y << endl;
				b = z;
				output << "     b_" << k + 1 << " = z_" << k << " = " << z << endl;
				x = x;
				output << "     x_" << k + 1 << " = x_" << k << " = " << x << endl << endl;
			}
		}

		l = abs(a - b);
		output << "7." << k << ") L_" << k + 1 << " = " << l << endl;
		if (l > 2 * e)
		{
			output << "     L_" << k + 1 << " > 2*l Переходим к шагу 4" << endl;
			++k;
			output << "     k = " << k << endl << endl;
		}
		else
		{
			output << "     L_" << k + 1 << " < 2*l" << endl;
			output << "     Итерационный процес закончен ответ: " << x << endl;
		}
		output << "=========================================================================" << endl << endl;
	}

	output.close();
	return 0;
}
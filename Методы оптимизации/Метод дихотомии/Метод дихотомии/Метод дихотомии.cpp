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
	double a, b, y, z, l, f_y, f_z, e, d;
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
	output << "     L_" << k << " = " << l << endl;
	d = e * 0.1;
	output << "     d_" << k << " = " << d << endl << endl;

	output << "2." << k << ") Устанаовливаем счетчик итераций" << endl << "     k = " << k << endl << endl;

	while (l > 2 * e)
	{
		output << "3." << k << ") Вычисляем Y и Z и значение в этих точках" << endl;
		y = (a + b - d) / 2;
		output << "     y_" << k << " = " << y << endl;
		f_y = func(y);
		output << "     f(y_" << k << ") = " << f_y << endl << endl;
		z = y + d + d;
		output << "     z_" << k << " = " << z << endl;
		f_z = func(z);
		output << "     f(z_" << k << ") = " << f_z << endl << endl;

		if (f_y < f_z)
		{
			output << "4." << k << ") f(y_" << k << ") < f(z_" << k << ") Х принадлежит отрезку [" << a << ", " << z << "]" << endl;
			a = a;
			output << "     a_" << k + 1 << " = a_" << k << " = " << a << endl;
			b = z;
			output << "     b_" << k + 1 << " = x_" << k << " = " << z << endl << endl;
		}
		else
		{
			output << "4." << k << ") f(y_" << k << ") > f(z_" << k << ") Х принадлежит отрезку [" << y << ", " << b << "]" << endl;
			a = y;
			output << "     a_" << k + 1 << " = a_" << k << " = " << y << endl;
			b = b;
			output << "     b_" << k + 1 << " = x_" << k << " = " << b << endl << endl;
		}

		l = abs(a - b);
		output << "5." << k << ") L_" << k + 1 << " = " << l << endl;
		if (l > 2 * e)
		{
			output << "     L_" << k + 1 << " > 2*l Переходим к шагу 3" << endl;
			++k;
			output << "     k = " << k << endl << endl;
		}
		else
		{
			output << "     L_" << k + 1 << " < 2*l" << endl;
			output << "     Итерационный процес закончен ответ: " << (a + b)/2 << endl;
		}
		output << "=========================================================================" << endl << endl;
	}

	output.close();
	return 0;
}
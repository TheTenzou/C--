#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

// сама функция
double func(vector<double> x) {
	return 3 * x[0] * x[0] + 4 * x[1] * x[1] - 2 * x[0] * x[1] + x[0];
}

//длина вектора
double vectorLengh(vector<double>x) {
	double tmp = 0;
	for (int i = 0; i < x.size(); ++i) {
		tmp += x[i] * x[i];
	}
	return sqrt(tmp);
}

//вычисление градиента в точке
vector<double> gradient(vector<double> x) {
	vector<double> tmp;
	double h = 0.001;
	tmp.resize(x.size());
	for (int i = 0; i < tmp.size(); ++i) {
		vector<double> tmpV = x;
		tmpV[i] -= h;
		tmp[i] = (func(x) - func(tmpV)) / h;
	}
	return tmp;
}

//вычетение векторов
vector<double> subVectors(vector<double> x1, vector<double> x2) {
	vector<double> tmp;
	tmp.resize(x1.size());
	for (int i = 0; i < x1.size(); ++i) {
		tmp[i] = x1[i] - x2[i];
	}
	return tmp;
}

// умножение вектора на число
vector<double> multVectorByNumber(vector<double> x, double k) {
	vector<double> tmp;
	tmp.resize(x.size());
	for (int i = 0; i < tmp.size(); ++i) {
		tmp[i] = k * x[i];
	}
	return tmp;
}

// функция фи
double fi(vector<double> x_k, double t) {
	return func(subVectors(x_k, multVectorByNumber(gradient(x_k), t)));
}

// алгоритм свена
pair<double, double> sven(vector<double> xv) {

	//Первый этап
	double x = 0;
	double t = 1;
	double delt;
	double x_n;
	double a = x - t;
	double b = x + t;
	int powerOfTwo = 2;

	//Второй этап
	int k = 0;

	//Третий этап
	double f_x_right = fi(xv, x - t);
	double f_x = fi(xv, x);
	double f_x_left = fi(xv, x + t);

	//Четвертый этап
	if ((f_x_right >= f_x) && (f_x <= f_x_left)) {
		return make_pair(x - t, x + t);
	}
	else if ((f_x_right <= f_x) && (f_x >= f_x_left)) {
		cout << "Что-то пошло не так" << endl;
		exit;
	}
	else {
		//Пятый этап
		if ((f_x_right >= f_x) & (f_x >= f_x_left)) {
			delt = t;
			a = x;
			x_n = x + t;
			k = 1;
		}
		else {
			delt = -t;
			b = x;
			x_n = x - t;
			k = 1;
		}
		for (;;) {
			//Шестой этап
			x = x_n;
			x_n = x_n + powerOfTwo * delt;
			powerOfTwo *= 2;

			//Седмой этап
			if (fi(xv, x_n) < fi(xv, x)) {
				if (delt == t) {
					a = x;
				}
				else {
					b = x;
				}
			}
			else {
				if (delt == t) {
					b = x_n;
				}
				else {
					a = x_n;
				}
				break;
			}
		}
	}

	return make_pair(a, b);
}

// дихотомия
double dihotimiya(vector<double> x_k) {
	double a;
	double b;
	double y;
	double z;
	double l;
	double f_y;
	double f_z;
	double e;
	double d;
	int k = 0;
	// todo

	pair<double, double> tmp = sven(x_k);
	a = tmp.first;
	b = tmp.second;

	l = abs(a - b);

	e = 0.1;
	d = e * 0.1;;

	for(;;)	{
		y = (a + b - d) / 2;
		f_y = fi(x_k, y);
		z = y + 2*d;
		f_z = fi(x_k, z);

		if (f_y < f_z) {
			b = z;
		}
		else {
			a = y;
		}

		l = abs(a - b);
		if (l > 2 * e) {
			++k;
		}
		else{
			break;
		}
	}

	return (a + b) / 2;
}

int main() {

	setlocale(LC_ALL, "rus");
	ofstream output;
	output.open("ans.txt");

	vector<double> x;
	x.resize(2);
	x[0] = 2;
	x[1] = 1.5;
	double e1 = 0.01;
	double e2 = 0.1;
	double m = 1000;
	bool priv = false;

	output << "1_0) Задаем x_0 = {";
	for (int i = 0; i < x.size() - 1; ++i) {
		output << x[i] << ", ";
	}
	output << x[x.size() - 1] << "}" << endl;
	output << "     e_1 = " << e1 << endl;
	output << "     e_2 = " << e2 << endl;
	output << "     M = " << m << " предельное число итераций" << endl << endl;

	int k = 0;
	output << "2_0) k = " << k << endl << endl;

	for (;;) {
		output << "3_" << k << ") Вычислим градиент в точке" << endl;

		vector<double> grad = gradient(x);
		output << "     grad(f(x_" << k << ")) = {";
		for (int i = 0; i < grad.size() - 1; ++i) {
			output << grad[i] << ", ";
		}
		output << grad[grad.size() - 1] << "}" << endl << endl;

		output << "4_" << k << ") Проверим выполнение критерия окончания ||grad(f(x_" << k << ")|| < e_1" << endl;
		if (vectorLengh(grad) < e1) {
			output << "     ||grad(f(x_" << k << ")|| = " << vectorLengh(grad) << " < " << e1 << endl;
			output << "     Критерий выпонен x* = x_" << k << endl << endl;
			break;
		}
		else {
			output << "     ||grad(f(x_" << k << ")|| = " << vectorLengh(grad) << " > " << e1 << endl;
			output << "     Критерий не выпонен переходим к шагу 5" << endl << endl;
		}

		output << "5_" << k << ") Проверияем выполнение неравенства k >= M" << endl;
		if (k >= m) {
			output << "     k = " << k << " > " << m << endl;
			output << "     Превышено допустимое число итераций" << endl;
			output << "     Неравенство выполнено x* = x_" << k << endl << endl;
			break;
		}
		else {
			output << "     k = " << k << " < " << m << endl;
			output << "     Критерий не выпонен переходим к шагу 6" << endl << endl;
		}

		output << "6_" << k << ") Вычисляем величину шага t_" << k << endl;
		double tK = dihotimiya(x);
		output << "     t_" << k << " = " << tK << endl << endl;

		vector<double> xNext = subVectors(x, multVectorByNumber(grad, tK));
		output << "7_" << k << ") Вычисляем x_" << k + 1 << " = {";
		for (int i = 0; i < xNext.size() - 1; ++i) {
			output << xNext[i] << ", ";
		}
		output << xNext[xNext.size() - 1] << "}" << endl << endl;

		output << "8_" << k << ") Проверяем условия ||x_" << k + 1 << " - x_" << k << "|| < e_2 |f(x_" << k + 1 << ") - f(x_" << k << ")| < e_2" << endl;
		if (vectorLengh(subVectors(xNext, x)) < e2 && abs(func(xNext) - func(x)) < e2) {
			if (priv) {
				output << "     ||x_" << k + 1 << " - x_" << k << "|| = " << vectorLengh(subVectors(xNext, x)) << " < " << e2 << endl;
				output << "     |f(x_" << k + 1 << ") - f(x_" << k << ")| = " << abs(func(xNext) - func(x)) << " < " << e2 << endl;
				output << "     а) Оба условия выполнены на этом и на придыдушем шаге" << endl;
				output << "     x* = {";
				for (int i = 0; i < xNext.size() - 1; ++i) {
					output << xNext[i] << ", ";
				}
				output << xNext[xNext.size() - 1] << "}" << endl << endl;
				break;
			}
			priv = true;
			output << "     ||x_" << k + 1 << " - x_" << k << "|| = " << vectorLengh(subVectors(xNext, x)) << " < " << e2 << endl;
			output << "     |f(x_" << k + 1 << ") - f(x_" << k << ")| = " << abs(func(xNext) - func(x)) << " < " << e2 << endl;
			output << "     б) Условия выполнились только на этом шаге" << endl << endl;
		} 
		else {
			output << "     ||x_" << k + 1 << " - x_" << k << "|| = " << vectorLengh(subVectors(xNext, x)) << " > " << e2 << endl;
			output << "     |f(x_" << k + 1 << ") - f(x_" << k << ")| = " << abs(func(xNext) - func(x)) << " > " << e2 << endl;
			output << "     в) Условия не выполнились" << endl << endl;
		}
		x = xNext;
		++k;
		output << "===============================================================================" << endl << endl;

	}

	output.close();
	system("pause");
	return 0;
}
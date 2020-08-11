#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

// сама функция
double func(vector<double> x) {
	//return 3 * x[0] * x[0] + 4 * x[1] * x[1] - 2 * x[0] * x[1] + x[0];
	//return x[0] * x[0] * x[1] * x[1] + 2 * x[0] * x[1] + x[1] * x[1] + 2 * x[1] + 3;
	return 3 * x[0] * x[0] + 4 * x[1] * x[1] - 2 * x[0] * x[1] + x[0] + 16 * pow(x[0] + x[1] - 1, 2) / 2;
}

vector<vector<double>> hMatrix(vector<double> x) {
	vector<vector<double>> tmp;
	double h = 0.1;
	tmp.resize(x.size());
	for (int i = 0; i < tmp.size(); ++i) {
		tmp[i].resize(x.size());
		for (int j = 0; j < tmp[i].size(); ++j) {
			vector<double> tmpV1 = x;
			tmpV1[i] += h;
			tmpV1[j] += h;
			vector<double> tmpV2 = x;
			tmpV2[i] += h;
			vector<double> tmpV3 = x;
			tmpV3[j] += h;
			tmp[i][j] = (func(tmpV1) - func(tmpV3) - func(tmpV2) + func(x)) / pow(h, 2);
		}
	}
	return tmp;
}

vector<vector<double>> invMatrix(vector<vector<double>> mx) {
	vector<vector<double>> tmp = mx;
	tmp[0][0] = mx[1][1] / (mx[0][0]*mx[1][1]-mx[1][0]*mx[0][1]);
	tmp[0][1] = -mx[0][1] / (mx[0][0] * mx[1][1] - mx[1][0] * mx[0][1]);
	tmp[1][0] = -mx[1][0] / (mx[0][0] * mx[1][1] - mx[1][0] * mx[0][1]);
	tmp[1][1] = mx[0][0] / (mx[0][0] * mx[1][1] - mx[1][0] * mx[0][1]);
	return tmp;
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

vector<double> addVectors(vector<double> x1, vector<double> x2) {
	vector<double> tmp;
	tmp.resize(x1.size());
	for (int i = 0; i < x1.size(); ++i) {
		tmp[i] = x1[i] + x2[i];
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

vector<double> multMatrixByVector(vector<vector<double>> m, vector<double> v) {
	vector<double> tmp;
	tmp.resize(v.size());
	for (int i = 0; i < m.size(); ++i) {
		for (int j = 0; j < m[i].size(); ++j) {
			tmp[i] += m[i][j] * v[j];
		}
	}
	return tmp;
}



int main() {

	setlocale(LC_ALL, "rus");
	ofstream output;
	output.open("ans.txt");

	vector<double> xk;
	xk.resize(2);
	xk[0] = 2;
	xk[1] = 1.5;
	double e1 = 0.01;
	double e2 = 0.1;
	double m = 1000;
	bool priv = false;

	output << "Находим миниму функции f(x,y)= 3x^2 + 4y^2 - 2xy + x" << endl << endl;

	output << "1_0) Задаем x_0 = {";
	for (int i = 0; i < xk.size() - 1; ++i) {
		output << xk[i] << ", ";
	}
	output << xk[xk.size() - 1] << "}" << endl;
	output << "     e_1 = " << e1 << endl;
	output << "     e_2 = " << e2 << endl;
	output << "     M = " << m << " предельное число итераций" << endl;
	output << "     f(x_0) = " << func(xk) << endl << endl;

	int k = 0;
	output << "2_0) k = " << k << endl << endl;

	vector<double> dK;

	for (;;) {
		output << "3_" << k << ") Вычисляем градиент в точке" << endl;

		vector<double> grad = gradient(xk);
		output << "     grad(f(x_" << k << ")) = {";
		for (int i = 0; i < grad.size() - 1; ++i) {
			output << grad[i] << ", ";
		}
		output << grad[grad.size() - 1] << "}" << endl << endl;

		output << "4_" << k << ") Провереям выполнение критерия окончания ||grad(f(x_" << k << ")|| < e_1" << endl;
		if (vectorLengh(grad) < e1) {
			output << "     ||grad(f(x_" << k << ")|| = " << vectorLengh(grad) << " < " << e1 << endl;
			output << "     Критерий выполнен x* = x_" << k << " = {";
			for (int i = 0; i < xk.size() - 1; ++i) {
				output << xk[i] << ", ";
			}
			output << xk[xk.size() - 1] << "}" << endl << endl;
			break;
		}
		else {
			output << "     ||grad(f(x_" << k << ")|| = " << vectorLengh(grad) << " > " << e1 << endl;
			output << "     Критерий не выполнен переходим к шагу 5" << endl << endl;
		}

		output << "5_" << k << ") Проверяем выполнение неравенства k >= M" << endl;
		if (k >= m) {
			output << "     k = " << k << " > " << m << endl;
			output << "     Превышено допустимое число итераций" << endl;
			output << "     Неравенство выполнено x* = x_" << k << endl << endl;
			break;
		}
		else {
			output << "     k = " << k << " < " << m << endl;
			output << "     Критерий не выполнен переходим к шагу 6" << endl << endl;
		}

		output << "6_" << k << ") Вычисляем матрицу Н(х_" << k << ")" << endl;
		vector<vector<double>> hmatrix = hMatrix(xk);
		output << "     ";
		for (int i = 0; i < hmatrix.size(); ++i) {
			for (int j = 0; j < hmatrix[i].size(); ++j) {
				output << hmatrix[i][j] << ' ';
			}
			output << endl << "     ";
		}
		output << endl;

		output << "7_" << k << ") Вычисляем Обратную матрицу Н^-1(x) = " << endl;
		vector<vector<double>> hObr = invMatrix(hmatrix);
		output << "     ";
		for (int i = 0; i < hObr.size(); ++i) {
			for (int j = 0; j < hObr[i].size(); ++j) {
				output << hObr[i][j] << ' ';
			}
			output << endl << "     ";
		}
		output << endl;

		int flag = 0;
		output << "8_" << k << ") Проверяем условие Н^-1(x) > 0" << endl;
		if ((hObr[0][0] > 0) && (hObr[0][0] * hObr[1][1] - hObr[0][1] * hObr[1][0] > 0)) {
			output << "     Условие выполнилось переходим к шагу 9" << endl << endl;

			dK = multVectorByNumber(multMatrixByVector(hObr, grad), -1);
			output << "9_" << k << ") Вычисляем d_" << k << " = {";
			for (int i = 0; i < dK.size() - 1; ++i) {
				output << dK[i] << ", ";
			}
			output << dK[dK.size() - 1] << "}" << endl << endl;
			flag = 1;
		}
		else {
			dK = multVectorByNumber(grad, -1);
			output << "     d_" << k << " = {";
			for (int i = 0; i < dK.size() - 1; ++i) {
				output << dK[i] << ", ";
			}
			output << dK[dK.size() - 1] << "}" << endl << endl;
			output << "     Переходим к шагу 10" << endl << endl;
		}

		vector<double> xNext;
		if (flag) {
			xNext = addVectors(xk, dK);
		}
		else {
			double t = 1;
			while (t >= -1) {
				xNext = addVectors(xk, multVectorByNumber(dK, t));
				if (func(xk) > func(xNext)) {
					break;
				}
				t -= 0.01;
				//output << "      f(" << xNext[0] <<", " << xNext[1] << ") = " << func(xNext) << endl;
			}
			if (func(xk) < func(xNext)) {
				output << endl << "     Что-то пошло не так" << endl;
				return 0;
			}
		}
		output << "10_" << k << ") Вычисляем x_" << k + 1 << endl;
		
		output << "      x_" << k + 1 << " = {";
		for (int i = 0; i < xNext.size() - 1; ++i) {
			output << xNext[i] << ", ";
		}
		output << xNext[xNext.size() - 1] << "}" << endl << endl;
		
		output << "11_" << k << ") Проверяем условия ||x_" << k + 1 << " - x_" << k << "|| < e_2 |f(x_" << k + 1 << ") - f(x_" << k << ")| < e_2" << endl;
		if (vectorLengh(subVectors(xNext, xk)) < e2 && abs(func(xNext) - func(xk)) < e2) {
			if (priv) {
				output << "      ||x_" << k + 1 << " - x_" << k << "|| = " << vectorLengh(subVectors(xNext, xk)) << " < " << e2 << endl;
				output << "      |f(x_" << k + 1 << ") - f(x_" << k << ")| = " << abs(func(xNext) - func(xk)) << " < " << e2 << endl;
				output << "      а) Оба условия выполнены на этом и на предыдушем шаге" << endl;
				output << "      x* = {";
				for (int i = 0; i < xNext.size() - 1; ++i) {
					output << xNext[i] << ", ";
				}
				output << xNext[xNext.size() - 1] << "}" << endl << endl;
				break;
			}
			priv = true;
			output << "      ||x_" << k + 1 << " - x_" << k << "|| = " << vectorLengh(subVectors(xNext, xk)) << " < " << e2 << endl;
			output << "      |f(x_" << k + 1 << ") - f(x_" << k << ")| = " << abs(func(xNext) - func(xk)) << " < " << e2 << endl;
			output << "      б) Условия выполнились только на этом шаге" << endl << endl;
		}
		else {
			if (vectorLengh(subVectors(xNext, xk)) < e2) {
				output << "      ||x_" << k + 1 << " - x_" << k << "|| = " << vectorLengh(subVectors(xNext, xk)) << " < " << e2 << endl;
			}
			else {
				output << "      ||x_" << k + 1 << " - x_" << k << "|| = " << vectorLengh(subVectors(xNext, xk)) << " > " << e2 << endl;
			}
			if (abs(func(xNext) - func(xk)) < e2) {
				output << "      |f(x_" << k + 1 << ") - f(x_" << k << ")| = " << abs(func(xNext) - func(xk)) << " < " << e2 << endl;
			}
			else {
				output << "      |f(x_" << k + 1 << ") - f(x_" << k << ")| = " << abs(func(xNext) - func(xk)) << " > " << e2 << endl;
			}

			output << "      в) Условия не выполнились" << endl << endl;
			priv = false;
		}
		xk = xNext;
		++k;
		output << "===============================================================================" << endl << endl;

	}

	output.close();
	system("pause");
	return 0;
}
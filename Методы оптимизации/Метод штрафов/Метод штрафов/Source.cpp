#include <iostream> 
#include <fstream>
#include <vector>
#include <string>

using namespace std;


double fun(vector<double> x) {
	return 3 * pow(x[0], 2) + 4 * pow(x[1], 2) - 2 * x[0] * x[1] + x[0];
}

double border(vector<double> x) {
	return x[0] + x[1] - 1;
}

double p(vector<double> x, double r) {
	return r * pow(border(x), 2)/2;
}

double F(vector<double> x, double r) {
	return fun(x) + p(x, r);
}

vector<vector<double>> hMatrix(vector<double> x, double r) {
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
			tmp[i][j] = (F(tmpV1, r) - F(tmpV3, r) - F(tmpV2, r) + F(x, r)) / pow(h, 2);
		}
	}
	return tmp;
}

vector<vector<double>> invMatrix(vector<vector<double>> mx) {
	vector<vector<double>> tmp = mx;
	tmp[0][0] = mx[1][1] / (mx[0][0] * mx[1][1] - mx[1][0] * mx[0][1]);
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
vector<double> gradient(vector<double> x, double r) {
	vector<double> tmp;
	double h = 0.001;
	tmp.resize(x.size());
	for (int i = 0; i < tmp.size(); ++i) {
		vector<double> tmpV = x;
		tmpV[i] -= h;
		tmp[i] = (F(x, r) - F(tmpV, r)) / h;
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



vector<double> min(vector<double> xk, double r) {
	double e1 = 0.01;
	double e2 = 0.1;
	double m = 1000;
	bool priv = false;


	int k = 0;

	vector<double> dK;

	for (;;) {
		vector<double> grad = gradient(xk, r);

		if (vectorLengh(grad) < e1) {
			return xk;
			break;
		}

		if (k >= m) {
			return xk;
			break;
		}

		vector<vector<double>> hmatrix = hMatrix(xk, r);

		vector<vector<double>> hObr = invMatrix(hmatrix);

		int flag = 0;
		if ((hObr[0][0] > 0) && (hObr[0][0] * hObr[1][1] - hObr[0][1] * hObr[1][0] > 0)) {

			dK = multVectorByNumber(multMatrixByVector(hObr, grad), -1);
			flag = 1;
		}
		else {
			dK = multVectorByNumber(grad, -1);
		}

		vector<double> xNext;
		if (flag) {
			xNext = addVectors(xk, dK);
		}
		else {
			double t = 1;
			while (t >= -1) {
				xNext = addVectors(xk, multVectorByNumber(dK, t));
				if (F(xk, r) > F(xNext, r)) {
					break;
				}
				t -= 0.01;
			}
			if (F(xk, r) < F(xNext, r)) {
				cout << endl << "     Что-то пошло не так" << endl;
				exit(0);
			}
		}

		if (vectorLengh(subVectors(xNext, xk)) < e2 && abs(F(xNext, r) - F(xk, r)) < e2) {
			if (priv) {
				return xNext;
				break;
			}
			priv = true;
		}
		else {
			priv = false;
		}
		xk = xNext;
		++k;

	}
	
}

int main() {

	setlocale(LC_ALL, "rus");
	ofstream output;
	output.open("ans.txt");

	vector<double> x;
	x.resize(2);
	x[0] = 1;
	x[1] = 1;
	double r = 1;
	double c = 2;
	double eps = 0.001;
	int k = 0;

	output << " f(x) = 3x^2 + 3y^2 - xy + x" << endl << endl;

	output << "1_0) Задаем x_0 = {";
	for (int i = 0; i < x.size() - 1; ++i) {
		output << x[i] << ", ";
	}
	output << x[x.size() - 1] << "} - начальная точка" << endl;
	output << "     r_0 = " << r << " начальное значение параметра штрафа" << endl;
	output << "     C = " << c << "число для увеличения параметра" << endl;
	output << "     e = " << eps << "  малое число для остановки алгоритма" << endl;
	output << "     k = " << k << endl << endl;

	for (;;) {
		output << "2_" << k << ") Составим вспомогательную функцию" << endl;
		output << "     F(x,r_" << k << ") = f(x) + r_" << k << "/2 * (sum(g_i(x)^2) + sum(g_i+(x)^2)" << endl << endl;

		output << "3_" << k << ") Найдем точку x* безусловного минимума функции F(x,r_" << k << ")" << endl << endl;
		vector<double> xN = min(x, r);
		output << "     x* = {";
		for (int i = 0; i < xN.size() - 1; ++i) {
			output << xN[i] << ", ";
		}
		output << xN[xN.size() - 1] << "}" << endl;
		double pv = p(xN, r);
		output << "     Вычисляем P(x*, r_" << k << ") = " << pv << endl;
		output << "     f(x) " << fun(xN) << endl << endl;

		output << "4_" << k << ") Проверка условие окончания" << endl;
		if (pv <= eps) {
			output << "     a) P(x*(r_" << k << "),r_" << k << ") = " << pv << " <= " << eps << " процесс поиска закончен" << endl;
			output << "     Ответ x* = {";
			for (int i = 0; i < xN.size() - 1; ++i) {
				output << xN[i] << ", ";
			}
			output << xN[xN.size() - 1] << "}" << endl;
			output << "     f(x) = " << fun(x) << endl;
			break;
		}
		else {
			output << "     б) P(x*(r_k),r_" << k << ") = " << pv << " > " << eps <<" то" << endl;
			output << "     r_" << k + 1 << " = C*r_" << k << " = " << c << "*" << r << " = " << c * k << endl;
			output << "     x_" << k + 1 << " = x*(r_" << k << ") = {";
			for (int i = 0; i < xN.size() - 1; ++i) {
				output << xN[i] << ", ";
			}
			output << xN[xN.size() - 1] << "}" << endl;
			output << "     k = k + 1 = " << k + 1 << endl;
			output << "     Переходим к шагу 2" << endl << endl;
			r = r * c;
			++k;
			x = xN;
		}
	}

	output.close();
	system("pause");
	return 0;
}
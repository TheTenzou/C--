#include <iostream> 
#include <fstream>
#include <string>
#include <vector>
#include <time.h>

using namespace std;

// метод кауса для решения СЛАУ
vector<double> gauss(vector<vector<double>> a, vector<double> y, int n) {

	vector<double> x;
	double max;
	int k, index;
	const double eps = 0.00001;
	x.resize(n);
	k = 0;
	while (k < n) {
		max = abs(a[k][k]);
		index = k;

		for (int i = k + 1; i < n; i++) {
			if (abs(a[i][k]) > max) {
				max = abs(a[i][k]);
				index = i;
			}
		}

		if (max < eps) {
			cout << "no solutions ";
			x.resize(n, 0);
			return x;
		}

		for (int j = 0; j < n; j++) {
			double temp = a[k][j];
			a[k][j] = a[index][j];
			a[index][j] = temp;
		}

		double temp = y[k];
		y[k] = y[index];
		y[index] = temp;

		for (int i = k; i < n; i++) {
			double temp = a[i][k];
			if (abs(temp) < eps) {
				continue;
			}

			for (int j = 0; j < n; j++) {
				a[i][j] = a[i][j] / temp;
			}

			y[i] = y[i] / temp;
			if (i == k) {
				continue;
			}

			for (int j = 0; j < n; j++) {
				a[i][j] = a[i][j] - a[k][j];
			}
			y[i] = y[i] - y[k];
		}
		k++;
	}
	for (k = n - 1; k >= 0; k--) {
		x[k] = y[k];
		for (int i = 0; i < k; i++) {
			y[i] = y[i] - a[i][k] * x[k];
		}
	}
	return x;
}

// длинна вектора
double lenth(vector<double> a) {
	double tmp = 0;
	for (int i = 0; i < a.size(); ++i) {
		tmp += a[i] * a[i];
	}
	return sqrt(tmp);
}

// нормализовать вектор
vector<double> norm(vector<double> a) {

	double len = lenth(a);

	for (int i = 0; i < a.size(); ++i) {
		a[i] = a[i] / len;
	}

	return a;
}

//умножение матрицы на вектор
vector<double> multMatrixVector(vector<vector<double>> a, vector<double> x) {

	vector<double> tmp;
	tmp.resize(x.size(), 0);
	for (int i = 0; i < x.size(); ++i) {
		for (int j = 0; j < a[i].size(); ++j) {
			tmp[i] += a[i][j] * x[j];
		}

	}
	return tmp;
}

int main() {
	cout << "Enter file name" << endl;
	string fileName;
	cin >> fileName;
	ifstream file;
	file.open(fileName + ".txt");

	int n; // Порядок матрицы
	vector<vector<double>> matrix; // Матрица
	vector<double> x; // приблеженый вектор
	vector<double> xPred; // приблеженый вектор
	double e = 1e-5; // Конствнта отличимости от 0
	n = 3;
	file >> n;
	
	// Случайное начальное приближение
	x.resize(n);
	srand(time(0));
	for (int i = 0; i < x.size(); ++i) {
		x[i] = rand();
	}
	x = norm(x);
	xPred = x;

	//ввод матрицы
	matrix.resize(n);
	for (int i = 0; i < matrix.size(); ++i) {
		matrix[i].resize(n);
		for (int j = 0; j < matrix[i].size(); ++j) {
			file >> matrix[i][j];
			
		}
	}
	file.close();

	// Степеной способ
	double lam = 0;
	double lamPred = 0;

	// находим первое приближение первого собственного векторо
	x = multMatrixVector(matrix, xPred);
	// находим первое приближение первого собственного чила
	int tempCount = 0;
	for (int i = 0; i < x.size(); ++i) {
		if (abs(xPred[i]) > e) {
			double tmp = x[i] / xPred[i];
			lam += tmp;
			++tempCount;
		}
	}
	lam = lam / tempCount;

	x = norm(x);

	while (abs(lam - lamPred) > 0.7) {
		xPred = x;
		// находим новое приближение первого собственного векторо
		x = multMatrixVector(matrix, x);
		lamPred = lam;
		// находим новое приближение первого собственного чила
		lam = 0;
		tempCount = 0;
		for (int i = 0; i < x.size(); ++i) {
			if (abs(xPred[i]) > e) {
				lam += x[i] / xPred[i];
				++tempCount;
			}
		}
		lam /= tempCount;
		x = norm(x);

	}
	//приближени собственого вектора
	vector<double> firstVector = x;

	// три собственных вектора для второго собственого чтсла
	xPred = multMatrixVector(matrix, xPred);
	x = multMatrixVector(matrix, xPred);
	vector<double> xNext = multMatrixVector(matrix, x);

	double lam2 = 0;
	tempCount = 0;
	for (int i = 0; i < x.size(); ++i) {
		if (abs(x[i] - lam * xPred[i]) > 1e-5) {
			lam2 += (xNext[i] - lam * x[i]) / (x[i] - lam * xPred[i]);
			tempCount++;
		}
	}
	cout << endl;
	lam2 /= tempCount;

	// обратные итерации для первого собственого числа и вектора

	vector<vector<double>> matrix1 = matrix;
	for (int i = 0; i < n; ++i) {
		matrix1[i][i] -= lam;
	}

	double lamObr = 0;
	double lamObrPred = 0;

	xPred = firstVector;
	x = multMatrixVector(matrix, xPred);
	tempCount = 0;
	for (int i = 0; i < x.size(); ++i) {
		if (abs(xPred[i]) > e) {
			double tmp = xPred[i] / x[i];
			lamObr += tmp;
			++tempCount;
		}
	}
	lamObr /= tempCount;

	x = norm(x);

	while (abs(lamObr - lamObrPred) > 0.0001) {
		xPred = x;
		x = gauss(matrix1, xPred,n);
		lamObrPred = lamObr;
		lamObr = 0;
		tempCount = 0;
		for (int i = 0; i < x.size(); ++i) {
			if (abs(x[i]) > e) {
				lamObr += xPred[i] / x[i];
				++tempCount;
			}
		}
		lamObr /= tempCount;
		x = norm(x);

	}

	firstVector = x;

	// обратные итерации первое собственое число и вектор
	vector<vector<double>> matrix2 = matrix;
	for (int i = 0; i < n; ++i) {
		matrix2[i][i] -= lam2;
	}

	double lamObr2 = 0;
	double lamObrPred2 = 0;

	for (int i = 0; i < x.size(); ++i) {
		x[i] = rand();
	}
	x = norm(x);
	xPred = x;
	x = multMatrixVector(matrix, xPred);
	tempCount = 0;
	for (int i = 0; i < x.size(); ++i) {
		if (abs(xPred[i]) > e) {
			double tmp = xPred[i] / x[i];
			lamObr2 += tmp;
			++tempCount;
		}
	}
	lamObr2 /= tempCount;

	x = norm(x);

	while (abs(lamObr2 - lamObrPred2) > 0.0001) {
		xPred = x;
		x = gauss(matrix2, xPred, n);
		lamObrPred2 = lamObr2;
		lamObr2 = 0;
		tempCount = 0;
		for (int i = 0; i < x.size(); ++i) {
			if (abs(x[i]) > e) {
				lamObr2 += xPred[i] / x[i];
				++tempCount;
			}
		}
		lamObr2 /= tempCount;
		x = norm(x);
	}
	//вывод
	vector<double> secondVector = x;
	cout << "lam = " << lam + lamObr << endl;
	cout << "vector 1 {";
	for (int i = 0; i < firstVector.size(); ++i) {
		cout << firstVector[i] << ", ";
	}
	cout << "}" << endl;
	cout << "lam2 = " << lam2 + lamObr2 << endl;
	cout << "vector 2 {";
	for (int i = 0; i < secondVector.size(); ++i) {
		cout << secondVector[i] << ", ";
	}
	cout << "}" << endl;
	system("pause");
	return 0;
}
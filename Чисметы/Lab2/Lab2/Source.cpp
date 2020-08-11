#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <time.h>

using namespace std;


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

		if (max < eps){
			cout << "no solutions ";
			x.resize(n,0);
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

		for (int i = k; i < n; i++)	{
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
	for (k = n - 1; k >= 0; k--){
		x[k] = y[k];
		for (int i = 0; i < k; i++) {
			y[i] = y[i] - a[i][k] * x[k];
		}
	}
	return x;
}


//матрица на число
vector<double> mult_m_v(vector<vector<double>> a, vector<double> x) {

	vector<double> tmp;
	tmp.resize(x.size(), 0);
	for (int i = 0; i < x.size(); ++i) {
		for (int j = 0; j < x.size(); ++j) {
			tmp[i] += a[i][j] * x[j];
		}

	}
	return tmp;
}

double mult_v(vector<double> a, vector<double> b) {

	double tmp = 0;

	for (int i = 0; i < a.size(); ++i) {
		tmp += a[i] * b[i];
	}
	return tmp;
}

// разность векторов
vector<double> sub_v(vector<double> a, vector<double> b) {
	for (int i = 0; i < a.size(); ++i) {
		a[i] -= b[i];
	}

	return a;
}


double norma(vector<double> a) {
	double tmp = a[0];

	for (int i = 0; i < a.size(); ++i) {
		if (tmp < a[i]) {
			tmp = a[i];
		}
	}

	return tmp;
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

vector<double> invert(vector<double> a) {

	for (int i = 0; i < a.size(); ++i) {
		a[i] *=-1;
	}

	return a;
}

int main() {
	cout << "enter file name" << endl;
	string filename;
	cin >> filename;
	ifstream file;
	file.open(filename + ".txt");

	int n; // порядок матрицы
	vector<vector<double>> m; // матрица
	vector<double> x_1, x; // приблеженый вектор
	double e = 1e-2; //точность
	file >> n;
	m.resize(n);
	x_1.resize(n);
	srand(time(0));
	for (int i = 0; i < x_1.size(); ++i) {
		x_1[i] = rand();
	}
	x_1 = norm(x_1);
	x = x_1;


	//ввод
	for (int i = 0; i < n; ++i) {
		m[i].resize(n);
		for (int j = 0; j < n; ++j) {
			file >> m[i][j];
		}
	}

	//степенной способ
	double lam = 0;
	double lam_pred = 0;
	
	x_1 = mult_m_v(m, x);

	int tempCount = 0;
	lam = 0;
	for (int i = 0; i < x_1.size(); ++i) {
		if (abs(x[i]) > e) {
			lam += x_1[i] / x[i];
			++tempCount;
			//cout << "x_1 = " << x_1[i] << endl;
			//cout << "x = " << x[i] << endl;
		}
	}
	//cout << lam << endl;
	//cout << tempCount << endl;
	lam = lam / tempCount;
	//cout << lam << endl;
	//cout << "===" << endl;
	x_1 = norm(x_1);

	while (abs(lam - lam_pred) > 0.2) {
		x = x_1;
		x_1 = mult_m_v(m, x_1);
		

		lam_pred = lam;

		int tempCount = 0;
		lam = 0;
		for (int i = 0; i < x_1.size(); ++i) {
			if (abs(x[i]) > e) {
				lam += x_1[i] / x[i];
				++tempCount;
				//cout << "+" << endl;
				//cout << "x_1 = " << x_1[i] << endl;
				//cout << "x = " << x[i] << endl;
			}
		}

		lam = lam / tempCount;
		cout << "lam = " << lam << endl;

		x_1 = norm(x_1);

		if (x[0] * x_1[0] < 0) {
			x_1 = invert(x_1);
		}
	}
	x = x_1;
	x_1 = mult_m_v(m, x_1);


	//считаем лямда 
	//cout << "====" << endl;
	//cout <<"lam1 = " << lam << endl;

	
	//считаем лямда 2
	x = mult_m_v(m, x);
	//x = norm(x);
	x_1 = mult_m_v(m, x);
	vector<double> x_2 = mult_m_v(m, x_1);

	vector<double> x_norm = norm(x);
	vector<double> x_1_norm = norm(x_1);
	
	/*cout << "v1" << endl;
	for (int i = 0; i < x.size(); ++i) {
		cout << x[i] << ' ';
	}
	cout << endl;

	cout << "v2" << endl;
	for (int i = 0; i < x_1.size(); ++i) {
		cout << x_1[i] << ' ';
	}
	cout << endl;
	cout << "v3" << endl;
	for (int i = 0; i < x_2.size(); ++i) {
		cout << x_2[i] << ' ';
	}*/
	
	cout << endl;
	cout << "lam = " << lam << endl;
	double lam_2 = 0;
	int cout_lam_2 = 0;
	for (int i = 0; i < x_1.size(); ++i){
		//cout << (x_2[i] - lam * x_1[i])/(x_1[i] - lam * x[i]) << ' ';
		
		if(abs(x_1[i] - lam * x[i]) > 1e-5) {
			lam_2 += (x_2[i] - lam * x_1[i]) / (x_1[i] - lam * x[i]);
			cout_lam_2++;
			//cout << "*" << endl;
		}
	}

	cout << endl;
	lam_2 /= cout_lam_2;
	cout << "lam_2 = " << lam_2 << endl;

	//обратные итерации
	vector<vector<double>> b = m;
	for (int i = 0; i < n; ++i) {
		b[i][i] -= lam;
	}


	vector<double> y = norm(x_1);
	vector<double> y_1 = gauss(b, y, n);
	y_1 = norm(y_1);

	while (lenth(sub_v(y_1, y)) > 0.0001) {
		y = y_1;
		y_1 = gauss(b, y, n);
		y_1 = norm(y_1);

		if (y[0] * y_1[0] < 0) {
			y_1 = invert(y_1);
		}
	}
	y = y_1;
	y_1 = gauss(b, y, n);

	double lam_obr = 0;
	int count_lam_obr = 0;
	for (int i = 0; i < y.size(); ++i) {
		//cout << y[i] / y_1[i] << ' ';
		if (abs(y_1[i]) > 1e-5) {
			lam_obr += y[i] / y_1[i];
			count_lam_obr++;
		}
	}
	//cout << endl;
	lam_obr /= count_lam_obr;
	cout << "lam_obr = " << lam_obr << endl;
	cout << "lam = " << lam + lam_obr << endl;

	/*cout << "vector: ";
	for (int i = 0; i < y.size(); ++i) {
		cout << y[i] << ' ';
	}*/
	

	vector<vector<double>> c = m;
	cout << "=======" << endl;

	for (int i = 0; i < c.size(); ++i) {
		for (int j = 0; j < c[i].size(); ++j) {
			cout << c[i][j] << ' ';
		}
		cout << endl;
	}

	cout << lam_2 << endl;
	cout << "oprox lam2: ";
	cin >> lam_2;

	cout << "=======" << endl;

	for (int i = 0; i < n; ++i) {
		c[i][i] -= lam_2;
	}
	
	cout << "=======" << endl;
	for (int i = 0; i < c.size(); ++i) {
		for (int j = 0; j < c[i].size(); ++j) {
			cout << c[i][j] << ' ';
		}
		cout << endl;
	}
	cout << "=======" << endl;

	//vector<double>
	//	y = norm(x_1);
	for (int i = 0; i < y.size(); ++i) {
		y[i] = rand();
	}
	//vector<double>
	//y_1 = gauss(b, y, n);
	//y_1 = norm(y_1);

	/*while (lenth(sub_v(y_1, y)) > 0.0001) {
		y = y_1;
		y_1 = gauss(c, y, 3);
		y_1 = norm(y_1);

		if (y[0] * y_1[0] < 0) {
			y_1 = invert(y_1);
		}
	}*/

	double lam_2_obr = 0;
	double lam_pred_2_obr = 0;

	y_1 = gauss(c, y, 3);

	tempCount = 0;
	lam_2_obr = 0;
	for (int i = 0; i < y_1.size(); ++i) {
		if (abs(y[i]) > e) {
			lam_2_obr += y_1[i] / y[i];
			++tempCount;
			//cout << "x_1 = " << x_1[i] << endl;
			//cout << "x = " << x[i] << endl;
		}
	}
	//cout << lam << endl;
	//cout << tempCount << endl;
	lam_2_obr = lam_2_obr / tempCount;
	//cout << lam << endl;
	//cout << "===" << endl;
	y_1 = norm(y_1);


	while (abs(lam_2_obr - lam_pred_2_obr) > 0.00001) {
		y = y_1;
		y_1 = gauss(c, y, 3);


		lam_pred_2_obr = lam_2_obr;

		int tempCount = 0;
		lam_2_obr = 0;
		for (int i = 0; i < x_1.size(); ++i) {
			if (abs(y[i]) > e) {
				lam_2_obr += y_1[i] / y[i];
				++tempCount;
				//cout << "+" << endl;
				//cout << "x_1 = " << x_1[i] << endl;
				//cout << "x = " << x[i] << endl;
			}
		}

		lam_2_obr = lam_2_obr / tempCount;
		cout << "lam_2_obr = " << lam_2_obr << endl;

		y_1 = norm(y_1);

		if (y[0] * y_1[0] < 0) {
			y_1 = invert(y_1);
		}
	}

	/*y = y_1;
	y_1 = gauss(b, y, 3);

	double lam_obr_2 = 0;
	//int 
		count_lam_obr = 0;
	for (int i = 0; i < y.size(); ++i) {
		//cout << y[i] / y_1[i] << ' ';
		if (abs(y_1[i]) > 1e-5) {
			lam_obr_2 += y[i] / y_1[i];
			count_lam_obr++;
		}
	}*/
	//cout << endl;
	//lam_obr /= count_lam_obr;
	cout << "lam_obr_2 = " << lam_2_obr << endl;
	cout << "lam_2 = " << lam_2 + lam_2_obr << endl;


	cout << endl;
	cout << "end" << endl;
	system("pause");
	return 0;
}
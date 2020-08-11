#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

typedef vector<double> functionType(double, vector<double>);

int n;

// y" + p(t)*y' + q(x)*y = f(t)
double f(double t) {
	if (n == 1) {
		return 0;
	}
	else if (n == 2) {
		return 6 * t/(pow(t, 2) - 1);
	}
	else if (n == 3) {
		return 0;
	}
}
double p(double t) {
	if (n == 1) {
		return 4 * t / (2 * t + 1);
	}
	else if (n == 2) {
		return 4 * t / (pow(t, 2) - 1);
	}
	else if (n == 3) {
		return 0;
	}
}
double q(double t) {
	if (n == 1) {
		return -4 / (2 * t + 1);
	}
	else if (n == 2) {
		return -2 / (pow(t, 2) - 1);
	}
	else if (n == 3) {
		return -2*(1+pow(tan(t),2));
	}
}
// y'(a) - al_1*y(a) = al_2
// y'(b) - bt_1*y(b) = bt_2
double a; double al_1; double al_2; 
double b; double bt_1; double bt_2;

void setBorders() {
	if (n == 1) {
		a = 0; al_1 = 1; al_2 = -2;
		b = 2; bt_1 = 1; bt_2 = -1.073262555554937;
	}
	else if (n == 2) {
		a = 2; al_1 = 1; al_2 = -1.234721044665223;
		b = 7; bt_1 = 1; bt_2 = -2.420465655758776;
	}
	else if (n == 3) {
		a = 0; al_1 = 2; al_2 = -1;
		b = 3.14/4; bt_1 = 2; bt_2 = -1;
	}
}


vector<double> sysU(double t, vector<double> v) {
	vector<double> tmp;
	tmp.resize(2);
	tmp[0] = v[1];
	tmp[1] = f(t) - q(t)*v[0] -p(t)*v[1];
	return tmp;
}

vector<double> initCon(double xi) {
	vector<double> tmp;
	tmp.resize(2);
	tmp[0] = xi;
	tmp[1] = al_2 + al_1 * xi;
	return tmp;
}

// сложение 2-х векторов
vector<double> addVectors(vector<double> a, vector<double> b) {
	for (int i = 0; i < a.size(); ++i) {
		a[i] += b[i];
	}
	return a;
}

// сложение 4-х векторов
vector<double> add4Vectors(vector<double> a, vector<double> b, vector<double> c, vector<double> d) {
	for (int i = 0; i < a.size(); ++i) {
		a[i] += b[i] + c[i] + d[i];
	}
	return a;
}

// умножение ветора на число
vector<double> multVectorByNumber(vector<double> a, double b) {
	for (int i = 0; i < a.size(); ++i) {
		a[i] *= b;
	}
	return a;
}

//k_1 = f(t_n, y_n)
vector<double> coefK1(double t, vector<double> v) {
	return sysU(t, v);
}
//k_2 = f(t + h, y_n + h*k_1)
vector<double> coefK2(double t, vector<double> v, vector<double> k, double h) {
	return sysU(t + h/2, addVectors(v, multVectorByNumber(k, h/2)));
}
//k_2 = f(t + h, y_n + h*k_1)
vector<double> coefK4(double t, vector<double> v, vector<double> k, double h) {
	return sysU(t + h, addVectors(v, multVectorByNumber(k, h)));
}
// метод рунге 1-го прядка
vector<double> runge(double t, vector<double> v, double h) {
	vector<double> k1 = coefK1(t, v);
	vector<double> k2 = coefK2(t, v, k1, h);
	vector<double> k3 = coefK2(t, v, k2, h);
	vector<double> k4 = coefK4(t, v, k3, h);
	return addVectors(v, multVectorByNumber(add4Vectors(k1, multVectorByNumber(k2, 2), multVectorByNumber(k3, 2), k4), h / 6));
}

vector<vector<double>> adamas(double xi) {

	vector<vector<double>> answer;
	answer.resize(3);

	double h = 0.01;

	//нулевой шаг
	double t = a;
	vector<double> v0 = initCon(xi);
	answer[0].push_back(t);
	answer[1].push_back(v0[0]);
	answer[2].push_back(v0[1]);

	//первый шаг
	t += h;
	vector<double> v1 = runge(t, v0, h);
	answer[0].push_back(t);
	answer[1].push_back(v1[0]);
	answer[2].push_back(v1[1]);
	
	//второй шаг
	t += h;
	vector<double> v2 = runge(t, v1, h);
	answer[0].push_back(t);
	answer[1].push_back(v2[0]);
	answer[2].push_back(v2[1]);

	//третий шаг
	t += h;
	vector<double> v3 = runge(t, v2, h);
	answer[0].push_back(t);
	answer[1].push_back(v3[0]);
	answer[2].push_back(v3[1]);
	
	//Метод Адамса
	while (t <= b) {
		t += h;
		vector<double> vNext = addVectors(v3, multVectorByNumber(add4Vectors(multVectorByNumber(sysU(t, v3), 55),
			multVectorByNumber(sysU(t, v2), -59), multVectorByNumber(sysU(t, v1), 37), multVectorByNumber(sysU(t, v0), -9)), h / 24));
		answer[0].push_back(t);
		answer[1].push_back(vNext[0]);
		answer[2].push_back(vNext[1]);
		v0 = v1;
		v1 = v2;
		v2 = v3;
		v3 = vNext;
	}
	
	return answer;
}


double test1;
double test2;
double test3;
double test4;

pair<double, vector<vector<double>>> fi(double x) {
	vector<vector<double>> tmp = adamas(x);
	test1 = tmp[1][tmp[1].size() - 1];
	test2 = tmp[2][tmp[2].size() - 1];
	test3 = tmp[1][tmp[1].size() - 1] - bt_1 * tmp[2][tmp[2].size() - 1] - bt_2;
	return make_pair( (tmp[2][tmp[2].size() - 1] - bt_1 * tmp[1][tmp[1].size() - 1] - bt_2), /*tmp2*/ tmp );
}

vector<vector<double>> solve() {
	pair<double, vector<vector<double>>> result;

	double eps = 0.00001;
	double xi_a = -100;
	double xi_b = 100;
	result = fi(xi_a);

	
	double l = xi_b - xi_a;

	result = fi(xi_a);
	double f_a = result.first;


	result = fi(xi_b);
	double f_b = result.first;


	while (l > eps) {
		double xi_c = (xi_a + xi_b) / 2;
		result = fi(xi_c);
		double f_c = result.first;


		if (f_a * f_c < 0) {
			xi_b = xi_c;
		} 
		else if (f_c * f_b < 0) {
			xi_a = xi_c;
			f_a = f_c;

		}
		l = abs(xi_b - xi_a);
	}
	cout << f_a << endl;
	return result.second;
	
}

int main() {
	cout << "Enter file name: ";
	cin >> n;
	setBorders();
	ofstream output;
	output.open("answer.txt");
	vector<vector<double>> answer = solve();

	for (int i = 0; i < answer[0].size(); ++i) {
		output << answer[0][i] << '	' << answer[1][i] << '	' << answer[2][i] << endl;
	}

	output.close();
	system("pause");
}
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

	//������ ����
	double x = 0;
	double t = 1;
	double delt;
	double x_n;
	double a = x - t;
	double b = x + t;
	int powerOfTwo = 2;

	output << "1) ������ ��������� ���������:" << endl;
	output << "   x_0 = " << x << endl;
	output << "   t = " << t << " > 0" << endl << endl;

	//������ ����
	int k = 0;

	output << "2) k = 0" << endl << endl;

	//������ ����
	double f_x_right = func(x - t);
	double f_x = func(x);
	double f_x_left = func(x + t);

	output << "3) �������� ��������� ������� ������� f(x_0-t) = " << f_x_right << endl;
	output << "                                      f(x_0)   = " << f_x << endl;
	output << "                                      f(x_0+t) = " << f_x_left << endl << endl;

	//��������� ����
	output << "4) �������� ������� ���������" << endl;
	if ((f_x_right >= f_x) && (f_x <= f_x_left)) {
		output << "a) f(x_0-t) >= f(x_0) <= f(x_0+t) �� ��������� �������� ������" << endl;
		output << "   [a,b] = [" << x - t << "," << x + t << "]" << endl << endl;
	}
	else if ((f_x_right <= f_x) && (f_x >= f_x_left)) {
		output << "�) f(x_0-t) <= f(x_0) >= f(x_0+t) ��" << endl;
		output << "   ������� �� ������������" << endl << endl;
	}
	else {
		output << "�) ������� ��������� �� ��������� �������� � ���� 5" << endl << endl;

		//����� ����

		output << "5) �������� �������� delt" << endl;
		if ((f_x_right >= f_x) & (f_x >= f_x_left)) {
			output << "�) f(x_0-t) >= f(x_0) > f(x_0+t)" << endl;
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
			output << "�) f(x_0-t) <= f(x_0) < f(x_0+t)" << endl;
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
			//������ ����
			x = x_n;
			x_n = x_n + powerOfTwo * delt;
			powerOfTwo *= 2;

			output << "6) ������ x_" << k + 1 << " = x_" << k << " + 2^k * delt = " << x_n << endl << endl;
			
			//������ ����
			output << "7) �������� ������� ��������" << endl;
			if (func(x_n) < func(x)) {
				if (delt == t) {
					output << "a) f(x_" << k + 1 << ") < f(x_" << k << ") � delt == t" << endl;
					a = x;
					output << "   �� a_0 = " << a << endl << endl;
				}
				else {
					output << "a) f(x_" << k + 1 << ") < f(x_" << k << ") � delt == -t" << endl;
					b = x;
					output << "   �� b_0 = " << b << endl << endl;
				}
			}
			else {
				output << "�) f(x_" << k + 1 << ") > f(x_" << k << ")" << endl;
				output << "   �������� �����������" << endl;
				if (delt == t) {
					b = x_n;
				}
				else {
					a = x_n;
				}
				output << "   [a,b] = [" << a << "," << b << "] - ������ ��������� �������� ���������������" << endl;
				break;
			}
		}
	}

	output.close();
	return 0;
}
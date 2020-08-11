#include <iostream>
#include <ctime> 
#include <vector>
#include <algorithm>

using namespace std;


int propotionalSampling(vector<int> a) {
	double sum = 0;
	for (int i = 0; i < a.size(); ++i) {
		sum += a[i];
	}

	vector<double> tmp;
	for (int i = 0; i < a.size(); ++i) {
		tmp.push_back(a[i]/sum);
	}

	sort(a.begin(), a.end());
	sort(tmp.begin(), tmp.end());

	vector<double> csum;
	csum.resize(a.size());
	csum[0] = tmp[0];
	for (int i = 1; i < csum.size(); ++i) {
		csum[i] = csum[i - 1] + tmp[i];
	}

	double r = (double) rand() / RAND_MAX;
	//cout << r << endl;
	double number = 0;

	for (int i = 0; i < csum.size(); ++i) {
		if (r <= csum[i]) {
			number = a[i];
			break;
		}
	}
	return number;
}


int backwardpropotionalSampling(vector<int> a) {
	double sum = 0;
	double max = 0;
	for (int i = 0; i < a.size(); ++i) {
		if (a[i] > max) {
			max = a[i];
		}
	}

	for (int i = 0; i < a.size(); ++i) {
		sum += max - a[i];
	}

	vector<double> tmp;
	for (int i = 0; i < a.size(); ++i) {
		tmp.push_back((max - a[i]) / sum);
	}

	sort(a.begin(), a.end(), greater<int>());
	sort(tmp.begin(), tmp.end());
	
	vector<double> csum;
	csum.resize(a.size());
	csum[0] = tmp[0];
	for (int i = 1; i < csum.size(); ++i) {
		csum[i] = csum[i - 1] + tmp[i];
	}
	
	double r = (double)rand() / RAND_MAX;
	//cout << r << endl;
	double number = 0;

	for (int i = 0; i < csum.size(); ++i) {
		if (r <= csum[i]) {
			number = a[i];
			break;
		}
	}
	return number;
}

int main() {
	srand(time(0));
	vector<int> a = { 0, 5, 27, 6, 13, 28, 100, 45, 10, 79 };
	vector<int> b = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	for (int i = 0; i < 100; ++i) {
		int tmp = propotionalSamplong(a);
		for (int i = 0; i < a.size(); ++i) {
			if (tmp == a[i]) {
				b[i]++;
			}
		}
	}

	for (int i = 0; i < b.size(); ++i) {
		cout << a[i] << " | " << b[i] << endl;
	}
	system("pause");
	return 0;
}
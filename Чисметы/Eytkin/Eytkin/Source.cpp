#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

double eytkin(vector<double> X, vector<double> Y, int n , double x)
{
	for (int j = 1; j < n; ++j)
	{
		//int k = 1;
		for (int i = 0; i < n - j; ++i)
		{
			//Y[i] = ((x - X[j]) * Y[i] - (x - X[i]) * Y[j]) / (X[i] - X[j]);
			Y[i] = ((x - X[i]) * Y[i + 1] - (x - X[i + j]) * Y[i]) / (X[i + j] - X[i]);
			//++k;
			//cout << Y[i] << ' ';
		}
		//cout << '\n';
	}
	return Y[0];
}

int main()
{
	vector <double> X;
	vector <double> Y;
	ifstream file;
	cout << "File name: ";
	string fileName;
	cin >> fileName;
	file.open(fileName + ".txt");
	if (!file)
	{
		cout << "file does't exist\n";
		return 0;
	}
	else
	{
		double tmp1,tmp2;
		while ((file >> tmp1) && (file >> tmp2))
		{
			X.push_back(tmp1);
			Y.push_back(tmp2);
		}
		file.close();

		double x = X[0];
		double step = (X[X.size() - 1] - X[0]) / 1000;

		//cout << '\n' << eytkin(X, Y, X.size(), 0.5);

		ofstream fileOut;
		fileOut.open(fileName + " output.txt");
		while (x <= X[X.size() - 1])
		{
			fileOut << x << ' ' << eytkin(X, Y, X.size(), x) << '\n';
			x += step;
		}
		
		/*for (int i = 0; i < x.size(); ++i)
		{
			cout << x[i] << ' ' << y[i] << '\n';
		}*/

	}
	return 0;
}
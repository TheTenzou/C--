#include <iostream>
#include <vector>

using namespace std;

typedef double (*func)(double);

vector<double> gauss(vector<vector<double>> a, vector<double> y, int n)
{
	vector<double> x(n,0); 
	double max;
	int k, index;
	const double eps = 0.00001;
	k = 0;
	while (k < n)
	{
		max = abs(a[k][k]);
		index = k;
		for (int i = k + 1; i < n; i++)
		{
			if (abs(a[i][k]) > max)
			{
				max = abs(a[i][k]);
				index = i;
			}
		}

		if (max < eps)
		{
			//cout << "no solutions ";
			return x;
		}
		for (int j = 0; j < n; j++)
		{
			float temp = a[k][j];
			a[k][j] = a[index][j];
			a[index][j] = temp;
		}

		float temp = y[k];
		y[k] = y[index];
		y[index] = temp;
		for (int i = k; i < n; i++)
		{
			float temp = a[i][k];
			if (abs(temp) < eps) continue;
			for (int j = 0; j < n; j++)
			{
				a[i][j] = a[i][j] / temp;
			}
			y[i] = y[i] / temp;
			if (i == k)  continue;
			for (int j = 0; j < n; j++)
			{
				a[i][j] = a[i][j] - a[k][j];
			}
			y[i] = y[i] - y[k];
		}
		k++;
	}
	for (k = n - 1; k >= 0; k--)
	{
		x[k] = y[k];
		for (int i = 0; i < k; i++)
		{
			y[i] = y[i] - a[i][k] * x[k];
		}
	}
	return x;
}

vector<double> coofQuad(vector<pair<double,double>> points)
{
	vector <vector<double>> a(3, vector<double>(3));
	vector <double>b(3);

	a[0][0] = points[0].first * points[0].first;
	a[0][1] = points[0].first;
	a[0][2] = 1;

	a[1][0] = points[1].first * points[1].first;
	a[1][1] = points[1].first;
	a[1][2] = 1;

	a[2][0] = points[2].first * points[2].first;
	a[2][1] = points[2].first;
	a[2][2] = 1;

	b[0] = points[0].second;
	b[1] = points[1].second;
	b[2] = points[2].second;

	return gauss(a, b, 3);
}

pair<double, double> solveQuad(vector<double> coof)
{
	float d = coof[1]*coof[1] - 4*coof[0]*coof[2];
	pair<double, double> ans;
	ans.first = (-coof[1] + sqrt(d)) / (2 * coof[0]);
	ans.second = (-coof[1] - sqrt(d)) / (2 * coof[0]);
	return ans;
}


double solve(func f, double a, double b)
{
	vector<pair<double,double>> points(3);
	points[0].first = a;
	points[1].first = b;
	points[2].first = (a + b) / 2;
	points[0].second = f(points[0].first);
	points[1].second = f(points[1].first);
	points[2].second = f(points[2].first);
	double eps = 0.00001;

	while (eps < abs(points.back().second))
	{
		pair<double, double> ansQuad = solveQuad(coofQuad(points));
		if ((a < ansQuad.first) && (ansQuad.first < b))
		{
			points.push_back(make_pair(ansQuad.first, f(ansQuad.first)));
		}
		else
		{
			points.push_back(make_pair(ansQuad.second, f(ansQuad.second)));
		}
		points.erase(points.begin());
	} 

	return points.back().first;
}

vector<double> solveIntr(func f, double a, double b, int steps)
{
	double tmp = a;
	double step = (b - a) / steps;
	vector<double> ans;
	while (tmp + step < b)
	{
		if (f(tmp) * f(tmp + step) < 0)
		{
			ans.push_back(solve(f, tmp, tmp + step));
		}
		tmp += step;
	}

	return ans;
}

double function1(double x) { return x * x * x + 3 * x * x - 6 * x - 8; }

double function2(double x) { return sin(x) * cos(x); }

double function3(double x) { return exp(-2*x) * log(x); }


int main()
{
	//vector<double> ans = solveIntr(&function1, -4.5, 5, 10);
	///vector<double> ans = solveIntr(&function2, -4.5, 2, 10);
	vector<double> ans = solveIntr(&function3, -4.5, 5, 10);
	for (size_t i = 0; i < ans.size(); ++i)
	{
		cout << ans[i] << ' ';
	}
	cout << '\n';
	system("pause");
	return 0;
}
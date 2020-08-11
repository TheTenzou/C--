#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

int r;
const long long MAX = 10000000000000000;
vector <long long> graphSize;
vector <long long> aToFirst, aToLast, bToFirst, bToLast;

void prepare(long long x, int n, vector <long long> &first, vector <long long> &last) 
{
	if (n == 0) // 1 �������
	{
		first[0] = 0;
		last[0] = 0;
		return;
	}

	if (n == 1) // 2 �������
	{
		first[1] = (x == 2);
		last[1] = (x == 1);
		return;
	}

	if (x <= graphSize[n - 1]) // � ������� ��������
	{
		prepare(x, n - 1, first, last);
		first[n] = min(first[n - 1], last[n - 1] + 2); // �� 1 ����� ������� ���� ��� ����� ������� ����� ����������
		last[n] = min(first[n - 1], last[n - 1]) + (n - 1) / 2 + 1; // min ���� �� ����� ���������� � �� ��� �� ����� ������ ��������
	}
	else // � ������� ��������
	{
		prepare(x - graphSize[n - 1], n - 2, first, last);
		first[n] = first[n - 2] + 1;
		last[n] = last[n - 2];
	}
}

long long distance(long long a, long long b, int n) 
{

	if (a == b)
	{
		return 0;
	}

	if (n <= 2)
	{
		return 1;
	}

	if (a <= graphSize[n - 1]) 
	{
		if (b >= graphSize[n - 1] + 1) // ����� �� ������ ������� �� ����� ����������
		{
			return min(aToFirst[n - 1], aToLast[n - 1]) + bToFirst[n - 2] + 1; // ���� �� � �� ����� ���������� + ���� �� �.�. �� b
		}
		else // ��� ����� � ������� (������) ��������
		{
			// ���� � ������� ��������       // ���� ����� ������� ����� ����������
			return min(distance(a, b, n - 1), min(aToFirst[n - 1] + 2 + bToLast[n - 1], aToLast[n - 1] + 2 + bToFirst[n - 1]));
		}
	}
	else //��� ����� � ������� (������) ��������
	{
		return distance(a - graphSize[n - 1], b - graphSize[n - 1], n - 2);
	}
}

int main() {
	int t;
	cin >> t >> r;

	graphSize.push_back(1);
	graphSize.push_back(2);
	int iMax = 2;
	for (; graphSize.back() < MAX; ++iMax)
	{
		graphSize.push_back(graphSize[iMax - 1] + graphSize[iMax - 2]);
	}

	for (int i = 1; i <= t; i++) 
	{
		long long a, b;
		cin >> a >> b;
		if (a > b)
		{
			swap(a, b);
		}
		aToFirst.resize(min(r, iMax) + 1);
		aToLast.resize(min(r, iMax) + 1);
		bToFirst.resize(min(r, iMax) + 1);
		bToLast.resize(min(r, iMax) + 1);
		prepare(a, min(r, iMax), aToFirst, aToLast);
		prepare(b, min(r, iMax), bToFirst, bToLast);
		cout << distance(a, b, min(r, iMax)) << endl;
	}
	system("pause");
	return 0;
}
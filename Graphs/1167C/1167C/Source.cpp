#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

vector <int> parent;
vector <int> size_;

void make_set(int v) {
	parent[v] = v;
	size_[v] = 1;
}

int find_set(int v) {
	if (v == parent[v])
		return v;
	return parent[v] = find_set(parent[v]);
}

void union_sets(int a, int b) {
	a = find_set(a);
	b = find_set(b);
	if (a != b) {
		if (size_[a] < size_[b])
			swap(a, b);
		parent[b] = a;
		size_[a] += size_[b];
	}
}

int main()
{
	int n, m;
	ifstream file;
	file.open("1.txt");
	file >> n >> m; // n - колличество пользователей, m - колличество груп
	parent.resize(n + 1, n + 1);
	size_.resize(n + 1);

	for (int i = 0; i < m; ++i)
	{
		int users_count;
		file >> users_count;
		if (users_count)
		{
			--users_count;

			int user_first;
			file >> user_first;

			if (parent[user_first] == n + 1)
			{
				make_set(user_first);
			}

			for (; users_count; --users_count)
			{
				int user_current;
				file >> user_current;

				if (parent[user_current] == n + 1)
				{
					make_set(user_current);
				}
				union_sets(user_first, user_current);
			}
		}
	}
	for (int i = 1; i <= n; ++i)
	{
		if (parent[i] != n + 1)
		{
			cout << size_[find_set(i)]<< '\n';
		}
		else
		{
			cout << 1 << '\n';
		}
	}
	return 0;
}
/*#include <iostream>
#include <vector>
//#include <algorithm>

using namespace std;

struct vertex
{
	int visited;
	vector <int> language;
	vector <int> neighbor;
};

vector <vertex> graph;

void dfs(int a)
{
	graph[a].visited = 1;
	for (size_t i = 0; i < graph[a].neighbor.size(); ++i)
	{
		if (!graph[graph[a].neighbor[i]].visited)
		{
			dfs(graph[a].neighbor[i]);
		}
	}
}

int main()
{
	/*vector<int> vector1 = { 1,45, 54, 71, 76, 13 };
	vector<int> vector2 = { 1, 5, 4, 6, 12 };
	vector<int> v(vector1.size() + vector2.size());
	vector<int>::iterator it, st;
	sort(vector1.begin(), vector1.end());
	sort(vector2.begin(), vector2.end());
	it = set_intersection(vector1.begin(),
		vector1.end(),
		vector2.begin(),
		vector2.end(),
		v.begin());
	cout << "\nCommon elements:\n";
	for (int i = 0; i < v.size(); ++i)
	{
		cout << v[i]<< ' ';
	}
	cout << '\n';
	for (st = v.begin(); st != it; ++st)
		cout << *st << ", ";
	cout << "====" << '\n';
	cout << (v.begin() != it);

	int n, m;
	cin >> n >> m;

	for (int i = 0; i < n; ++i)
	{
		int langCount;
		cin >> langCount;
		vertex emploee;
		emploee.visited = 0;
		for (;langCount; --langCount)
		{
			int lang;
			cin >> lang;
			emploee.language.push_back(lang);
		}
		//sort(emploee.language.begin(), emploee.language.end());
		for (size_t j = 0; j < graph.size(); ++j)
		{
			/*vector<int> tmp(graph[j].language.size() + emploee.language.size());
			vector<int>::iterator it;
			it = set_intersection(
				graph[j].language.begin(),
				graph[j].language.end(),
				emploee.language.begin(),
				emploee.language.end(),
				tmp.begin());
			if (tmp.begin() != it)
			{
				emploee.neighbor.push_back(j);
				graph[j].neighbor.push_back(i);
			}
			int canCommunicate = 0;
			for (int k = 0; k < emploee.language.size(); ++k)
			{
				for (int l = 0; l < graph[j].language.size(); ++l)
				{
					if (emploee.language[k] == graph[j].language[l])
					{
						canCommunicate = 1;
					}
				}
			}
			if (canCommunicate)
			{
				emploee.neighbor.push_back(j);
				graph[j].neighbor.push_back(i);
			}
		}
		graph.push_back(emploee);
	}
	int answer = 0;
	for (int i = 0; i < graph.size(); ++i)
	{
		if (!graph[i].visited)
		{
			dfs(i);
			++answer;
		}
	}
	cout << answer - 1;
	return 0;
}*/

#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

vector <int> parent;
vector <int> rang;

void make_set(int v) {
	parent[v] = v;
	rang[v] = 0;
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
		if (rang[a] < rang[b])
			swap(a, b);
		parent[b] = a;
		if (rang[a] == rang[b])
			++rang[a];
	}
}

int main()
{
	int n, m;
	ifstream file;
	file.open("1.txt");
	file >> n >> m;
	parent.resize(m,m);
	rang.resize(m);
	int people_0 = 0;
	for (int i = 0; i < n; ++i)
	{
		int language_count;
		file >> language_count;
		if (language_count)
		{
			--language_count;

			int language_first;
			file >> language_first;
			--language_first;

			if (parent[language_first] == m)
			{
				make_set(language_first);
			}

			for (; language_count; --language_count)
			{
				int language_current;
				file >> language_current;
				--language_current;

				if (parent[language_current] == m)
				{
					make_set(language_current);
				}
				union_sets(language_first, language_current);
			}
		}
		else
		{
			++people_0;
		}
	}
	int answer = 0;
	for (size_t i = 0; i < parent.size(); ++i)
	{
		if (parent[i] == i)
		{
			++answer;
		}
	}
	if (answer)
	{
		--answer;
	}
	cout << answer + people_0;
	return 0;
}
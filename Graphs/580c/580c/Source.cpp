//версия 1
/*#include <iostream>
#include <vector>

using namespace std;

struct vertex
{
	int visited;
	int cat;
	vector <int> neighbor;
};

vector <vertex> graph;

int m;

int bfs(int a, int k)
{
	graph[a].visited = 1;
	k += graph[a].cat;
	if (k <= m)
	{
		int sum = 0;
		int t = 0;
		for (size_t i = 0; i < graph[a].neighbor.size(); ++i)
		{
			if (!graph[graph[a].neighbor[i]].visited)
			{
				if (graph[a].cat)
				{
					sum += bfs(graph[a].neighbor[i], k);
				}
				else
				{
					sum += bfs(graph[a].neighbor[i], 0);
				}
				++t;
			}
		}
		if (!t)
		{
			return 1;
		}
		else
		{
			return sum;
		}
	}
	else
	{
		return 0;
	}
}

int main()
{
	int n;
	cin >> n >> m;
	graph.resize(n);
	for (int i = 0; i < n; ++i)
	{
		cin >> graph[i].cat;
	}
	for (int i = 0; i < n - 1; ++i)
	{
		int a, b;
		cin >> a >> b;
		graph[--a].neighbor.push_back(--b);
		graph[b].neighbor.push_back(a);
	}

	for (size_t i = 0; i < graph.size(); ++i)
	{
		graph[i].visited = 0;
	}

	cout << bfs(0, 0);
	return 0;
}*/

//версия 2
#include <iostream>
#include <vector>

using namespace std;

struct vertex
{
	int visited;
	int cat;
	vector <int> neighbor;
};

vector <vertex> graph;

int m;

int bfs(int a, int k)
{
	graph[a].visited = 1;
	k += graph[a].cat;
	if (k <= m)
	{
		int sum = 0;
		int t = 0;
		for (size_t i = 0; i < graph[a].neighbor.size(); ++i)
		{
			if (!graph[graph[a].neighbor[i]].visited)
			{
				if (graph[a].cat)
				{
					sum += bfs(graph[a].neighbor[i], k);
				}
				else
				{
					sum += bfs(graph[a].neighbor[i], 0);
				}
				++t;
			}
		}
		if (!t)
		{
			return 1;
		}
		else
		{
			return sum;
		}
	}
	else
	{
		return 0;
	}
}

int main()
{
	int n;
	scanf("%d", &n);
	scanf("%d", &m);
	graph.resize(n);
	for (int i = 0; i < n; ++i)
	{
		scanf("%d", &graph[i].cat);
	}
	for (int i = 0; i < n - 1; ++i)
	{
		int a, b;
		scanf("%d", &a);
		scanf("%d", &b);
		graph[--a].neighbor.push_back(--b);
		graph[b].neighbor.push_back(a);
	}

	for (size_t i = 0; i < graph.size(); ++i)
	{
		graph[i].visited = 0;
	}
	printf("%d", bfs(0, 0));
	return 0;
}
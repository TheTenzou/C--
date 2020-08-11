#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <fstream>
#include <iomanip>

using namespace std;

// структура вершины графа
struct vertex 
{
	int visited;
	int weight;
	int color;
	vector <pair<int, int>> neighbor;
};

// граф
vector <vertex> graph; 

//ребро
struct edge
{
	int a, b, w;
};

//ребра графа
vector<edge> edges;
int zero = 0; // 1 граф начинается с 0, 0 с 1
//================================================================


// ввод графа
int initGraph()
{
	ifstream file;
	cout << "File name: ";
	string fileName;
	cin >> fileName;
	file.open(fileName + ".txt");
	if (!file)
	{
		cout << "File does't exist" << endl;
		return 0;
	}
	else
	{

		int n, m;
		file >> zero;
		file >> n;
		file >> m;
		graph.resize(n);

		for (int i = 0; i < m; ++i)
		{
			int a, b, w;
			file >> a >> b;
			file >> w;
			if (!zero) 
			{
				--a;
				--b;
			}
			graph[a].neighbor.push_back(make_pair(b, w));
			graph[b].neighbor.push_back(make_pair(a, w));
		}

		for (int i = 0; i < graph.size(); ++i)
		{
			graph[i].visited = 0;
		}

		file.close();
		return 1;
	}
}


int initTreeColor()
{
	ifstream file;
	cout << "File name: ";
	string fileName;
	cin >> fileName;
	file.open(fileName + ".txt");
	if (!file)
	{
		cout << "File does't exist" << endl;
		return 0;
	}
	else
	{

		int n, k;
		file >> n;
		file >> k;
		graph.resize(n);
		for (int i = 0; i < k; ++i)
		{
			int j;
			file >> j;
			graph[--j].color = 1;
		}
		for (int i = 0; i < n - 1; ++i)
		{
			int a, b, w = 0;
			file >> a >> b;
			//file >> w;
			if (!zero)
			{
				--a;
				--b;
			}
			graph[a].neighbor.push_back(make_pair(b, w));
			graph[b].neighbor.push_back(make_pair(a, w));
		}

		for (int i = 0; i < graph.size(); ++i)
		{
			graph[i].visited = 0;
		}

		file.close();
		return 1;
	}
}

//строим вектор ребер
void getVectorOfEdges()
{
	for (int i = 0; i < graph.size(); ++i)
	{
		for (int j = 0; j < graph[i].neighbor.size(); ++j)
		{
			edge tmp;
			tmp.a = i;
			tmp.b = graph[i].neighbor[j].first;
			tmp.w = graph[i].neighbor[j].second;
			edges.push_back(tmp);
		}
	}
}

//обход в глубину
void dfs(int a) 
{
	graph[a].visited = 1;

	cout << ((zero) ? a : a + 1) << endl;

	for (int i = 0; i < graph[a].neighbor.size(); ++i)
	{
		graph[graph[a].neighbor[i].first].weight = graph[a].weight;
		if (!graph[graph[a].neighbor[i].first].visited)
		{
			dfs(graph[a].neighbor[i].first);
		}
	}
}

int dfsColor(int a)
{
	graph[a].visited = 1;

	//cout << ((zero) ? a : a + 1) << endl;
	int sum = 0;
	for (int i = 0; i < graph[a].neighbor.size(); ++i)
	{
		if (!graph[graph[a].neighbor[i].first].visited)
		{
			sum += dfsColor(graph[a].neighbor[i].first);
		}
	}
	graph[a].weight = sum + graph[a].color;
	return graph[a].weight;
}

void dfsColor2(int a)
{
	graph[a].visited = 1;

	//cout << ((zero) ? a : a + 1) << endl;
	int k = 0;
	for (int i = 0; i < graph[a].neighbor.size(); ++i)
	{
		if (!graph[graph[a].neighbor[i].first].visited)
		{
			//dfsColor2(graph[a].neighbor[i].first);
			if (graph[graph[a].neighbor[i].first].weight)
			{
				dfsColor2(graph[a].neighbor[i].first);
			}
			else
			{
				++k;
			}
		}
	}
	if ((!k) && (!graph[a].color) && ((graph[0].weight - graph[a].weight) | (!a)))

	{
		cout << a + 1 << endl;
	}

}

//обход в ширену
void bfs(int a) 
{
	queue <pair<int, int>> q;
	q.push(make_pair(a, 0));
	graph[a].visited = 1;
	while (!q.empty())
	{
		a = q.front().first;
		int p = q.front().second;
		cout << "vertices " << ((zero) ? a : a + 1) << " level " << p << endl;
		q.pop();

		for (int i = 0; i < graph[a].neighbor.size(); ++i)
		{
			if (!graph[graph[a].neighbor[i].first].visited)
			{
				q.push(make_pair(graph[a].neighbor[i].first, p + 1));
				graph[graph[a].neighbor[i].first].visited = 1;
			}
		}
	}
};

//сумма всех весов ребер
int sumOfEdges()
{
	int inf = 1;
	for (int i = 0; i < graph.size(); ++i)
	{
		for (int j = 0; j < graph[i].neighbor.size(); ++j)
		{
			inf += graph[i].neighbor[j].second;
		}
	}
	return inf;
}

//алгоритм Дейкстры кратчайшее растояние до всех вершин от заданой
void dxt(int a)
{
	vector<int> distance(graph.size(), sumOfEdges());
	distance[a] = 0;
	set<pair<int, int>> q;
	q.insert(make_pair(distance[a], a));
	while (!q.empty())
	{
		int vertices = q.begin()->second;
		q.erase(q.begin());
		graph[vertices].visited = 1;
		for (int i = 0; i < graph[vertices].neighbor.size(); ++i)
		{
			if (!graph[graph[vertices].neighbor[i].first].visited)
			{
				int to = graph[vertices].neighbor[i].first, len = graph[vertices].neighbor[i].second;
				if (distance[vertices] + len < distance[to])
				{
					q.erase(make_pair(distance[to], to));
					distance[to] = distance[vertices] + len;
					q.insert(make_pair(distance[to], to));
				}
			}
		}
	}
	for (int i = 0; i < distance.size(); ++i)
	{
		cout << "vertices " << ((zero) ? i : i + 1) << " distance " << distance[i] << endl;
	}
}

//представление графа в матречном виде
vector <vector <int>> getGraphMatrix()
{
	int inf = sumOfEdges();

	vector <vector <int>> m(graph.size(), vector <int>(graph.size(), inf));

	for (int i = 0; i < graph.size(); ++i)
	{
		for (int j = 0; j < graph[i].neighbor.size(); ++j)
		{
			m[i][graph[i].neighbor[j].first] = graph[i].neighbor[j].second;
		}
	}

	return m;
}

//алгоритм Флойда-Уоршела крачайшее растояние между двумя вершинами
void floyd()
{
	vector <vector <int>> distance = getGraphMatrix();

	vector <vector <int>> root(graph.size(), vector<int>(graph.size(), -1));

	int inf = sumOfEdges();
	
	for (int k = 0; k < graph.size(); ++k)
	{
		for (int i = 0; i < graph.size(); ++i)
		{
			for (int j = 0; j < graph.size(); ++j)
			{
				if ((distance[i][k] < inf) && (distance[k][j] < inf))
				{
					if (distance[i][j] > (distance[i][k] + distance[k][j]))
					{
						distance[i][j] = distance[i][k] + distance[k][j];
						root[i][j] = k;
					}
				}
			}
		}
	}
	//востановление пути
	for (int a = 0; a < graph.size(); ++a)
	{
		for (int b = 0; b < graph.size(); ++b)
		{
			if (distance[a][b] == inf)
			{
				cout << "No path from: " << ((zero) ? a : a + 1) << " to " << ((zero) ? b : b + 1) << endl;
			}
			else
			{
				cout << "Length " << distance[a][b] << endl;

				vector <int> path;

				for (int current = a; current != -1; current = root[current][b])
				{
					path.push_back(current);
				}
				cout << "Path from " << ((zero) ? a : a + 1) << " to " << ((zero) ? b : b + 1) << ": ";
				for (size_t i = 0; i < path.size(); ++i)
				{
					cout << ((zero) ? path[i] : path[i] + 1) << ' ';
				}
				cout << ((zero) ? b : b + 1) << endl;
			}
		}
	}
}

//алгоритм Форда-Беллмана
void ford(int a)
{
	int inf = sumOfEdges(); 
	vector <int> distance(graph.size(), inf);
	vector <int> root(graph.size(), -1);

	getVectorOfEdges();
	distance[a] = 0;

	int doit = 1;
	while (doit)
	{
		doit = 0;
		for (int i = 0; i < edges.size(); ++i)
		{
			if (distance[edges[i].a] < inf)
			{
				if (distance[edges[i].b] > distance[edges[i].a] + edges[i].w)
				{
					distance[edges[i].b] = distance[edges[i].a] + edges[i].w;
					root[edges[i].b] = edges[i].a;
					doit = 1;
				}
			}
		}
	}
	//востановление пути
	for (int b = 0; b < distance.size(); ++b)
	{
		if (distance[b] == inf)
		{
			cout << "No path from " << ((zero) ? a : a + 1) << " to " << ((zero) ? b : b + 1) << endl;
		}
		else
		{
			cout << "Length " << distance[b] << endl;
			vector <int> path;
			for (int current = b; current != -1; current = root[current])
			{
				path.push_back(current);
			}
			reverse(path.begin(), path.end());
			cout << "Path from " << ((zero) ? a : a + 1) << " to " << ((zero) ? b : b + 1) << ": ";
			for (size_t i = 0; i < path.size(); ++i)
			{
				cout << ((zero) ? path[i] : path[i] + 1) << ' ';
			}
			cout << endl;
		}
	}
}

//задача с окрашеными вершинами
//Дерево из n вершин
//В дереве есть k покрашенных вершин
//Выберем произвольную непокрашенную вершину и сформируем корневое корневое дерево с вершиной в этой вершине
//Если у этой корневой вершины в каждом поддереве есть хотябы одна покрашенная верошина то она называется интересной
//Вы вести все инересные вершины
void zd1()
{
	if (initTreeColor())
	{
		int k = 0;
		dfsColor(k);
		for (int i = 0; i < graph.size(); ++i)
		{
			//cout << i + 1 << ' ' << graph[i].weight << ' ' << graph[i].color << endl;
			graph[i].visited = 0;
		}
		//dfsColor2(0);
		for (int i = 0; i < graph.size(); ++i)
		{
			if (!graph[i].color)
			{
				int t = 0;
				for (int j = 0; j < graph[i].neighbor.size(); ++j)
				{
					if (!graph[graph[i].neighbor[j].first].weight)
					{
						++t;
					}
				}
				if ((!t) && ((graph[k].weight - graph[i].weight) | (k == i)))
				{
					cout << i + 1 << endl;
				}
			}
		}
	}
}

int main()
{
	zd1();
	//if (initGraph())
	{
		//dfs(6);
		//bfs(0);
		//dxt(0);
		//floyd();
		//ford(5);
	}
	system("pause");
}

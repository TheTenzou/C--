/*#include <vector>
using namespace std;

const int MAXN = 1000;

int n, bridges, ancestor[MAXN], bl[MAXN], comp[MAXN], size_[MAXN];


void init() {
	for (int i = 0; i < n; ++i) {
		bl[i] = comp[i] = i;
		size_[i] = 1;
		ancestor[i] = -1;
	}
	bridges = 0;
}


int get(int v) {
	if (v == -1)  return -1;
	return bl[v] == v ? v : bl[v] = get(bl[v]);
}

int get_comp(int v) {
	v = get(v);
	return comp[v] == v ? v : comp[v] = get_comp(comp[v]);
}

void make_root(int v) {
	v = get(v);
	int root = v,
		child = -1;
	while (v != -1) {
		int p = get(ancestor[v]);
		ancestor[v] = child;
		comp[v] = root;
		child = v;  v = p;
	}
	size_[root] = size_[child];
}


int cu, u[MAXN];

void merge_path(int a, int b) {
	++cu;

	vector<int> va, vb;
	int lca = -1;
	for (;;) {
		if (a != -1) {
			a = get(a);
			va.push_back(a);

			if (u[a] == cu) {
				lca = a;
				break;
			}
			u[a] = cu;

			a = ancestor[a];
		}

		if (b != -1) {
			b = get(b);
			vb.push_back(b);

			if (u[b] == cu) {
				lca = b;
				break;
			}
			u[b] = cu;

			b = ancestor[b];
		}
	}

	for (size_t i = 0; i < va.size(); ++i) {
		bl[va[i]] = lca;
		if (va[i] == lca)  break;
		--bridges;
	}
	for (size_t i = 0; i < vb.size(); ++i) {
		bl[vb[i]] = lca;
		if (vb[i] == lca)  break;
		--bridges;
	}
}

//добавление нового ребра
void add_edge(int a, int b) {
	a = get(a);   b = get(b);
	if (a == b)  return;

	int ca = get_comp(a),
		cb = get_comp(b);
	if (ca != cb) {
		++bridges;
		if (size_[ca] > size_[cb]) {
			swap(a, b);
			swap(ca, cb);
		}
		make_root(a);
		ancestor[a] = comp[a] = b;
		size_[cb] += size_[a];
	}
	else
		merge_path(a, b);
}*/
/*#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 1000;
vector<int> g[MAXN];
bool used[MAXN];
int timer, time_in[MAXN], fup[MAXN];

void dfs(int v, int p = -1) {
	used[v] = true;
	time_in[v] = fup[v] = ++timer;
	for (size_t i = 0; i < g[v].size(); ++i) {
		int to = g[v][i];
		if (to == p)  continue;
		if (used[to])
			fup[v] = min(fup[v], time_in[to]);
		else {
			dfs(to, v);
			fup[v] = min(fup[v], fup[to]);
			if (fup[to] > time_in[v])
				//IS_BRIDGE(v, to);
				;
		}
	}
}

void find_bridges() {
	timer = 0;
	for (int i = 0; i < n; ++i)
		used[i] = false;
	for (int i = 0; i < n; ++i)
		if (!used[i])
			dfs(i);
}*/
/*
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <queue>

using namespace std;

struct vertex
{
	int visited;
	vector<pair<int,int>> neighbor;
};

vector<vertex> graph;
vector<int> bridges;
vector<int> time_in;
vector<int> low;
int timer;
int count_ = 0;



void dfs(int vertices, int previous_v = -1)
{
	graph[vertices].visited = 1;
	time_in[vertices] = low[vertices] = ++timer;
	for (size_t i = 0; i < graph[vertices].neighbor.size(); ++i)
	{
		int to = graph[vertices].neighbor[i].first;
		int to_index = graph[vertices].neighbor[i].second;
		if (to == previous_v) continue;
		if (graph[to].visited)
		{
			low[vertices] = min(low[vertices], time_in[to]);
		}
		else
		{
			dfs(to, vertices);
			low[vertices] = min(low[vertices], low[to]);
			if (low[to] > time_in[vertices])
			{
				bridges[to_index] = 1;
			}
		}
	}
}

void bfs(int vertices)
{
	queue <int> q;
	q.push(vertices);
	graph[vertices].visited = 1;
	while (!q.empty())
	{
		vertices = q.front();
		q.pop();
	}
}

int bridge_count()
{
	int bridge_countt = 0;
	timer = 0;
	for (size_t i = 0; i < graph.size(); ++i)
	{
		graph[i].visited = 0;
	}
	for (size_t i = 0; i < graph.size(); ++i)
	{
		if (!graph[i].visited)
		{
			//bridge_countt += dfs(i);
		}
	}
	return bridge_countt;
}

int main()
{
	ifstream file;
	file.open("test.txt");
	
	int n, m;
	file >> n >> m;
	//cin >> n >> m;

	graph.resize(n);
	time_in.resize(n);
	low.resize(n);
	bridges.resize(m);

	for (int i = 0; i < m; ++i)
	{
		int a, b;
		file >> a >> b;
		//cin >> a >> b;
		graph[--a].neighbor.push_back(make_pair(--b, i));
		graph[b].neighbor.push_back(make_pair(a, i));
	}
	file.close();
	dfs(0);
	for (size_t i = 0; i < graph.size(); ++i)
	{
		graph[i].visited = 0;
	}
	return 0;
}*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <set>

using namespace std;

const int MAXN = 10;

int n;
int bridges;         //количество мостов
int par[MAXN];      //предок в системе непересекающихся множеств для компонент связности,
int bl[MAXN];      //Система непересекающихся множеств для компонент двусвязности
int comp[MAXN];   //Система непересекающихся множеств для компонент связности
int size_[MAXN]; //размкры компонент comp
set<pair<int,int>> bridgess;

void init()//инициализация
{
	for (int i = 0; i < n; ++i) 
	{
		bl[i] = comp[i] = i;
		size_[i] = 1;
		par[i] = -1;
	}
	bridges = 0;
}


int get(int v) //возвращающая лидера компоненты двусвязности
{
	if (v == -1)  return -1;
	return bl[v] == v ? v : bl[v] = get(bl[v]);
}

int get_comp(int v) // возвращает лидера компоненты связности
{
	v = get(v);
	return comp[v] == v ? v : comp[v] = get_comp(comp[v]);
}

void make_root(int v) //Функция переподвешивания дерева
{
	v = get(v);
	int root = v,
		child = -1;
	while (v != -1) {
		int p = get(par[v]);
		par[v] = child;
		comp[v] = root;
		child = v;  v = p;
	}
	size_[root] = size_[child];
}


int cu, u[MAXN];

void merge_path(int a1, int b1) //Функция обнаружения и сжатия пути
{
	++cu;
	int a = a1;
	int b = b1;
	vector<int> va, vb;
	int lca = -1;
	for (;;) {
		if (a != -1) {
			a = get(a);
			va.push_back(a);

			if (u[a] == cu) {
				lca = a;
				break;
			}
			u[a] = cu;

			a = par[a];
		}

		if (b != -1) {
			b = get(b);
			vb.push_back(b);

			if (u[b] == cu) {
				lca = b;
				break;
			}
			u[b] = cu;

			b = par[b];
		}
	}

	for (size_t i = 0; i < va.size(); ++i) {
		bl[va[i]] = lca;
		if (va[i] == lca)  break;
		--bridges;
		//bridgess.erase(make_pair(a, b));
		bridgess.erase(bridgess.find(make_pair(a,b)));
		
	}
	for (size_t i = 0; i < vb.size(); ++i) {
		bl[vb[i]] = lca;
		if (vb[i] == lca)  break;
		--bridges;
		//bridgess.erase(make_pair(a, b));
		bridgess.erase(bridgess.find(make_pair(a, b)));
	}
}


void add_edge(int a1, int b1) //функция обработки запросов на добавление нового ребра
{
	int a = get(a1);  int b = get(b1);
	if (a == b)  return;

	int ca = get_comp(a),
		cb = get_comp(b);
	if (ca != cb) {
		++bridges;
		bridgess.insert(make_pair(a, b));
		if (size_[ca] > size_[cb]) {
			swap(a, b);
			swap(ca, cb);
		}
		make_root(a);
		par[a] = comp[a] = b;
		size_[cb] += size_[a];
	}
	else
		merge_path(a, b);
}

int main()
{
	ifstream file;
	file.open("test.txt");
	
	int  m;
	file >> n >> m;
	//cin >> n >> m;
	init();
	

	for (int i = 0; i < m; ++i)
	{
		int a, b;
		file >> a >> b;
		//cin >> a >> b;
		add_edge(--a, --b);
	}
	file.close();
	cout << bridges;
	return 0;
}
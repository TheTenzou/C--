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
/*
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <set>
#include <queue>

using namespace std;

const int MAXN = 10;

int n;
int bridges_count;   //количество мостов
int par[MAXN];      //предок в системе непересекающихся множеств для компонент связности,
int bl[MAXN];      //Система непересекающихся множеств для компонент двусвязности
int comp[MAXN];   //Система непересекающихся множеств для компонент связности
int size_[MAXN]; //размкры компонент comp

set<pair<int, int>> bridges;

void init()//инициализация
{
	for (int i = 0; i < n; ++i)
	{
		bl[i] = comp[i] = i;
		size_[i] = 1;
		par[i] = -1;
	}
	bridges_count = 0;
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

void merge_path(int a, int b) //Функция обнаружения и сжатия пути
{
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
		int tmp = bl[va[i]];
		bl[va[i]] = lca;
		if (va[i] == lca)  break;
		--bridges_count;

		int a2 = a;
		int b2 = b;
		if (a2 == -1)
			a2 = tmp;
		if (b2 == -1)
			b2 = tmp;
		if (a2 > b2)
			swap(a2, b2);
		bridges.erase(make_pair(a2, b2));

		//bridgess.erase(bridgess.find(make_pair(a, b)));

	}
	for (size_t i = 0; i < vb.size(); ++i) {
		int tmp = bl[vb[i]];
		bl[vb[i]] = lca;
		if (vb[i] == lca)  break;
		--bridges_count;

		int a2 = a;
		int b2 = b;
		if (a2 == -1)
			a2 = tmp;
		if (b2 == -1)
			b2 = tmp;
		if (a2 > b2)
			swap(a2, b2);
		bridges.erase(make_pair(a2, b2));

		//bridgess.erase(bridgess.find(make_pair(a, b)));
	}
}


void add_edge(int a, int b) //функция обработки запросов на добавление нового ребра
{
	a = get(a);  b = get(b);
	if (a == b)  return;

	int ca = get_comp(a),
		cb = get_comp(b);
	if (ca != cb) {
		++bridges_count;

		int a2 = a;
		int b2 = b;
		if (a2 > b2)
			swap(a2, b2);
		bridges.insert(make_pair(a2, b2));

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

struct vertex
{
	int visited;
	int weight;
	vector<int> neighbor;
};

vector<vertex> graph_bridges;

int dfs1(int a)
{
	graph_bridges[a].visited = 1;
	int tmp1, tmp2 , max = 0, maxList = a;

	for (size_t i = 0; i < graph_bridges[a].neighbor.size(); ++i)
	{
		if (!graph_bridges[graph_bridges[a].neighbor[i]].visited)
		{
			tmp2 = dfs1(graph_bridges[a].neighbor[i]);
			tmp1 = graph_bridges[graph_bridges[a].neighbor[i]].weight;
			if (tmp1 > max)
			{
				max = tmp1;
				maxList = tmp2;
			}
		}
	}
	graph_bridges[a].weight = max + 1;
	return maxList;
}

int dfs2(int a)
{
	graph_bridges[a].visited = 1;
	int tmp = 0, max = 0;

	for (size_t i = 0; i < graph_bridges[a].neighbor.size(); ++i)
	{
		if (!graph_bridges[graph_bridges[a].neighbor[i]].visited)
		{
			tmp = dfs2(graph_bridges[a].neighbor[i]);
			if (tmp > max)
			{
				max = tmp;
			}
		}
	}
	return max + 1;
}

/*int f = 0, fm = 0;

void bfs(int a)
{
	queue <pair<int, int>> q;
	q.push(make_pair(a, 0));
	graph_bridges[a].visited = 1;


	while (!q.empty())
	{
		a = q.front().first;
		int p = q.front().second;
		q.pop();

		if (p > fm)
		{
			f = a;
			fm = p;
		}

		for (int i = 0; i < graph_bridges[a].neighbor.size(); ++i)
		{
			if (!graph_bridges[graph_bridges[a].neighbor[i]].visited)
			{
				q.push(make_pair(graph_bridges[a].neighbor[i], p + 1));
				graph_bridges[graph_bridges[a].neighbor[i]].visited = 1;
			}
		}
	}
}*//*

vector<int> bfs(int a)
{
	vector<int> distance(n,-1);
	distance[a] = 0;
	queue <int> q;
	q.push(a);
	while (!q.empty())
	{
		a = q.front();
		q.pop();
		for (size_t i = 0; i < graph_bridges[a].neighbor.size(); ++i)
		{
			if (distance[graph_bridges[a].neighbor[i]] == -1)
			{
				distance[graph_bridges[a].neighbor[i]] = distance[a] + 1;
				q.push(graph_bridges[a].neighbor[i]);
			}
		}
	}
	return distance;
}

int diametrTree(int a)
{
	int u = 0;
	vector<int> distance = bfs(a);
	for (int i = 0; i < n; ++i)
	{
		if (distance[i] > distance[u])
		{
			u = i;
		}
	}
	distance = bfs(u);
	u = 0;
	for (int i = 0; i < n; ++i)
	{
		if (distance[i] > distance[u])
		{
			u = i;
		}
	}
	return distance[u];
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


	graph_bridges.resize(n);
	int k = bridges.begin()->first;
	while (bridges.size())
	{
		graph_bridges[bridges.begin()->first].neighbor.push_back(bridges.begin()->second);
		graph_bridges[bridges.begin()->second].neighbor.push_back(bridges.begin()->first);
		bridges.erase(bridges.begin());
	}
	*/
	/*k = dfs1(k);
	for (size_t i = 0; i < n; ++i)
	{
		graph_bridges[i].visited = 0;
	}
	cout << dfs2(k) - 1;*/

	/*k = dfs1(k);
	int max = 0;
	for (size_t i = 0; i < n; ++i)
	{
		for (size_t j = 0; j < n; ++j)
		{
			graph_bridges[j].visited = 0;
		}
		int tmp = dfs2(i);
		if (tmp > max) max = tmp;
	}
	cout << max - 1;*/
	/*bfs(k);
	for (size_t i = 0; i < n; ++i)
	{
		graph_bridges[i].visited = 0;
	}
	bfs(f);
	cout << fm;*//*
	cout << diametrTree(k);
	return 0;
}*/

#include <iostream>
#include <vector>
#include <fstream>
#include <queue>

using namespace std;

struct vertex
{
	int visited;
	vector<int> neighbor;
};

vector<vertex> graph;
vector<vertex> graph_bridges;
vector<pair<int, int>> bridges;
vector<int> time_in;
vector<int> fup;
vector<int> parent;
vector<int> rank_;
int timer;
int count_ = 0;
int st = 0;
int n, m;

void init()
{
	for (size_t i = 0; i < parent.size(); ++i)
	{
		rank_[i] = 1;
		parent[i] = i;
	}
}

int get(int x)
{
	return (parent[x] == x ? x : parent[x] = get(parent[x]));
}

void link(int a, int b)
{
	a = get(a);
	b = get(b);
	if (a == b) return;
	if (rank_[a] > rank_[b])
	{
		swap(a, b);
	}
	parent[a] = b;
	rank_[b] += rank_[a];
}

void dfs(int vertices, int previous_v = -1)
{
	graph[vertices].visited = 1;
	time_in[vertices] = fup[vertices] = ++timer;
	for (size_t i = 0; i < graph[vertices].neighbor.size(); ++i)
	{
		int to = graph[vertices].neighbor[i];
		int to_index = graph[vertices].neighbor[i];
		if (to == previous_v) continue;
		if (graph[to].visited)
		{
			fup[vertices] = min(fup[vertices], time_in[to]);
		}
		else
		{
			dfs(to, vertices);
			fup[vertices] = min(fup[vertices], fup[to]);
			if (fup[to] > time_in[vertices])
			{
				bridges.push_back(make_pair(vertices, to));
			}
			else
			{
				link(vertices, to);
			}
		}
	}
}

void build()
{
	for (size_t i = 0; i < bridges.size(); ++i)
	{
		int x = get(bridges[i].first);
		int y = get(bridges[i].second);
		st = x;
		graph_bridges[x].neighbor.push_back(y);
		graph_bridges[y].neighbor.push_back(x);
	}
}
pair<int,int> bfs(int x)
{
	vector<int> distance(n, -1);
	distance[x] = 0;
	queue<int> q;
	q.push(x);
	int last = 0;
	while (!q.empty())
	{
		last = q.front();
		q.pop();

		for (size_t i = 0; i < graph_bridges[last].neighbor.size(); ++i)
		{
			//if (distance[graph_bridges[last].neighbor[i]] > distance[last] + 1)
			if (distance[graph_bridges[last].neighbor[i]] == -1)
			{
				distance[graph_bridges[last].neighbor[i]] = distance[last] + 1;
				q.push(graph_bridges[last].neighbor[i]);
			}
		}
	}
	return make_pair(last, distance[last]);
}

/*vector<int> bfs(int a)
{
	vector<int> distance(n, -1);
	distance[a] = 0;
	queue <int> q;
	q.push(a);
	while (!q.empty())
	{
		a = q.front();
		q.pop();
		for (size_t i = 0; i < graph_bridges[a].neighbor.size(); ++i)
		{
			if (distance[graph_bridges[a].neighbor[i]] == -1)
			{
				distance[graph_bridges[a].neighbor[i]] = distance[a] + 1;
				q.push(graph_bridges[a].neighbor[i]);
			}
		}
	}
	return distance;
}*/

int main()
{
	ifstream file;
	file.open("test.txt");

	
	file >> n >> m;
	//cin >> n >> m;

	graph.resize(n);
	time_in.resize(n);
	fup.resize(n);
	parent.resize(n);
	rank_.resize(n);
	init();
	graph_bridges.resize(n);
	for (int i = 0; i < m; ++i)
	{
		int a, b;
		file >> a >> b;
		//cin >> a >> b;
		graph[--a].neighbor.push_back(--b);
		graph[b].neighbor.push_back(a);
	}
	file.close();
	dfs(0);
	build();
	pair<int, int> tmp1 = bfs(st);
	pair<int, int> tmp2 = bfs(tmp1.first);
	cout << tmp2.second;
	return 0;
}
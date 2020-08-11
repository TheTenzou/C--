#include<stdio.h>
#include<algorithm>
#include<cstring>
#include<iostream>
using namespace std;

const int INF = 0x3f3f3f3f;

struct edge
{
	int v, u, last, w, id;
};
edge treeEdges[400010]; //списки ребер
edge edges[400010]; //список ребер графа

int n, m, tot = 0;
int num = 0;
int head[200010]; // масив вершин дерева со сылками на список их ребер
int ancestor[200010][20]; // запоминаем предков
int st[200010][20]; // запаминаем те вершины в которые входит ребро вес которого меньше предыдуших
int depth[200010]; // глубина вершины в дереве подвешаном за первыу вершину
int answer[200010]; // ответ
int to[200010]; // id вершин по которым пришли в i вершину
int parent[200010]; // система не пересекаюшихся множеств
int used[200010]; //проверка на нализие вершины в дереве

bool cmp(const edge &a, const edge &b)
{
	return a.w < b.w;
}

int getfather(int x)
{
	if (x == parent[x]) return x;
	return parent[x] = getfather(parent[x]);
}

void add(int u, int v, int w, int id)
{
	num++;
	treeEdges[num].v = v;
	treeEdges[num].id = id;
	treeEdges[num].w = w;
	treeEdges[num].last = head[u];
	head[u] = num;
}

void dfs(int u, int f)
{
	ancestor[u][0] = f;
	for (int i = 1; i <= 18; i++)
	{
		ancestor[u][i] = ancestor[ancestor[u][i - 1]][i - 1];
		st[u][i] = max(st[u][i - 1], st[ancestor[u][i - 1]][i - 1]);
	}
	for (int i = head[u]; i; i = treeEdges[i].last)
	{
		int v = treeEdges[i].v;
		if (v == f) continue;
		to[v] = treeEdges[i].id;
		st[v][0] = treeEdges[i].w;
		depth[v] = depth[u] + 1;
		dfs(v, u);
	}
}

int lca(int u, int v, int &d)
{
	d = 0;
	if (depth[u] < depth[v]) swap(u, v);
	//обходим и ищем ощего предка и макс ребро на этом пути иесть ответ - 1
	//пока глубена одного больше другого
	for (int i = 18; i >= 0; i--)
	{
		if (depth[ancestor[u][i]] >= depth[v])
		{
			d = max(d, st[u][i]);
			u = ancestor[u][i];
		}
	}
	if (u == v) return u;
	//если нашли предка то выходим 
	// если нет то начинаем подыматся по обеим вершинам и 
	//макс ребро на этом пути иесть ответ - 1
	for (int i = 18; i >= 0; i--)
	{
		if (ancestor[u][i] != ancestor[v][i])
		{
			d = max(d, st[u][i]);
			d = max(d, st[v][i]);
			u = ancestor[u][i];
			v = ancestor[v][i];
		}
	}
	// сравниваем с самим ребром для которого ишеи
	d = max(d, st[u][0]);
	d = max(d, st[v][0]);
	return ancestor[u][0];
}

void Kruscal()
{
	sort(edges + 1, edges + m + 1, cmp);
	for (int i = 1; i <= n; i++) parent[i] = i;
	for (int i = 1; i <= m; i++)
	{
		int u = edges[i].u, v = edges[i].v, w = edges[i].w;
		int x = getfather(u), y = getfather(v);
		if (x != y)
		{
			parent[x] = y, used[i] = 1;
			add(u, v, w, edges[i].id);
			add(v, u, w, edges[i].id);
			tot++;
		}
		if (tot == n - 1) return;
	}
}

void modify(int u, int v, int d)
{
	u = getfather(u);
	while (depth[u] > depth[v])
	{
		//проверяем меньши ли вес ранее посчитаный ответ весса для потециального ребра которое заменит
		answer[to[u]] = min(answer[to[u]], d);
		int y = getfather(ancestor[u][0]); // anc[u][0] ближай ший предок
		parent[u] = y;
		u = getfather(u);
	}
}

int main()
{
	cin >> n >> m;
	for (int i = 1; i <= m; i++)
	{
		cin >> edges[i].u >> edges[i].v >> edges[i].w;
		edges[i].id = i;
	}
	Kruscal();
	dfs(1, 1);
	memset(answer, INF, sizeof(answer));
	for (int i = 1; i <= n; i++)
	{
		parent[i] = i;
	}
	for (int i = 1; i <= m; i++)
	{
		if (used[i]) continue;
		int u = edges[i].u;
		int v = edges[i].v;
		int f = lca(u, v, answer[edges[i].id]);
		answer[edges[i].id]--;
		modify(u, f, edges[i].w - 1);
		modify(v, f, edges[i].w - 1);
	}
	for (int i = 1; i <= m; i++)
	{
		if (answer[i] == INF)
		{
			cout << "-1\n";
		}
		else
		{
			cout << answer[i] << ';
		}
	}
	return 0;
}
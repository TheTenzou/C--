#include<stdio.h>
#include<algorithm>
#include<cstring>
#include <iostream>
#include <vector>

using namespace std;

const int INF = 0x3f3f3f3f;

struct edge
{
	int v;
	int u;
	int last;
	int weight;
	int id;
}ed[400010];// , e[400010];
struct tree
{

};
vector<edge> edges;
vector<int> parent;
vector<int> tree;

int n, m, tot = 0, num = 0, head[200010], anc[200010][20], st[200010][20];
int dep[200010], ans[200010], to[200010], fa[200010], used[200010];

bool cmp(const edge &a, const edge &b)
{
	return a.weight < b.weight;
}

int find(int x)
{
	if (x == parent[x]) return x;
	return parent[x] = find(parent[x]);
}

void add(int u, int v, int w, int id)
{
	num++;
	ed[num].v = v;
	ed[num].id = id;
	ed[num].weight = w;
	ed[num].last = head[u];
	head[u] = num;
	/*
	edge tmp;
	tmp.v = v;
	tmp.id = id;
	tmp.weight = w;
	*/
}

void dfs(int u, int f)
{
	anc[u][0] = f;
	for (int i = 1; i <= 18; i++)
	{
		anc[u][i] = anc[anc[u][i - 1]][i - 1];
		st[u][i] = max(st[u][i - 1], st[anc[u][i - 1]][i - 1]);
	}
	for (int i = head[u]; i; i = ed[i].last)
	{
		int v = ed[i].v;
		if (v == f) continue;
		to[v] = ed[i].id;
		st[v][0] = ed[i].weight;
		dep[v] = dep[u] + 1;
		dfs(v, u);
	}
}

int lca(int u, int v, int &d)
{
	d = 0;
	if (dep[u] < dep[v]) swap(u, v);
	for (int i = 18; i >= 0; i--)
		if (dep[anc[u][i]] >= dep[v])
		{
			d = max(d, st[u][i]);
			u = anc[u][i];
		}
	if (u == v) return u;
	for (int i = 18; i >= 0; i--)
		if (anc[u][i] != anc[v][i])
		{
			d = max(d, st[u][i]), d = max(d, st[v][i]);
			u = anc[u][i], v = anc[v][i];
		}
	d = max(d, st[u][0]), d = max(d, st[v][0]);
	return anc[u][0];
}

void Kruscal()
{
	sort(edges.begin() , edges.end(), cmp);

	for (size_t i = 0; i < n; i++)
	{
		parent.push_back(i);
	}
	for (int i = 0; i < m; i++)
	{
		int u = edges[i].u;
		int v = edges[i].v;
		int x = find(u);
		int y = find(v);
		if (x != y)
		{
			parent[x] = y;
			used[i] = 1;
			add(u, v, edges[i].weight, edges[i].id);
			add(v, u, edges[i].weight, edges[i].id);
			tot++;
		}
		if (tot == n - 1) return;
	}
}

void modify(int u, int v, int d)
{
	u = find(u);
	while (dep[u] > dep[v])
	{
		ans[to[u]] = min(ans[to[u]], d);
		int y = find(anc[u][0]);
		fa[u] = y;
		u = find(u);
	}
}

int main()
{

	cin >> n >> m;
	for (int i = 0; i < m; i++)
	{
		edge tmp;
		cin >> tmp.u >> tmp.v >> tmp.weight;
		tmp.id = i;
		edges.push_back(tmp);
	}
	Kruscal();
	dfs(1, 1);
	memset(ans, INF, sizeof(ans));
	for (int i = 1; i <= n; i++) fa[i] = i;
	for (int i = 1; i <= m; i++)
	{
		if (used[i]) continue;
		int u = e[i].u, v = e[i].v, f = lca(u, v, ans[e[i].id]);
		ans[e[i].id]--;
		modify(u, f, e[i].weight - 1);
		modify(v, f, e[i].weight - 1);
	}
	for (int i = 1; i <= m; i++) if (ans[i] == INF) printf("-1\n");
	else printf("%d\n", ans[i]);
	system("pause");
	return 0;
}
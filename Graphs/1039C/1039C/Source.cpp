#include <set>
#include <iostream>
#include<algorithm>

using namespace std;
#define N 500001
#define MOD 1000000007

set<long long>s;

struct edges
{ 
	long long x, v1, v2; 
};
edges a[N];

long long n, m, k, c[N], parent[N], size_, count_, ans;

bool cmp(edges x, edges y) 
{ 
	return x.x < y.x; 
}

long long find(long long x)
{ 
	if (parent[x] == x)
		return x;
	return parent[x] = find(parent[x]); 
}

void add(long long u, long long v)
{
	s.insert(u), s.insert(v);
	if (find(u) != find(v))
	{
		parent[find(u)] = find(v);
		size_--;
	}
}

long long fpow(long long x, long long y)
{ 
	if (y)
	{
		if (y & 1)
		{
			return x * fpow(x, y - 1) % MOD;
		}
		else
		{
			return fpow(x * x % MOD, y / 2);
		}
	}
	else
	{
		return 1;
	}
	//return y ? (y & 1 ? x * qow(x, y - 1) % MOD : qow(x * x % MOD, y / 2)) : 1; 
}

int main()
{
	//scanf("%I64d%I64d%I64d", &n, &m, &k);
	cin >> n >> m >> k;
	for (long long i = 1; i <= n; i++)
	{
		//scanf("%I64d", &c[i]), fa[i] = i;
		cin >> c[i];
		parent[i] = i;
	}
	for (long long i = 1; i <= m; i++)
	{
		//scanf("%I64d%I64d", &a[i].u, &a[i].v),
			//a[i].x = c[a[i].u] ^ c[a[i].v];
		cin >> a[i].v1 >> a[i].v2;
		a[i].x = c[a[i].v1] ^ c[a[i].v2];
	}
	sort(a + 1, a + m + 1, cmp);

	for (long long i = 1; i <= m;)
	{
		long long j = i;
		size_ = n; 
		for (auto x : s)
		{
			parent[x] = x;
		}
		s.clear();
		//for ()
		while (j <= m && a[j].x == a[i].x)
		{
			add(a[j].v1, a[j].v2);
			j++;
		}
		i = j;
		count_++;
		ans += fpow(2, size_);
		ans %= MOD;
	}
	cout << (ans + (fpow(2, k) + MOD - count_) * fpow(2, n) % MOD) % MOD;
	return 0;
}
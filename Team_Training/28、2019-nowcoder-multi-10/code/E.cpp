#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long LL;
#define N 1000000 + 5

int n, k, X[N], Y[N], Ord[N];
LL Fix[N];

LL Get(int x, int y, int dep)
{
	if (dep == 0)
		return 1;
	int field = (x >= (1 << dep - 1)) << 1 | (y >= (1 << dep - 1));
	switch (field)
	{
		case 0 : return Get(y, x, dep - 1);
		case 1 : return (3LL << (2 * (dep - 1))) + Get((1 << dep) - 1 - y, (1 << dep - 1) - 1 - x, dep - 1);
		case 2 : return (1LL << (2 * (dep - 1))) + Get(x - (1 << dep - 1), y, dep - 1);
		case 3 : return (2LL << (2 * (dep - 1))) + Get(x - (1 << dep - 1), y - (1 << dep - 1), dep - 1);
	}
}

int main()
{
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; i ++)
	{
		scanf("%d%d", X + i, Y + i);
		Fix[i] = Get(X[i] - 1, Y[i] - 1, k);
		Ord[i] = i;
	}
	sort(Ord + 1, Ord + n + 1, [](int u, int v){
		return Fix[u] < Fix[v];
	});
	for (int i = 1; i <= n; i ++)
		printf("%d %d\n", X[Ord[i]], Y[Ord[i]]);
	return 0;
}

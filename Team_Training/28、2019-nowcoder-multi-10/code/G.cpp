#include <cmath>
#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long LL;
#define N 300 + 5
#define M 90000 + 5
#define mp make_pair

int n, sz, X[N], Y[N], Ord[N];
double ans;

LL Dot(int x_1, int y_1, int x_2, int y_2)
{
	return 1LL * x_1 * x_2 + 1LL * y_1 * y_2;
}

LL Cross(int x_1, int y_1, int x_2, int y_2)
{
	return 1LL * x_1 * y_2 - 1LL * x_2 * y_1;
}

LL Cross(int st, int t_1, int t_2)
{
	int x_1 = X[t_1] - X[st], y_1 = Y[t_1] - Y[st];
	int x_2 = X[t_2] - X[st], y_2 = Y[t_2] - Y[st];
	return Cross(x_1, y_1, x_2, y_2);
}

struct Point
{
	int x, y;
	Point(){}
	Point(int x_1, int y_1, int x_2, int y_2) : Point(x_2 - x_1, y_2 - y_1) {}
	Point(int x, int y) : x(x), y(y) {
		Simplify();
	}
	void Simplify()
	{
		if (y < 0 || (y == 0 && x < 0))
			x = -x, y = -y;
	}
	double len() const
	{
		return sqrt(1LL * x * x + 1LL * y * y);
	}
	bool operator < (const Point &obj) const
	{
		return Cross(x, y, obj.x, obj.y) > 0;
	}
	bool operator == (const Point &obj) const
	{
		return !(*this < obj) && !(obj < *this);
	}
};

LL Cross(const Point &lhs, const Point &rhs)
{
	return Cross(lhs.x, lhs.y, rhs.x, rhs.y);
}

LL Dot(const Point &lhs, const Point &rhs)
{
	return Dot(lhs.x, lhs.y, rhs.x, rhs.y);
}

struct Opt
{
	Point k;
	int u, v;
	Opt() {}
	Opt(Point k, int u, int v) : k(k), u(u), v(v) {}
	bool operator < (const Opt& obj) const
	{
		return k < obj.k;
	}
}O[M];

template <typename Value>
inline int sgn(Value x)
{
	if (x > 0) return 1;
	if (x < 0) return -1;
	return 0;
}

bool CheckInOneLine()
{
	for (int i = 1; i < n; i ++)
		for (int j = i + 1; j < n; j ++)
			for (int k = j + 1; k <= n; k ++)
				if (Cross(i, j, k) != 0)
					return false;
	return true;
}

double Dis(int u, int v)
{
	int _x = X[u] - X[v], _y = Y[u] - Y[v];
	return sqrt(1LL * _x * _x + 1LL * _y * _y);
}

double Calc(const Point &prek, const Point &nxtk)
{
	int lm = Ord[n / 2], rm = Ord[n / 2 + 1];
	Point v(X[rm] - X[lm], Y[rm] - Y[lm]);
	double res;
	if (sgn(Dot(prek, v)) * sgn(Dot(nxtk, v)) < 0)
		res = Dis(lm, rm);
	else
	{
		double ldis = abs(Cross(prek, v)) / prek.len();
		double rdis = abs(Cross(nxtk, v)) / nxtk.len();
		res = max(ldis, rdis);
	}
	return res / 2.0;
}

int main()
{
	while (~scanf("%d", &n))
	{
		for (int i = 1; i <= n; i ++)
		{
			scanf("%d%d", X + i, Y + i);
			Ord[i] = i;
		}
		sort(Ord + 1, Ord + n + 1, [](int u, int v) {
			return mp(Y[u], X[u]) < mp(Y[v], X[v]);
		});
		if (CheckInOneLine())
		{
			printf("%.9f\n", Dis(Ord[n / 2], Ord[n / 2 + 1]) / 2.0);
			continue ;
		}
		sz = 0;
		for (int i = 1; i < n; i ++)
			for (int j = i + 1; j <= n; j ++)
				O[++ sz] = Opt(Point(X[Ord[i]], Y[Ord[i]], X[Ord[j]], Y[Ord[j]]), Ord[i], Ord[j]);
		sort(O + 1, O + sz + 1);
		O[0] = O[sz], O[0].k.x = -O[0].k.x, O[0].k.y = -O[0].k.y;
		ans = 0.0;
		for (int l = 1, r, pre = 0; l <= sz; pre = l, l = r)
		{
			ans = max(ans, Calc(O[pre].k, O[l].k));
			for (r = l; r <= sz && O[l].k == O[r].k; r ++) ;
			for (int i = 2; i <= n; i ++)
				for (int j = i; j > 1; j --)
				{
					if (Point(X[Ord[j]] - X[Ord[j - 1]], Y[Ord[j]] - Y[Ord[j - 1]]) == O[l].k)
						swap(Ord[j], Ord[j - 1]);
					else break ;
				}
		}
		printf("%.9f\n", ans);
	}
	return 0;
}

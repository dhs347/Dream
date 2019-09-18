// 无重点、三点共线
// O(n^2log_2n)
struct P { int x, y, ind, u, v; };
namespace MinAreaTri {
	const int N = 2020;
	const ll inf = 4e18;
	int n, m, pos[N];
	P p[N], l[N * N];
	bool cmp(const P &x, const P &y) { return det(x, y) < 0; }
	void solve() {
		sort(p + 1, p + 1 + n);
		rep(i, 1, n + 1) p[i].ind = i, pos[i] = i;
		m = 0; rep(i, 1, n + 1) rep(j, i + 1, n + 1) {
			l[++m] = p[i] - p[j];
			if(l[m].x < 0) l[m].x *= -1, l[m].y *= -1;
			else if(l[m].x == 0 && l[m].y < 0) l[m].y *= -1;
			l[m].u = i, l[m].v = j;
		}
		sort(l + 1, l + 1 + m, cmp);
		mi = inf, ma = 0;
		rep(i, 1, m + 1) {
			int u = l[i].u, v = l[i].v;
			int pu = pos[u], pv = pos[v];
			if(pu > pv) swap(u, v), swap(pu, pv);
			if(pu == 1 || pv == n) continue;
			mi = min(mi, area(p[pu - 1], p[pu], p[pv + 1], p[v]));
			ma = max(ma, area(p[1], p[pu], p[n], p[v]));
			swap(p[pu], p[pv]);
			swap(pos[u], pos[v]);
		}
		cout << mi << " " << ma << endl;
	}
}

const int N = 1010;
int n; P p[N], q[N]; ll s[N];
namespace CNT {
	bool gao(P a) { return a.y > 0 || (a.y == 0 && a.x >= 0); }
	bool cmp(P a, P b) {
		bool o = gao(a), t = gao(b);
		if(o != t) return o > t;
		return det(a, b) > 0;
	}
	void solve(int u, ll &ans) {
		rep(i, 1, n + 1) q[i] = p[i]; swap(q[1], q[u]);
		rep(i, 2, n + 1) q[i] = q[i] - p[u];
		sort(q + 2, q + n + 1, cmp);
		int k = n; while(k >= 2 && q[k].y <= 0) --k;
		int j = k, cnt = 0;
		per(i, k + 1, n + 1) {
			while(j >= 2 && det(q[j], q[i]) > 0) --j, ++cnt;
			s[i] = s[i + 1] + cnt;
		}
		int c = j = k + 1;
		rep(i, 2, k + 1) {
			while(c <= n && det(q[i], q[c]) > 0) ++c;
			while(j <= n && det(q[i], q[j]) >= 0) ++j;
			ans += s[j] + (n - j + 1) * 1ll * (c - k - 1);
		}
	}
	ll solve() {
		ll ans = 0; rep(i, 1, n + 1) solve(i, ans);
		return ans;
	}
}

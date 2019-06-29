// 曼哈顿最小距离生成树（可以求最大）
// 这份代码处理的区域是 Y 轴右转 45 度
namespace MMST {
#define lb(x) ((x) & -(x))
	const int N = 101010, inf = 1e9 + 7;

	vector<pair<int, pii> > E;
	vi V;

	// 最大只要把这里所有 mi 改成 ma 就行了
	pii mi[N];
	void init() { rep(i, 1, sz(V) + 1) mi[i] = mp(inf, inf); }
	void upd(int p, pii c) {
		p = sz(V) + 1 - p;
		for( ; p <= sz(V); p += lb(p)) mi[p] = min(mi[p], c);
	}
	pii qry(int p) {
		p = sz(V) + 1 - p;
		pii ans = mp(inf, inf);
		for( ; p >= 1; p ^= lb(p)) ans = min(ans, mi[p]);
		return ans;
	}
	int F(int x) { return lower_bound(all(V), x) - V.begin() + 1; }
	void _solve(vector<pair<pii, int> > v) {
		V.clear();
		rep(i, 0, sz(v)) v[i].fi.se -= v[i].fi.fi, V.pb(v[i].fi.se);
		sort(all(V));
		V.erase(unique(all(V)), V.end());
		sort(all(v));
		reverse(all(v));
		init();
		for(auto u : v) {
			pii t = qry(F(u.fi.se));
			int s = u.fi.fi * 2 + u.fi.se;
			if(t.se != inf) E.pb(mp(t.fi - s, mp(t.se, u.se)));
			upd(F(u.fi.se), mp(s, u.se));
		}
	}
	void solve(vector<pair<pii, int> > v) {
		_solve(v);
		rep(i, 0, sz(v)) swap(v[i].fi.fi, v[i].fi.se);
		_solve(v);
		rep(i, 0, sz(v)) v[i].fi.fi *= -1;
		_solve(v);
		rep(i, 0, sz(v)) swap(v[i].fi.fi, v[i].fi.se);
		_solve(v);
	}
}

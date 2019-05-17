// zoj 2112 动态区间 k 大
const int N = 50505, M = 10101;
int n, m, a[N], rt[N<<1];
vi V, add, sub;
inline int rk(int x) { return lower_bound(all(V), x) - V.begin(); }
struct Q {
	bool op;
	int a, b, k;
}q[M];
struct Seg {
	static const int N = 2500005;//(::N + 32 * ::M) * 16;
	int cntn, cnt[N], ls[N], rs[N];
	void init() { fill_n(rt+1, n, cntn = 0); }
	void upd(int pre, int &now, int p, int c, int l, int r) {
		now = ++cntn;
		cnt[now] = cnt[pre] + c;
		ls[now] = ls[pre];
		rs[now] = rs[pre];
		if(l == r) return ;
		int mid = l+r>>1;
		if(p<=mid) upd(ls[pre], ls[now], p, c, l, mid);
		else upd(rs[pre], rs[now], p, c, mid+1, r);
	}
	int qry(int L, int R, int k, int l, int r) {
		if(l == r) return l;
		int mid = l+r>>1;
		int lc = 0;
		for(auto i : add) lc += cnt[ls[i]];
		for(auto i : sub) lc -= cnt[ls[i]];
		if(lc>=k) {
			rep(i, 0, sz(add)) add[i] = ls[add[i]];
			rep(i, 0, sz(sub)) sub[i] = ls[sub[i]];
			return qry(L, R, k, l, mid);
		} else {
			rep(i, 0, sz(add)) add[i] = rs[add[i]];
			rep(i, 0, sz(sub)) sub[i] = rs[sub[i]];
			return qry(L, R, k-lc, mid+1, r);
		}
	}
}seg;
struct Fenwick {
#define lb(x) ((x)&(-x))
	void init() { fill_n(rt+1+n, n, 0); }
	void upd(int x, int p, int c) {
		for(; x<=n; x+=lb(x)) seg.upd(rt[x+n], rt[x+n], p, c, 0, sz(V)-1);
	}
	int qry(int l, int r, int k) {
		add.clear();sub.clear();
		add.pb(rt[r]);sub.pb(rt[l-1]);
		int x = r;
		for(; x; x^=lb(x)) add.pb(rt[n+x]);
		x = l-1;
		for(; x; x^=lb(x)) sub.pb(rt[n+x]);
		return seg.qry(l, r, k, 0, sz(V)-1);
	}
}fw;
int main() {
	int T; cin >> T;
	while(T--) {
		cin >> n >> m;
		V.clear(); seg.init(); fw.init();
		///read
		rep(i, 1, n+1) cin >> a[i], V.pb(a[i]);
		rep(i, 1, m+1) {
			string s;
			cin >> s >> q[i].a >> q[i].b;
			q[i].op = (s[0]=='Q');
			if(s[0]=='Q') cin >> q[i].k;
			else V.pb(q[i].b);
		}
		///solve
		sort(all(V));
		V.erase(unique(all(V)), V.end());
		rep(i, 1, n+1) seg.upd(rt[i-1], rt[i], rk(a[i]), 1, 0, sz(V)-1);
		rep(i, 1, m+1) {
			if(q[i].op) { cout << V[fw.qry(q[i].a, q[i].b, q[i].k)] << endl;
			} else {
				int p = q[i].a, c = q[i].b;
				fw.upd(p, rk(a[p]), -1);
				fw.upd(p, rk(a[p] = c), 1);
			} } }
	return 0; }

// 如果有O2比较快, 不然可能比较慢要手写bitset 
namespace PX{
	const int N = :: N, M = sqrt(N) + 5;
	const int K = 7;
	int n, k, B, pos[K][N];
	bitset<N> s[K][M];
	vector<pii> V[K];
	
	struct node{
		int d[K];
	} a[N];
	
	void init(int _n, int _k) {
		n = _n; k = _k;
		rep(i, 1, n+1) rep(j, 0, k) cin >> a[i].d[j];
		rep(i, 1, n+1) rep(j, 0, k) V[j].pb(mp(a[i].d[j], i));
		rep(j, 0, k) sort(all(V[j]));
		rep(i, 1, n+1) 
			rep(j, 0, k) 
				a[i].d[j] = lower_bound(all(V[j]), mp(a[i].d[j], i)) - V[j].begin(), pos[j][a[i].d[j]] = i;
		B = sqrt(n);
		rep(j, 0, k) {
			bitset<N> tmp; int id = 1; 
			rep(i, 0, n) {
				tmp.set(pos[j][i]);
				if (i == id * B - 1) s[j][id++] = tmp; 
			}
		}
	}	 
	int qry(node a) {
		bitset<N> ans; ans.set();
		rep(j, 0, k) {	
			int ed = lower_bound(all(V[j]), mp(V[j][a.d[j]].fi, n+1)) - V[j].begin() - 1;
			bitset<N> tmp;int id = ed / B, st = id ? (id - 1) * B : 0;
			if (id) tmp = s[j][id - 1];
			rep(i, st, ed+1) tmp[pos[j][i]] = 1;
			ans &= tmp;
		}
		return ans.count();	
	}
}

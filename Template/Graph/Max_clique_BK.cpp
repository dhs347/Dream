//g[i][i] should be 0 
//g[i] is i's edge
//index [0..N)
//O(n ^ 3)
typedef unsigned long long T;
struct BK {
	static const int N = 100; T g[N];
	inline int ctz(T s){ return s ? __builtin_ctzll(s) : 64;}
	int n, ans;
	void ini(int _n) { 
		//per(i, 0, n = _n) g[i] = (1ull << n) - 1 - (1ull << i); }
		n = _n;rep(i, 0, n) g[i] = 0;
		rep(i, 0, n) rep(j, 0, n) if (a[i][j]) g[i] |= 1ull << j;
	}
	void gao(T cur, T can, T ban) {
		if (!can && !ban) { ans = max(ans, __builtin_popcountll(cur)); return; }
		if (!can) return;
		int piv = ctz(can | ban), ret = 0;
		T z = can & ~g[piv];
		for(int u = ctz(z); u < n; u += ctz(z >> (u + 1)) + 1) {
			gao(cur | (1ull << u), can & g[u], ban & g[u]);
			can ^= 1ull << u, ban |= 1ull << u;
		}
	}
	int run() { gao(ans = 0, (1ull << n) - 1, 0); return ans; }
}	bk;

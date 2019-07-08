struct Gra {
	static const int N = ::N << 1;
	int L, hd[::N], ne[N], to[N]; ll val[N];
	inline void init(int n) { L = 0; rep(i, 1, n + 1) hd[i] = -1; }
	inline void _add(int u, int v, ll w) { to[L] = v; val[L] = w; ne[L] = hd[u]; hd[u] = L++; }
	inline void add(int u, int v, ll w) { _add(u, v, w); _add(v, u, w); }
};

struct StoerWagner{
	static const int N = 305;
	static const int INF = 0x3f3f3f3f;;
	int n;
	int g[N][N], val[N];
	bool vis[N], use[N];
	void init(int _n) {
		n = _n;
		fill_n(use + 1, n, 0);
		rep(i, 1, n+1) fill_n(g[i] + 1, n, 0);
	}
	void add_edge(int u, int v, int w) {
    	g[u][v] += w;
    	g[v][u] += w;
	}
	void merge(int u, int v) {
    	rep(i, 1, n+1) {
			g[v][i] += g[u][i];
			g[i][v] += g[i][u];
		}
		use[u] = 1;
	}
	int MinimumCutPhase(int cnt, int &s, int &t) {
    	fill_n(val + 1, n, 0);
    	fill_n(vis + 1, n, 0);
    	t = 1;
    	while (--cnt) {
        	vis[s = t] = 1;
            rep(i, 1, n+1) if (!vis[i] && !use[i]) val[i] += g[t][i];
			int ma = 0;
			rep(i, 1, n+1) if (!vis[i] && !use[i] && val[i] >= ma) {
				ma = val[i]; t = i;
			}
            if (!ma) return 0;
    	}
    	return val[t];
	}
	int solve() {
    	int res = INF;
    	for (int i = n, s, t; i > 1; --i) {
        	res = min(res, MinimumCutPhase(i, s, t));
        	if (res == 0) break;
        	merge(s, t);
   		}
    	return res;
	}
} SW;


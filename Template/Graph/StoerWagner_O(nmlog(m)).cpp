struct StoerWagner{
	static const int N = 3005, M = 100005 * 2, INF = 0x3f3f3f3f;;
	int head[N], val[N], e, n;
	int to[M], ne[M], data[M];
	bool vis[N];
	int fa[N], link[N];
	void init(int _n) {
		n = _n;
		fill_n(head + 1, n, -1);
		fill_n(link + 1, n, -1);
		rep(i, 1, n+1) fa[i] = i;
    	e = 0;
	}
	void add_edge(int u, int v, int w) {
    	to[e] = v; data[e] = w; ne[e] = head[u]; head[u] = e++;
    	to[e] = u; data[e] = w; ne[e] = head[v]; head[v] = e++;
	}
	int findset(int u) { 
    	return u == fa[u] ? u : fa[u] = findset(fa[u]);
	}
	void merge(int u, int v) {
    	int p = u;
    	while (~link[p]) p = link[p];
    	link[p] = v;
    	fa[v] = u;
	}
	int MinimumCutPhase(int cnt, int &s, int &t) {
    	fill_n(val + 1, n, 0);
    	fill_n(vis + 1, n, 0);
    	priority_queue<pii> q;
    	t = 1;
    	while (--cnt) {
        	vis[s = t] = 1;
        	for (int u = s; ~u; u = link[u]) {
            	for (int p = head[u]; ~p; p = ne[p]) {
                	int v = findset(to[p]);
                	if (!vis[v]) q.push(mp(val[v] += data[p], v));
            	}
        	}
        	while (!q.empty() && (vis[q.top().se] || val[q.top().se] != q.top().fi)) {
        		q.pop();
			}
            if (q.empty()) return 0;
            t = q.top().se; q.pop();
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

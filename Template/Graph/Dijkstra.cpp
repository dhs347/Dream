int n, dis[N];
void Dijkstra(int st) {
	priority_queue<pii> q;
	fill_n(dis + 1, n, inf);
	dis[st] = 0;
	q.push(mp(0, st));
	while(!q.empty()) {
		pii u = q.top();q.pop();
		if(dis[u.se] != -u.fi) continue;
		for(auto v : g[u.se]) {
			if(dis[v.fi] > dis[u.se] + v.se) {
				dis[v.fi] = dis[u.se] + v.se;
				q.push(mp(-dis[v.fi], v.fi));
			}
		}
	}
}
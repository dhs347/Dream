int mat1[N], mat[N], pos[N]; 
vi g1[N], g2[N];
queue<int> q;

void match(int n, vi *g, vi *rank) { 
	rep(i, 1, n+1) q.push(i), pos[i] = 0, mat[i] = 0;
	while (!q.empty()) {
		int u = q.front(); q.pop();
		int &p = pos[u], v = g[u][p];
		if (!mat[v]) mat[v] = u;
		else if (rank[v][mat[v]] > rank[v][u]) {
			q.push(mat[v]);
			mat[v] = u;
		}else q.push(u);
		p++;
	}
	rep(i, 1, n+1) mat1[mat[i]] = i;
}

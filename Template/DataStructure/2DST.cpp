namespace ST_2D{
	const int N = 1030;
	int LOG[N], P[20], dep1, dep2;
	short st[11][11][N][N];
	void build(int n, int m, short a[][N]){
		rep(i, 0, 11) P[i] = 1<<i;
		rep(i, 2, 1025) LOG[i] = LOG[i>>1]+1;
		for(dep1 = 0; (1<<dep1) < n; dep1++);
		for(dep2 = 0; (1<<dep2) < m; dep2++);
		rep(i, 1, n+1)
			rep(j, 1, m+1)
				st[0][0][i][j] = a[i][j];//modi
		rep(i, 1, n+1)
			rep(j, 1, dep2+1)
				rep(k, P[j], m+1)
					st[0][j][i][k] = max(st[0][j-1][i][k], st[0][j-1][i][k-P[j-1]]);
		rep(i, 1, dep1+1)
			rep(j, P[i], n+1)
				rep(k, 0, dep2+1) //attention to range of k
					rep(l, P[k], m+1)
						st[i][k][j][l]=max(st[i-1][k][j-P[i-1]][l], st[i-1][k][j][l]);
	}
	int qry(int x1, int y1, int x2, int y2){
		int l1 = LOG[x2-x1+1], l2 = LOG[y2-y1+1];
		int res1 = max(st[l1][l2][x1+P[l1]-1][y1+P[l2]-1], st[l1][l2][x2][y2]);
		int res2 = max(st[l1][l2][x1+P[l1]-1][y2], st[l1][l2][x2][y1+P[l2]-1]);
		return max(res1, res2);
	}
}

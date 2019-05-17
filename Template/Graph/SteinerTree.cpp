// 要视图的情况使用spfa, dijstra, 多源bfs 
const int N = 11, M = 10;
const int inf = 0x3f3f3f3f;
int n, m, k, a[N][N], st[N][N], dp[1 << M][N][N], S, ans;
bool use[N][N], vis[1 << M][N][N];
int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};
queue<pii> q;

struct node {
	int x, y, msk; 
	node(int x = 0, int y = 0, int msk = 0):x(x), y(y), msk(msk){}
} now;

pair<node, node> pre[1 << M][N][N];

void spfa(int msk) {
	while (!q.empty()) {
		pii u = q.front(); q.pop();
		int x = u.fi, y = u.se;
		vis[msk][x][y] = 0;
		rep(i, 0, 4) {
			int nx = x + dx[i], ny = y + dy[i], t = msk | st[nx][ny];
			if (nx > n || nx < 1 || ny > m || ny < 1) continue;
			int &z = dp[t][nx][ny], w = dp[msk][x][y] + a[nx][ny];
			if (z > w) {
				z = w, pre[t][nx][ny] = mp(node(x, y, msk), node(x, y, 0));
				if (t == msk && !vis[msk][nx][ny]) {
					vis[msk][nx][ny] = 1;
					q.push(mp(nx, ny));
				}
			}
		}
	}
}

void dfs(node now) {
	pair<node, node> t = pre[now.msk][now.x][now.y];
	node t1 = t.fi, t2 = t.se;
	use[now.x][now.y] = 1;
	if (!t1.x) return;
	dfs(t1);
	if (t2.msk) dfs(t2);
}

int SteinerTree(int n, int m) {
	memset(dp, 0x3f, sizeof(dp));
	rep(i, 1, n+1) rep(j, 1, m+1) {
		cin >> a[i][j];
		if (!a[i][j]) {
			st[i][j] = pw(k);
			dp[pw(k)][i][j] = 0;
			pre[pw(k++)][i][j] = mp(node(0, 0, 0), node(0, 0, 0));
		}
	} 
	S = pw(k) - 1;
	rep(msk, 1, S+1) {
		rep(i, 1, n+1)
			rep(j, 1, m+1) {
				if (st[i][j] && !(st[i][j] & msk)) continue;
				int &z = dp[msk][i][j];
				for (int t = msk & (msk - 1); t > 0; t = (t - 1) & msk) {
					int t1 = t | st[i][j], t2 = msk ^ t | st[i][j];
					int w = dp[t1][i][j] + dp[t2][i][j] - a[i][j]; 
					if (z > w) z = w, pre[msk][i][j] = mp(node(i, j, t1), node(i, j, t2)); 
				}
				if (z < inf) q.push(mp(i, j)), vis[msk][i][j] = 1;
			}
		spfa(msk);
	}
	ans = inf;
	rep(i, 1, n+1) rep(j, 1, m+1) if (ans > dp[S][i][j]) 
		ans = dp[S][i][j], now = node(i, j, S);
	dfs(now);
	return ans == inf ? -1 : ans;
}

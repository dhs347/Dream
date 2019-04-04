//网格图中选一些点使目标点连通，花费最小，且要方案  斯坦纳树 
#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define rep(i, a, b) for(int i=(a); i<(b); i++)
#define per(i, a, b) for(int i=(b)-1; i>=(a); i--)
#define sz(a) (int)a.size()
#define de(a) cout << #a << " = " << a << endl
#define dd(a) cout << #a << " = " << a << " "
#define all(a) a.begin(), a.end()
#define pw(x) (1ll<<(x))
#define endl "\n"
typedef double db;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;
const int P = 1e9 + 7;
int add(int a, int b) {if((a += b) >= P) a -= P; return a;}
int sub(int a, int b) {if((a -= b) < 0) a += P; return a;}
int mul(int a, int b) {return 1ll * a * b % P;}
int kpow(int a, int b) {int r=1;for(;b;b>>=1,a=mul(a,a)) {if(b&1)r=mul(r,a);}return r;}
//----


const int N = 105;
int n, m, k, a[N][N], st[N][N], dp[N][N][300], vis[N][N][300], u, v, S, y, x, ans, use[N][N];
int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};
pair<pair<pii, int>, int > fa[N][N][300];
queue<pii> q;
pair<pii, int> now;

void spfa(int mask) {
	while (!q.empty()) {
		pii u = q.front(); q.pop();
		vis[u.fi][u.se][mask] = 0;
		rep(i, 0, 4) {
			int x = u.fi + dx[i], y = u.se + dy[i];
			if (x > n || x < 1 || y > m || y < 1) continue;
			int &z = dp[x][y][mask | st[x][y]];
			if (z == -1 || z > dp[u.fi][u.se][mask] + a[x][y]) {
				z = dp[u.fi][u.se][mask] + a[x][y];
				fa[x][y][mask | st[x][y]] = mp(mp(u, mask), -1);
				if ((st[x][y] | mask != mask) || vis[x][y][mask]) continue;
				vis[x][y][mask] = 1;
				q.push(mp(x, y));
			}
		}
	}
}
void dfs(pair<pii, int> now) {
	auto t = fa[now.fi.fi][now.fi.se][now.se];
	int x = t.fi.fi.fi, y = t.fi.fi.se;
	//de(now.fi.fi);de(now.fi.se);de(now.se);
	//de(x);de(y);
	int m1 = t.fi.se, m2 = t.se;
	//de(m1);de(m2);
	if (x == 0) {use[now.fi.fi][now.fi.se] = 1;return;}
	dfs(mp(mp(x, y), m1));
	if (m2 == -1) {
		use[now.fi.fi][now.fi.se] = 1;
	}else dfs(mp(mp(x, y), m2));
}

int main() {
	freopen("a.in","r",stdin);
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	cin >> n >> m >> k;
	rep(i, 1, n+1) rep(j, 1, m+1) cin >> a[i][j];
	memset(dp, -1, sizeof(dp));
	rep(i, 0, k) {
		cin >> u >> v;
		st[u][v] = pw(i);
		dp[u][v][pw(i)] = a[u][v];
	}
	S = pw(k);
	
	rep(mask, 1, S) {
		rep(i, 1, n+1)
			rep(j, 1, m+1) {
				if (st[i][j] && !(st[i][j] & mask)) continue;
				int &z = dp[i][j][mask];
				for (int t = mask & (mask - 1); t > 0; t = (t - 1) & mask) {
					int &x = dp[i][j][t | st[i][j]], &y = dp[i][j][mask ^ t | st[i][j]];
					if (x != -1 && y != -1) {
						if (z == -1 || z > x + y - a[i][j]) {
							z = x + y - a[i][j];
							fa[i][j][mask] = mp(mp(mp(i, j), t | st[i][j]), mask ^ t | st[i][j]);
							//if (mask == 3 && i == 1 && j == 2) de(233); 
						}
					}
				}
				if (z != -1) q.push(mp(i, j)), vis[i][j][mask] = 1;
			}
		spfa(mask);
	}
	ans = pw(30);
	rep(i, 1, n+1) rep(j, 1, m+1) if (dp[i][j][S-1] != -1 && ans > dp[i][j][S-1]) ans = dp[i][j][S-1], now = mp(mp(i, j), S-1);
	cout << ans << endl;
	dfs(now);
	rep(i, 1, n+1) {
		rep(j, 1, m+1) if (use[i][j]) cout << "X";else cout << ".";
		cout << endl;
	}
	return 0;
}



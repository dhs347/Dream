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

const int N = 11, M = 10;
const int inf = 0x3f3f3f3f;
int n, m, k, a[N][N], st[N][N], dp[N][N][1 << M], S, ans;
bool use[N][N], vis[N][N][1 << M];
int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};
queue<pii> q;

struct node {
	int x, y, msk; 
	node(int x = 0, int y = 0, int msk = 0):x(x), y(y), msk(msk){}
} now;

pair<node, node> pre[N][N][1 << M];

void spfa(int msk) {
	while (!q.empty()) {
		pii u = q.front(); q.pop();
		int x = u.fi, y = u.se;
		vis[x][y][msk] = 0;
		rep(i, 0, 4) {
			int nx = x + dx[i], ny = y + dy[i], t = msk | st[nx][ny];
			if (nx > n || nx < 1 || ny > m || ny < 1) continue;
			int &z = dp[nx][ny][t], w = dp[x][y][msk] + a[nx][ny];
			if (z > w) {
				z = w, pre[nx][ny][t] = mp(node(x, y, msk), node(x, y, 0));
				if (t == msk && !vis[nx][ny][msk]) {
					vis[nx][ny][msk] = 1;
					q.push(mp(nx, ny));
				}
			}
		}
	}
}

void dfs(node now) {
	pair<node, node> t = pre[now.x][now.y][now.msk];
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
			dp[i][j][pw(k)] = 0;
			pre[i][j][pw(k++)] = mp(node(0, 0, 0), node(0, 0, 0));
		}
	} 
	S = pw(k) - 1;
	rep(msk, 1, S+1) {
		rep(i, 1, n+1)
			rep(j, 1, m+1) {
				if (st[i][j] && !(st[i][j] & msk)) continue;
				int &z = dp[i][j][msk];
				for (int t = msk & (msk - 1); t > 0; t = (t - 1) & msk) {
					int t1 = t | st[i][j], t2 = msk ^ t | st[i][j];
					int w = dp[i][j][t1] + dp[i][j][t2] - a[i][j]; 
					if (z > w) z = w, pre[i][j][msk] = mp(node(i, j, t1), node(i, j, t2)); 
				}
				if (z < inf) q.push(mp(i, j)), vis[i][j][msk] = 1;
			}
		spfa(msk);
	}
	ans = inf;
	rep(i, 1, n+1) rep(j, 1, m+1) if (ans > dp[i][j][S]) ans = dp[i][j][S], now = node(i, j, S);
	dfs(now);
	cout << ans << endl;
	rep(i, 1, n+1) {
		rep(j, 1, m+1) 
			if (!a[i][j]) cout << "x";
			else if (use[i][j]) cout << "o";
			else cout << "_";
		cout << endl;
	}
	return ans;
}


int main() {
	freopen("a.in","r",stdin);
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	cin >> n >> m;
	SteinerTree(n, m);
	return 0;
}



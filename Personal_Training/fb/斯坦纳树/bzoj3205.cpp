// 关键在建图，以及因为边权为1可以用多源bfs 
#include<bits/stdc++.h>
using namespace std;
#define mp make_pair
#define pb push_back
#define rep(i, a, b) for(register int i=(a); i<(b); i++)
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
//typedef pair<short, short> pii;
typedef vector<int> vi;
const int P = 1e9 + 7;
int add(int a, int b) {if((a += b) >= P) a -= P; return a;}
int sub(int a, int b) {if((a -= b) < 0) a += P; return a;}
int mul(int a, int b) {return 1ll * a * b % P;}
int kpow(int a, int b) {int r=1;for(;b;b>>=1,a=mul(a,a)) {if(b&1)r=mul(r,a);}return r;}
//----

const int N = 505, M = 11;
const short inf = 0x3f3f;
short n, m, k, ans, dp[M][M][N][N], w[N * N];
struct pii{
	short fi, se;
	pii(short a = 0, short b = 0) : fi(a), se(b) {}
};
bool Vis[N][N][4];
pii g[N][N][4];
pii tmp[N * N], pos[N * N];
short dx[] = {1, 0, -1, 0};
short dy[] = {0, -1, 0, 1};
string s[N];
pii q[N * N];
int cnt[inf], S, h, t;


inline void spfa(int l, int r) {
	short mi = inf, ma = -1;
	rep(i, 0, S) {
		mi = min(w[i], mi);
		ma = max(w[i], ma);
		cnt[w[i]]++;
	}
	rep(i, mi+1, ma+1) cnt[i] += cnt[i-1];
	rep(i, 0, S) tmp[--cnt[w[i]]] = pos[i];
	rep(i, mi, ma+1) cnt[i] = 0;
	int p = 0, h = 0, t = 0, ww = 0;
	while (h != t || p < S) {
		pii u;
		u = (h == t || (p < S && dp[l][r][tmp[p].fi][tmp[p].se] < dp[l][r][q[h].fi][q[h].se])) ? tmp[p++] : q[h++];
		short x = u.fi, y = u.se;
		rep(i, 0, 4) {
			short nx = g[x][y][i].fi, ny = g[x][y][i].se;
			if (nx && dp[l][r][nx][ny] > dp[l][r][x][y] + 1) dp[l][r][nx][ny] = dp[l][r][x][y] + 1, q[t++] = pii(nx, ny);
		}
	}
}

int SteinerTree(int n, int m) {
	rep(i, 1, n+1) rep(j, 1, m+1) rep(l, 1, k+1) rep(r, l, k+1) dp[l][r][i][j] = inf;
	rep(i, 1, n+1) rep(j, 1, m+1) {
		S = 0;
		if (s[i][j-1] >= '0' && s[i][j-1] <= '9') {
			int x = s[i][j-1] - '0';
			dp[x][x][i][j] = 0;
			w[S] = 0; pos[S++] = pii(i, j);
			spfa(x, x);
		}
	} 
	for (int l = k - 1; l; l--)
		for (int r = l + 1; r <= k; r++){
			for (int mid = l; mid < r; mid++) 
				rep(i, 1, n+1)
					rep(j, 1, m+1) 
						dp[l][r][i][j] = min(dp[l][r][i][j], short(dp[l][mid][i][j] + dp[mid+1][r][i][j]));
			S = 0;
			rep(i, 1, n+1) rep(j, 1, m+1) 
				if (dp[l][r][i][j] < inf) w[S] = dp[l][r][i][j], pos[S++] = pii(i, j);
			if (l != 1 || r != k) spfa(l, r);
		}
	ans = inf;
	rep(i, 1, n+1) rep(j, 1, m+1) if (ans > dp[1][k][i][j]) ans = dp[1][k][i][j];
	return ans == inf ? -1 : ans;
}

void dfs(int x, int y, int o) {
	Vis[x][y][o] = 1;
	int no = o;
	if (s[x][y-1] == 'A') no--;
	if (s[x][y-1] == 'C') no++;
	no = (no + 4) % 4;
	int nx = x + dx[no], ny = y + dy[no];
	if (nx < 1 || nx > n || ny < 1 || ny > m || s[nx][ny-1] == 'x') {
		g[x][y][o] = pii(x, y);
		return;
	}
	if (!Vis[nx][ny][no]) dfs(nx, ny, no);
	g[x][y][o] = g[nx][ny][no];
	return;
}

int main() {
	freopen("a.in","r",stdin);
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	cin >> k >> m >> n;
	rep(i, 1, n+1) cin >> s[i];
	rep(i, 1, n+1) rep(j, 1, m+1) rep(t, 0, 4) if (s[i][j-1] != 'x') dfs(i, j, t);
	cout << SteinerTree(n, m) << " ";
	return 0;
}



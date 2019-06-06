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
#define lb(x) ((x) & -(x))
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

const int N = 55, M = 1 << 10, inf = pw(30);
int S, n, m, p, dis[N][N][M], g[N][N][N][N], s[N][N], x, y, xx, yy, now, nxt, Q, a, b, c, d, w, ans;
int dx[] = {0, 0, -1, 1};
int dy[] = {-1, 1, 0, 0};
queue<pair<pii, int> > q;

void init() {
	S = pw(p) - 1;
	rep(i, 1, n+1) rep(j, 1, m+1) rep(k, 0, S + 1) dis[i][j][k] = inf;
	rep(i, 1, n+1) rep(j, 1, m+1) rep(k, 1, n+1) rep(l, 1, m+1) g[i][j][k][l] = -1;
	rep(i, 1, n+1) rep(j, 1, m+1) s[i][j] = 0;
}

void bfs() {
	q.push(mp(mp(1, 1), s[1][1]));
	dis[1][1][s[1][1]] = 0;
	while (!q.empty()) {
		auto t = q.front(); q.pop();
		x = t.fi.fi; y = t.fi.se; now = t.se;
		rep(i, 0, 4) {
			xx = x + dx[i]; yy = y + dy[i];
			if (xx < 1 || xx > n || yy < 1 || yy > m || !g[x][y][xx][yy]) continue;
			if (g[x][y][xx][yy] >= 0 && !(pw(g[x][y][xx][yy]-1) & now)) continue;
			nxt = now | s[xx][yy];
			if (dis[xx][yy][nxt] > dis[x][y][now] + 1) {
				dis[xx][yy][nxt] = dis[x][y][now] + 1;
				q.push(mp(mp(xx, yy), nxt));
			}
		}
	}
}

int main() {
	freopen("a.in","r",stdin);
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	while (cin >> n >> m >> p) {
		init();
		cin >> Q;
		rep(i, 0, Q) {
			cin >> a >> b >> c >> d >> w;
			g[a][b][c][d] = g[c][d][a][b] = w; 
		}
		cin >> Q;
		rep(i, 0, Q) {
			cin >> a >> b >> w;
			s[a][b] |= pw(w-1);
		}
		bfs();
		ans = *min_element(dis[n][m], dis[n][m] + S + 1);
		if (ans == inf) cout << -1;else cout << ans;
		cout << endl;
	}
	
	return 0;
}



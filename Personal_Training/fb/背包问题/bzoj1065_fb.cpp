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
#define all(a) (a).begin(), (a).end()
#define pw(x) (1ll<<(x))
#define lb(x) ((x) & -(x))
#define endl "\n"
typedef double db;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;
const int P = 1e9 + 7;
int add(int a, int b) {if((a += b) >= P) a -= P; return a < 0 ? a + P : a;}
int mul(int a, int b) {return 1ll * a * b % P;}
int kpow(int a, int b) {int r=1;for(;b;b>>=1,a=mul(a,a)) {if(b&1)r=mul(r,a);}return r;}
//----

const int N = 80;
int n, m, d[N], vis[N], u, ne[N], t, len;
db k, f[N][N][N], c[N], s1, s2, ans;
vi g[N];

void dfs(int u) {
	//f[u][1][1] = c[u] * k;
	rep(i, min(2, d[u]), d[u]+1) f[u][0][i] = c[u] * pow(k, i);
	rep(i, 0, sz(g[u])) {
		int v = g[u][i];
		d[v] = d[u] + 1;
		dfs(v);
		rep(j, min(2, d[u]), d[u]+1) { 
			per(l, 0, m+1)  
				rep(t, 0, l+1) f[u][l][j] = max(f[u][l][j], f[u][l-t][j] + max(f[v][t][1], f[v][t][j+1]));
		}
		if (d[u] > 1 && !vis[u]) {
			per(l, 0, m+1) 
				rep(t, 0, l+1) f[u][l][1] = max(f[u][l][1], f[u][l-t][1] + max(f[v][t][1], f[v][t][2]));
		}
	}
	if (d[u] > 1 && !vis[u]) {
		per(l, 1, m+1) f[u][l][1] = f[u][l-1][1] + c[u] * k;
		f[u][0][1] = 0;
	}
	//rep(j, min(2, d[u]), d[u]+1) rep(l, 0, m+1) f[u][l][j] += c[u] * pow(k, j);
}


void solve() {
	rep(i, 1, n+1) g[i].clear();
	memset(f, 0, sizeof(f));
	rep(i, 2, n+1) {
		u = ne[i];
		g[u].pb(i);
	}
	dfs(1);
}

int main() {
	freopen("a.in","r",stdin);
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout << setiosflags(ios::fixed);
	cout << setprecision(2);
	cin >> n >> m >> k;
	rep(i, 1, n+1) cin >> ne[i];
	rep(i, 1, n+1) cin >> c[i];
	t = 1; len = 1; vis[1] = 1;
	while (1) { 
		t = ne[t]; len ++; vis[t] = 1;
		if (t == 1) break;
		if (ne[t] != 1) m--;
		if (m >= 0) {
			int tmp = ne[t]; ne[t] = 1;
			solve();
			rep(i, 0, m+1)  ans = max(f[1][i][0] / (1 - pow(k, len)), ans);
			ne[t] = tmp;
		}
		m++;
	}
	cout << ans;
	return 0;
}



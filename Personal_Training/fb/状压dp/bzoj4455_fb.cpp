// 给n个点的图和树，给树不重复标号，树上边要在图中出现
// 用容斥来保证标号不重复，有重复标号等价于有标号没用到 

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

const int N = 18;
int op, S, a[N][N], n, m, u, v, sta;
vi tmp, g[N];
ll ans, f[N][N];

void dfs(int u, int fa) {
	rep(i, 0, sz(tmp)) f[u][tmp[i]] = 1;
	rep(l, 0, sz(g[u])) {
		int v = g[u][l];
		if (v == fa) continue;
		dfs(v, u);
		rep(i, 0, sz(tmp)) {
			ll cnt = 0;
			rep(j, 0, sz(tmp)) if (a[tmp[i]][tmp[j]]) cnt += f[v][tmp[j]];
			f[u][tmp[i]] *= cnt;
		}
	}
}

int main() {
	freopen("a.in","r",stdin);
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	cin >> n >> m;
	rep(i, 1, m+1) {
		cin >> u >> v;
		u--;v--;
		a[u][v] = a[v][u] = 1;
	}
	rep(i, 1, n) {
		cin >> u >> v;
		g[u].pb(v);
		g[v].pb(u);
	}
	S = pw(n) - 1;
	rep(i, 0, S) {
		sta = i;
		memset(f, 0, sizeof(f));
		op = __builtin_popcount(i) & 1 ? -1 : 1;
		rep(i, 0, n) if (!(pw(i) & sta)) tmp.pb(i);
		dfs(1, -1);
		tmp.clear();
		rep(j, 0, n) ans += op * f[1][j];
	}
	cout << ans;
	return 0;
}



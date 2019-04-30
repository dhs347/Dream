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
int add(int a, int b) {if((a += b) >= P) a -= P; return a < 0 ? a + P : a;}
int mul(int a, int b) {return 1ll * a * b % P;}
int kpow(int a, int b) {int r=1;for(;b;b>>=1,a=mul(a,a)) {if(b&1)r=mul(r,a);}return r;}
//----

const int N = 101010 << 1;
int dep[N], f[N][20], siz[N];
db w[N], ans, w2[N];
int n, m, u, v;
vi g[N];

struct LCARMQ{
    void dfs(int c, int fa, const vi g[]){
        siz[c] = 1; 
        rep(i, 1, 20) f[c][i] = f[f[c][i-1]][i-1];
		for(auto t : g[c]) if (t != fa) 
			dep[t] = dep[c]+1, f[t][0] = c, dfs(t, c, g),  siz[c] += siz[t], w[c] += w[t] + siz[t];
	}
	void dfs2(int c, int fa, const vi g[], db tmp){
		w2[c] = tmp + siz[1] - siz[c];
		for(auto t : g[c]) if (t != fa) 
			dfs2(t, c, g, w2[c] + w[c] - w[t] - siz[t]);
	}
    void Build(const vi g[]){
        dep[1] = 1; dfs(1, 0, g);
        dfs2(1, 0, g, 0);
    }
    int lca(int x,int y){
        if (dep[x] < dep[y]) swap(x, y);
        per(i, 0, 20) if (dep[f[x][i]] >= dep[y]) x = f[x][i];
        per(i, 0, 20) if (f[x][i] != f[y][i]) x = f[x][i], y = f[y][i];
        if (x == y) return x;
        return f[x][0];
    }
    int dis(int x, int y) {
		int z = lca(x, y);
		return dep[x] + dep[y] - 2 * dep[z];
	}
} R;


int main() {
	freopen("a.in","r",stdin);
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	cout << setiosflags(ios::fixed);
	cout << setprecision(6);
	cin >> n >> m;
	rep(i, 1, n) {
		cin >> u >> v;
		g[u].pb(v);
		g[v].pb(u);
	}
	R.Build(g);
	rep(i, 1, m+1) {
		cin >> u >> v;
		int d = R.dis(u, v), z = R.lca(u, v);
		if (z != u && z != v) {
			ans = 1.0 * siz[u] * siz[v] * d + w[u] * siz[v] + w[v] * siz[u];
			ans /= 1.0 * siz[u] * siz[v];
		}else {
			if (v == z) swap(u, v);
			int y = v;
			per(i, 0, 20) if (dep[f[y][i]] > dep[u]) y = f[y][i];
			//de(z);de(d);de(y);
			ans = 1.0 * (siz[1] - siz[y]) * siz[v] * d + (w[u] - w[y] - siz[y] + w2[u]) * siz[v] + w[v] * (siz[1] - siz[y]);
			ans /= 1.0 * (siz[1] - siz[y]) * siz[v];
		}
		cout << ans + 1 << endl; 
	}
	return 0;
}



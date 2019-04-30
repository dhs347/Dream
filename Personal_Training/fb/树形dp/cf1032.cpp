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
const int P = 998244353;
int add(int a, int b) {if((a += b) >= P) a -= P; return a < 0 ? a + P : a;}
int mul(int a, int b) {return 1ll * a * b % P;}
int kpow(int a, int b) {int r=1;for(;b;b>>=1,a=mul(a,a)) {if(b&1)r=mul(r,a);}return r;}
//----

const int N = 3e5 + 7;
int f[N][2][2], n, u, v, pre[N], suf[N];
vi g[N];

void dfs(int u, int fa) {
	int p = -1;
	rep(i, 0, sz(g[u])) if (g[u][i] == fa) {p = i;break;}
	if (p >= 0) g[u].erase(g[u].begin() + p);
	f[u][0][0] = 1; f[u][1][0] = 1;
	for (auto v : g[u]) {
		dfs(v, u);
		f[u][0][0] = mul(f[u][0][0], add(f[v][0][0], f[v][1][1]));
		f[u][1][0] = mul(f[u][1][0], add(f[v][0][0], mul(f[v][1][1], 2)));
		pre[v] = suf[v] = add(f[v][0][0], mul(f[v][1][1], 2));
	}
	f[u][1][0] = add(f[u][1][0], -f[u][0][0]);
	rep(i, 1, sz(g[u])) pre[g[u][i]] = mul(pre[g[u][i]], pre[g[u][i-1]]);
	per(i, 0, sz(g[u]) - 1) suf[g[u][i]] = mul(suf[g[u][i]], suf[g[u][i+1]]);
	rep(i, 0, sz(g[u])) {
		int v = g[u][i], t = add(f[v][1][0], f[v][0][0]);
		if (i) t = mul(t, pre[g[u][i-1]]);
		if (i + 1 < sz(g[u])) t = mul(t, suf[g[u][i+1]]);
		f[u][1][1] = add(f[u][1][1], t);
	}
}

int main() {
	freopen("a.in","r",stdin);
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	cin >> n;
	rep(i, 1, n) {
		cin >> u >> v;
		g[u].pb(v);
		g[v].pb(u);
	} 
	dfs(1, 0);
	cout << add(f[1][0][0], f[1][1][1]);
	return 0;
}



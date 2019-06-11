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

const int N = 2600;
int siz[N], n, k, x;
pii a[N];
vi g[N];
db l, r, mid, f[N][N], tmp[N], b[N];

void dfs(int u) {
	siz[u] = 1; f[u][1] = b[u];
	rep(i, 0, sz(g[u])) {
		int v = g[u][i];
		dfs(v);
		rep(j, 1, siz[u] + siz[v] + 1) tmp[j] = -pw(30);
		rep(j, 1, siz[u] + 1)
			rep(k, 0, siz[v] + 1)
				tmp[j + k] = max(tmp[j + k], f[u][j] + f[v][k]);
		siz[u] += siz[v];
		rep(j, 1, siz[u] + 1) f[u][j] = tmp[j];
	}
}

bool check() {
	dfs(0);
	return f[0][k + 1] >= 0;
}

int main() {
	//freopen("a.in","r",stdin);
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout << setiosflags(ios::fixed);
	cout << setprecision(3);
	cin >> k >> n;
	rep(i, 1, n+1) cin >> a[i].fi >> a[i].se >> x, g[x].pb(i), r += a[i].se;
	rep(tim, 0, 50) {
		mid = (l + r) / 2;
		rep(i, 1, n+1) b[i] = a[i].se - a[i].fi * mid;
		if (check()) l = mid; else r = mid;
	}
	cout << l << endl;
	return 0;
}



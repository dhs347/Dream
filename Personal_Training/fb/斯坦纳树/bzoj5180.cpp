// 如果图比较大且为正权，用dijstra 
#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
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
typedef pair<int, int> pii;
typedef vector<int> vi;
const int P = 1e9 + 7;
int add(int a, int b) {if((a += b) >= P) a -= P; return a;}
int sub(int a, int b) {if((a -= b) < 0) a += P; return a;}
int mul(int a, int b) {return 1ll * a * b % P;}
int kpow(int a, int b) {int r=1;for(;b;b>>=1,a=mul(a,a)) {if(b&1)r=mul(r,a);}return r;}
//----

const int N = 1e5 + 10, M = 1 << 5;
const ll inf = 0x3f3f3f3f3f3f3f3f;
int n, m, k, S, u, v, w, st[N];
ll ans, dp[M][N];
bool vis[M][N];
vector<pii> g[N];
//queue<int> q;
priority_queue<pair<ll, int>, vector<pair<ll, int> >, greater<pair<ll, int> > > q;

/*void spfa(int msk) {
	while (!q.empty()) {
		int u = q.front(); q.pop();
		vis[msk][u] = 0;
		rep(i, 0, sz(g[u])) {
			int v = g[u][i].fi, t = msk | st[v];
			ll &z = dp[t][v], w = dp[msk][u] + g[u][i].se;
			if (z > w) {
				z = w;
				if (t == msk && !vis[msk][v]) {
					vis[msk][v] = 1;
					q.push(v);
				}
			}
		}
	}
}*/

void dij(int msk) {
	while (!q.empty()) {
		pair<ll, int> u = q.top(); q.pop();
		if (vis[msk][u.se]) continue;
		vis[msk][u.se] = 1;
		rep(i, 0, sz(g[u.se])) {
			int v = g[u.se][i].fi, t = msk | st[v];
			ll &z = dp[t][v], w = dp[msk][u.se] + g[u.se][i].se;
			if (z > w) {
				z = w;
				if (t == msk) q.push(mp(w, v));
			}
		}
	}
}

ll SteinerTree(int n, int k) {
	S = pw(k) - 1;
	rep(msk, 0, S + 1) rep(i, 1, n+1) dp[msk][i] = inf; 
	rep(i, 1, k+1) {
		cin >> u;
		st[u] = pw(i - 1);
		dp[pw(i - 1)][u] = 0;
	}  
	rep(i, 1, m+1) {
		cin >> u >> v >> w;
		g[u].pb(mp(v, w));
		g[v].pb(mp(u, w));
	}
	rep(msk, 1, S+1) {
		rep(i, 1, n+1) {
			if (st[i] && !(st[i] & msk)) continue;
				//ll &z = dp[msk][i];
				for (int t = msk & (msk - 1); t > 0; t = (t - 1) & msk) {
					int t1 = t | st[i], t2 = msk ^ t | st[i];
					//ll w = dp[t1][i] + dp[t2][i]; 
					//if (z > w) z = w; 
					dp[msk][i] = min(dp[msk][i], dp[t1][i] + dp[t2][i]);
				}
				if (dp[msk][i] < inf) q.push(mp(dp[msk][i], i));
			}
		//spfa(msk);
		dij(msk);
	}
	ans = *min_element(dp[S] + 1, dp[S] + n + 1);
	return ans == inf ? -1 : ans;
}

int main() {
	freopen("a.in","r",stdin);
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	cin >> n >> k >> m;
	cout << SteinerTree(n, k) << endl;
	return 0;
}



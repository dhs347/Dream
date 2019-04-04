// 只要联通快中的点有一个付出代价就行，建超级源的技巧 
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

const int N = 1e4 + 10, M = 1 << 6;
const int inf = 0x3f3f3f3f;
int n, m, k, ans, dp[M][N], st[N], S, u, v, w, T;
bool vis[M][N];
vector<pii> g[N];
queue<int> q;


void spfa(int msk) {
	while (!q.empty()) {
		int u = q.front(); q.pop();
		vis[msk][u] = 0;
		rep(i, 0, sz(g[u])) {
			int v = g[u][i].fi, t = msk | st[v];
			int &z = dp[t][v], w = dp[msk][u] + g[u][i].se;
			if (z > w) {
				z = w;
				if (t == msk && !vis[msk][v]) {
					vis[msk][v] = 1;
					q.push(v);
				}
			}
		}
	}
}

int SteinerTree(int n, int k) {
	S = pw(k) - 1;
	rep(msk, 0, S + 1) rep(i, 1, n+1) dp[msk][i] = inf; 
	rep(i, 1, k) {
		st[i] = pw(i - 1);
		dp[pw(i - 1)][i] = 0;
	}  
	st[n] = pw(k-1);
	dp[pw(k-1)][n] = 0;
	rep(msk, 1, S+1) {
		rep(i, 1, n+1) {
			if (st[i] && !(st[i] & msk)) continue;
				int &z = dp[msk][i];
				for (int t = msk & (msk - 1); t > 0; t = (t - 1) & msk) {
					int t1 = t | st[i], t2 = msk ^ t | st[i];
					int w = dp[t1][i] + dp[t2][i]; 
					if (z > w) z = w; 
				}
				if (z < inf) q.push(i), vis[msk][i] = 1;
			}
		spfa(msk);
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
	while (cin >> k >> n >> m){
		n += k + 1; k++;
		rep(i, 1, n+1) g[i].clear(), st[i] = 0;
		rep(i, 1, n) {
			cin >> w;
			g[n].pb(mp(i, w));
			g[i].pb(mp(n, w));
		}
		rep(i, 1, m+1) {
			cin >> u >> v >> w;
			g[u].pb(mp(v, w));
			g[v].pb(mp(u, w));
		}
		cout << SteinerTree(n, k) << endl;
	}
	return 0;
}



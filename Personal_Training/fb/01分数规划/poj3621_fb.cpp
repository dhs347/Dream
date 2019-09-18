#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>
#include<queue>
#include<iomanip>
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
#define FI(x) freopen(#x".in","r",stdin)
#define FO(x) freopen(#x".out","w",stdout)
typedef double db;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;
//typedef uniform_int_distribution<ll> RR;
//mt19937 gen(998244353);
//ll rnd(ll l, ll r) { RR dis(l, r); return dis(gen); }
const int P = 1e9 + 7;
int add(int a, int b) {if((a += b) >= P) a -= P; return a < 0 ? a + P : a;}
int mul(int a, int b) {return 1ll * a * b % P;}
int kpow(int a, int b) {int r=1;for(;b;b>>=1,a=mul(a,a)) {if(b&1)r=mul(r,a);}return r;}
//----

const int N = 5e3 +10;
const db eps = 1e-8, inf = 1e18;
int n, m, u[N], v[N], w[N], inq[N], cnt[N], a[N];
db dis[N], l, r, mid;
vector<pair<int, db> > g[N]; 

int sign(db x) {return (x > eps) - (x < -eps);}

bool spfa() {
	queue<int> q;
	rep(i, 1, n+1) dis[i] = 0, q.push(i), inq[i] = 1, cnt[i] = 0;
	while (!q.empty()) {
		int u = q.front(); q.pop(); inq[u] = 0;
		rep(i, 0, sz(g[u])) {
			pair<int, db> v = g[u][i];
			if (sign(dis[u] + v.se - dis[v.fi]) < 0) {
				dis[v.fi] = dis[u] + v.se;
				if (!inq[v.fi]) {
					inq[v.fi] = 1;
					cnt[v.fi] = cnt[u] + 1;
					if (cnt[v.fi] > n + 1) return 1;
					q.push(v.fi);
				}
			}
		}
	}
	return 0;
}

bool check(db mid) {
	rep(i, 1, n+1) g[i].clear();
	rep(i, 1, m+1) {
		g[u[i]].pb(mp(v[i], mid * w[i] - a[u[i]]));
	}
	return spfa();
}
 
int main() {
	//FI(a);
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout << setiosflags(ios::fixed);
	cout << setprecision(2);
	cin >> n >> m;
	l = r = 0;
	rep(i, 1, n+1) cin >> a[i], r += a[i];
	rep(i, 1, m+1) {
		cin >> u[i] >> v[i] >> w[i];
	}
	rep(tim, 0, 50) {
		mid = (l + r) / 2;
		if (check(mid)) l = mid;
		else r = mid;
	}
	cout << l << endl;
	return 0;
}



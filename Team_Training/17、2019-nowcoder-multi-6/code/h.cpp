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
#define FI(x) freopen(#x".in","r",stdin)
#define FO(x) freopen(#x".out","w",stdout)
typedef double db;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;
//typedef uniform_int_distribution<ll> RR;
const int P = 1e9 + 7;
//ll rnd(ll l, ll r) { mt19937 gen(rand()); RR dis(l, r); return dis(gen); }
int add(int a, int b) {if((a += b) >= P) a -= P; return a < 0 ? a + P : a;}
int mul(int a, int b) {return 1ll * a * b % P;}
int kpow(int a, int b) {int r=1;for(;b;b>>=1,a=mul(a,a)) {if(b&1)r=mul(r,a);}return r;}
//----

const int N = 1e5 +7, inf = 1e9 + 7;
int siz, u, v, dis[N], na, nb, n, a[N], b[N], T, wa[21][N], wb[21][N], m, q[N * 2];
ll ans;
vi g[N], tmp[N];
pii V[N];
 
bool cmp(pii &a, pii &b) { return a.se < b.se; }

void bfs() {
	rep(i, 0, n+1) dis[i] = inf;
	rep(i, 0, siz) dis[V[i].fi] = V[i].se;
	int p = 0;
	int l = 0, r = 0;
	while (l < r || p < siz) {
		if (l < r && (p >= siz || dis[q[l]] < dis[V[p].fi])) u = q[l++];
		else u = V[p++].fi;
		for (auto v : g[u]) if (dis[u] + 1 < dis[v]) {
			dis[v] = dis[u] + 1;
			q[r++] = v;
		} 
	}
}

int main() {
	//FI(a);
	ios::sync_with_stdio(0);
	cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	cin >> T;
	rep(cas, 0, T) {
		cin >> n >> m;
		rep(i, 1, n+1) g[i].clear();
		rep(i, 1, m+1) {
			cin >> u >> v;
			g[u].pb(v);
			g[v].pb(u);
		}
		cin >> na;
		rep(i, 1, na+1) cin >> a[i];
		cin >> nb;
		ans = 0;
		rep(i, 1, nb+1) cin >> b[i];
		rep(i, 1, na+1) {
			siz = 1; V[0] = mp(a[i], 0);
			bfs();
			rep(j, 1, n+1) wa[i][j] = dis[j];
		}
		rep(i, 1, nb+1) {
			siz = 1; V[0] = mp(b[i], 0);
			bfs();
			rep(j, 1, n+1) wb[i][j] = dis[j];
		}
		rep(i, 1, na+1) {
			rep(j, 1, nb+1) {
				//sort(V, V+n, cmp);
				siz = 0;
				rep(k, 1, n+1) tmp[wa[i][k] + wb[j][k]].pb(k); 
				rep(k, 0, n+1) {
					for (auto u : tmp[k]) V[siz++] = mp(u, k);
					tmp[k].clear();
				}
				bfs();
				rep(k, 1, n+1) ans += dis[k];
			}
		}
		cout << "Case #" << cas + 1 << ": ";
		ll fm = na * nb * n;
		ll d = __gcd(ans, fm);
		ans /= d; fm /= d;
		if (fm > 1) cout << ans << "/" << fm;
		else cout << ans;
		cout << endl;  
	}
	return 0;
}



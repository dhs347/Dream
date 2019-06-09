#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define endl "\n"
#define pw(x) (1ll << (x))
#define all(x) x.begin(), x.end()
#define sz(a) (int)a.size()
#define de(x) cout << #x << " = " << x << endl
#define dd(x) cout << #x << " = " << x << " "
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int N = 101010;

int n, q, k;
// 0 +k
// 1 -k
int ty[N], in[N], out[N], dis[N], ne[N];
char s[N];
pair<pii, int> Q[N];
vi vec;
vi g[N];

bool check() {
	rep(i, 1, sz(vec)) if(s[vec[i]] != s[vec[0]]) return 0;
	return 1;
}

void gao(int st) {
	vec.clear();
	vec.pb(st);
	for(int p = (st + k) % n; p != st; p = (p + k) % n) vec.pb(p);
	if(check()) {
		for(auto p : vec) ty[p] = (s[st] == ')');
	} else {
		vi que;
		for(auto p : vec) if(ne[ne[p]] == p) dis[p] = 0, que.pb(p);
		rep(i, 0, sz(que)) {
			int u = que[i];
			for(auto v : g[u]) {
				dis[v] = dis[u] + 1;
				que.pb(v);
			}
		}
	}
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	while(cin >> n >> q >> k >> s) {
		rep(i, 1, q + 1) {
			int l, r, d;
			cin >> l >> r >> d;
			Q[i] = mp(mp(l, r), d);
		}
		rep(i, 0, n) g[i].clear(), in[i] = out[i] = 0, dis[i] = N;
		rep(u, 0, n) {
			int v = (s[u] == '(' ? (u - k + n) % n : (u + k) % n);
			g[v].pb(u);
			ne[u] = v;
			++out[u]; ++in[v];
		}
		int Gcd = __gcd(n, k);
		rep(i, 0, Gcd) gao(i);
		rep(i, 1, q + 1) {
			int l = Q[i].fi.fi, r = Q[i].fi.se;
			int d = Q[i].se;
			int c = k * 1ll * d % n;
			ll ans = 0;
			// ans += 区间在大环上的下标和
			// ans += 区间在正大环的个数 * c
			// ans -= 区间在正大环上且下标大等于n-c的个数 * n
			// ans -= 区间在负大环的个数 * c
			// ans += 区间在负大环且下标小于c的个数 * n
			cout << ans << endl;
		}
	}
	return 0;
}

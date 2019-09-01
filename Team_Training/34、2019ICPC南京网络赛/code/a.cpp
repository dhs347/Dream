#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define de(x) cout << #x << " = " << x << endl
#define dd(x) cout << #x << " = " << x << " "
#define endl '\n'
#define pw(x) (1ll<<(x))
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef long long ll;

const int N = 1e6 + 2;

int n, m, q, tot[N];
ll pre[N], ans[N];
vector<pii> vec[N];
pii rng[N];

int calc(ll x) {
	int res = 0;
	while(x) res += x % 10, x /= 10;
	return res;
}
struct FW {
	ll a[N];
	void init() {
		fill_n(a, n + 1, 0);
	}
	void upd(int p, ll c) {
		for( ; p <= n; p += p & -p) a[p] += c;
	}
	ll _qry(int p) {
		ll res = 0;
		for( ; p; p -= p & -p) res += a[p];
		return res;
	}
	ll qry(int l, int r) {
		if(l == 1) return _qry(r);
		return _qry(r) - _qry(l - 1);
	}
}fw;
int gao(int x, int y) {
	int t = min(min(x, n - x + 1), min(y, n - y + 1));
	int k = n - 2 * t + 1;
	if(k) {
		ll res = pre[t - 1];
		if(x == n - t + 1 && y != t) {
			res += n - t + 1 - y + 1;
		} else if(x != t && y == t) {
			res += tot[t];
			res += n - t + 1 - x + 1;
		} else if(x == t && y != n - t + 1) {
			res += 2ll * tot[t];
			res += y - t + 1;
		} else if(x != n - t + 1 && y == n - t + 1) {
			res += 3ll * tot[t];
			res += x - t + 1;
		} else {
			assert(0);
		}
		return calc(res);
	} else {
		return calc(n * 1ll * n);
	}
}

void solve() {
	cin >> n >> m >> q;
	fw.init();
	int to = n / 2 + 1; rep(i, 1, to + 1) {
		tot[i] = n - 2 * i + 1;
		pre[i] = pre[i - 1] + 4ll * tot[i];
	}
	int ma = 0;
	rep(i, 1, m + 1) {
		int x, y; cin >> x >> y;
		int w = gao(x, y);
		vec[x].pb(mp(y, w));
		ma = max(ma, x);
	}
	rep(i, 1, q + 1) {
		ans[i] = 0;
		int xl, yl, xr, yr;
		cin >> xl >> yl >> xr >> yr;
		rng[i] = mp(yl, yr);
		vec[xl - 1].pb(mp(i, -1));
		vec[xr].pb(mp(i, 0));
		ma = max(ma, xr);
	}
	rep(i, 1, n + 1) {
		for(auto u : vec[i]) {
			if(u.se > 0) {
				fw.upd(u.fi, u.se);
			} else {
				int o = u.se; if(!o) o = 1;
				ans[u.fi] += o * fw.qry(rng[u.fi].fi, rng[u.fi].se);
			}
		}
	}
	rep(i, 1, q + 1) cout << ans[i] << endl;
	rep(i, 0, ma + 1) vec[i].clear();
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int T; cin >> T;
	while(T--) solve();
	return 0;
}

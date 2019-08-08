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
#define all(x) x.begin(), x.end()
#define pw(x) (1ll<<(x))
#define sz(x) (int)x.size()
typedef long long ll;
typedef pair<int, int> pii;
typedef double db;
typedef vector<int> vi;

const int N = 101010;

int n, m;
int e[N], l[N], c[N];
vi vec[N];
ll ans;

struct FW {
#define lb(x) (x)&(-(x))
	int a[N * 2]; ll sum[N * 2];
	static const int n = 2e5;
	void init() {
		memset(a, 0, sizeof(a));
		memset(sum, 0, sizeof(sum));
	}
	void upd(int x, int c) {
		int t = x;
		if (x <= 0) return;
		for (int p = x; p <= n; p += lb(p)) a[p] += c, sum[p] += t * 1ll * c;
	}
	int qry(int p) {
		if(p < 1) return 0;
		int r = 0;
		for (; p > 0; p -= lb(p)) r += a[p];
		return r;
	}
	ll qry2(int p) {
		if(p < 1) return 0;
		ll r = 0;
		for (; p > 0; p -= lb(p)) r += sum[p];
		return r;
	}
}fw;

void solve() {
	ans = 0;
	cin >> n;
	rep(i, 1, n + 1) cin >> e[i] >> l[i] >> c[i];
	cin >> m;
	rep(i, 1, n + 1) vec[i].clear();
	rep(i, 1, m + 1) {
		int t, l, r;
		cin >> t >> l >> r;
		vec[l].pb(t);
		vec[r + 1].pb(-t);
	}
	set<int> st;
	fw.init();
	rep(i, 1, n + 1) {
		for(auto u : vec[i]) {
			if(u > 0) {
				auto r = st.lower_bound(u);
				if(r != st.end()) {
					fw.upd((*r) - u, 1);
				}
				if(r != st.begin()) {
					auto l = r; --l;
					fw.upd((*r) - (*l), -1);
					fw.upd(u - (*l), 1);
				}
				st.insert(u);
			} else {
				u = -u;
				auto p = st.lower_bound(u);
				if(p != st.begin()) {
					auto l = p; --l;
					fw.upd((*p) - (*l), -1);
					auto r = p; ++r;
					if(r != st.end()) {
						fw.upd((*r) - (*l), 1);
					}
				} else {
					auto r = p; ++r;
					if(r != st.end()) {
						fw.upd((*r) - (*p), -1);
					}
				}
				st.erase(p);
			}
		}
		if(sz(st)) {
			int t = *st.begin();
			ans += min((ll)c[i], e[i] + 1ll * t * l[i]);
		}
		if(l[i]) {
			int t = (c[i] - e[i]) / l[i];
			ll s = fw.qry2(t);
			ans += s * l[i];
			int cc = fw.qry(2e5) - fw.qry(t);
			ans += cc * 1ll * c[i];
		} else {
			int cc = fw.qry(2e5);
			ans += cc * 1ll * e[i];
		}
	}
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int T; cin >> T;
	rep(i, 1, T + 1) {
		solve();
		cout << "Case #" << i << ": " << ans << endl;
	}
	return 0;
}

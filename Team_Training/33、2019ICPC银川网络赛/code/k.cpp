#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define de(c) cout << #c << " = " << c << endl
#define dd(c) cout << #c << " = " << c << " "
#define endl '\n'
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()
#define pw(x) (1ll<<(x))
typedef long long ll;
typedef pair<int, int> pii;
typedef double db;
typedef vector<int> vi;

const int N = 44;

int n, m, P, a[N];
int f[1 << 18], g[1 << 18];
int nf, ng;
vector<pii> e;

int add(int a, int b) {
	if((a += b) >= P) a -= P;
	return a;
}
int mul(int a, int b) {
	return 1ll * a * b % P;
}

bool check(int i, int d) {
	int l = d ? d : 0;
	int r = d ? n - 1 : nf - 1;
	for(auto t : e) {
		int u = t.fi, v = t.se;
		if(l <= u && u <= r && l <= v && v <= r) {
			u -= d, v -= d;
			if((!(i >> u & 1)) && (!(i >> v & 1))) return 0;
		}
	}
	return 1;
}

void solve() {
	cin >> n >> m >> P;
	rep(i, 0, n) cin >> a[i], a[i] %= P;
	e.clear();
	rep(i, 1, m + 1) {
		int u, v; cin >> u >> v;
		e.pb(mp(u - 1, v - 1));
	}
	if(n == 1) {
		cout << add(1, a[0]) << endl;
		return ;
	}
	nf = n >> 1, ng = n - nf;
	fill_n(f, pw(nf), 0);
	fill_n(g, pw(ng), 0);
	rep(i, 0, pw(nf)) if(check(i, 0)) {
		f[i] = 1;
		rep(j, 0, nf) if(i >> j & 1) f[i] = mul(f[i], a[j]);
	}
	rep(i, 0, pw(ng)) if(check(i, nf)) {
		g[i] = 1;
		rep(j, 0, ng) if(i >> j & 1) g[i] = mul(g[i], a[j + nf]);
	}
	rep(i, 0, ng) for(int j = pw(ng) - 1;	~j; --j) if(!(j >> i & 1)) {
		g[j] = add(g[j], g[j | pw(i)]);
	}
	int ans = 0;
	rep(i, 0, pw(nf)) if(f[i]) {
		int j = 0;
		for(auto t : e) {
			int u = t.fi, v = t.se;
			if(u > v) swap(u, v);
			if(u < nf && v >= nf && (!(i >> u & 1))) j |= pw(v - nf);
		}
		ans = add(ans, mul(f[i], g[j]));
	}
	cout << ans << endl;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int T; cin >> T;
	rep(i, 1, T + 1) {
		cout << "Case #" << i << ": ";
		solve();
	}
	return 0;
}

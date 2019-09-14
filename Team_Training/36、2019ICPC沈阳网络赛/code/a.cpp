#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); i++)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define de(x) cout << #x << " = " << x << endl
#define dd(x) cout << #x << " = " << x << " " 
#define endl '\n'
#define pw(x) (1ll<<(x))
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int P = 1025436931, N = 1010; // todo

int lr(ll n, int m, vi a, vi c) {
	if(n < m) return (a[n] + P) % P;
	vector<ll> v(m, 0), u(m << 1, 0);
	v[0] = 1;
	for(ll x = 0, W = n ? 1ll << (63 - __builtin_clzll(n)) : 0; W; W >>= 1, x <<=1) {
		fill(all(u), 0);
		int b = !!(n & W); if(b) x++;
		if(x < m) {
			u[x] = 1;
		} else {
			rep(i, 0, m) rep(j, 0, m) (u[i + b + j] += v[i] * v[j]) %= P;
			per(i, m, 2 * m) rep(j, 0, m) (u[i - m + j] += c[j] * u[i]) %= P;
		}
		copy(u.begin(), u.begin() + m, v.begin());
	}
	ll ans = 0;
	rep(i, 0, m) (ans += v[i] * a[i]) %= P;
	return (ans + P) % P;
}

int calc(ll n) {
	vi t1, t2;
	t1.pb(1);t1.pb(1);
	t2.pb(1);t2.pb(1);
	return (lr(n + 1, 2, t1, t2) + P - 1) % P;
}

int n, m, a1, a2, b1, b2;

ll solve() {
	cin >> n >> m >> a2 >> b2 >> a1 >> b1;
	if(n > m) swap(n, m), swap(a1, b1), swap(a2, b2);
	if(n == 1) {
		int ans = (b1 <= b2 ? b2 - 1 : m - b2);
		if(abs(b1 - b2) & 1) return ans;
		return ans - 1;
	} else {
		ll d = abs(a1 - a2) + abs(b1 - b2);
		if(d & 1) return -1;
		ll ans = 0;
		for(ll i = 1; i <= n; i += n - 1)
			for(ll j = 1; j <= m; j += m - 1) {
				ll t = abs(i - a2) + abs(j - b2);
				if(abs(i - a1) + abs(j - b1) < t) ans = max(ans, t - 1);
			}
		return ans;
	}
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	//rep(i, 5, 35) dd(i), de(calc(i) - calc(i - 1)), assert(calc(i) - calc(i - 1) == calc(i - 1) - calc(i - 3));
	int T; cin >> T;
	while(T--) {
		auto res = solve();
		if(res == -1) cout << "countless" << endl;
		else cout << calc(res) << endl;
	}
	return 0;
}

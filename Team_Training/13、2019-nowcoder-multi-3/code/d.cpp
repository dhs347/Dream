#include<bits/stdc++.h>
using namespace std;
#define fi first 
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a) --i)
#define de(c) cout << #c << " = " << c << endl
#define dd(c) cout << #c << " = " << c << " "
#define all(c) c.begin(), c.end()
#define sz(x) (int)x.size()
#define endl '\n'
#define pw(x) (1ll << (x))
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef double db;

int kpow(ll a, int b, int p) {
	ll r = 1;
	while (b) {
		if (b & 1) { r = r * a % p;}
		a = a * a % p;
		b >>= 1;
	}
	return r;
}

ll T, ans, p, n, m;

int get(int n) {
	int t = sqrt(n);
	vi d;
	rep(i, 1, t+1) {
		if (n % i == 0) {
			d.pb(i);
			d.pb(n / i);
		}
	}
	sort(all(d));
	rep(i, 0, sz(d)) if (kpow(10, d[i], p) == 1) return d[i];
	return 0;
}

vector<pii> get2(int n) {
	vector<pii> d;
	for (int i = 2; i * i <= n; i++) if (n % i == 0) {
		int cnt = 0;
		while (n % i == 0) n /= i, cnt++;
		d.pb(mp(i, cnt));
	}
	if (n > 1) d.pb(mp(n, 1));
	return d;
}


int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> T;
	rep(cas, 0, T) {
		ans = 0;
		cin >> p >> n >> m;
		if (p == 2 || p == 5) {
			cout << 0 << endl;
			continue;
		}
		if (p == 3) {
			cout << n / 3 * m << endl; 
			continue;
		}
		int K = get(p - 1);
		vector<pii> d = get2(K);
		int t = min(35ll, m);
		rep(j, 1, t+1) {
			int z = 1;
			for (auto u : d) {
				int w = (u.se - 1) / j + 1;
				rep(i, 0, w) z = z * u.fi;
			}
			ans += n / z;
		}
		int z = 1;
		for (auto u : d) z = z * u.fi;
		ans += n / z * (m - t);
		cout << ans << endl;
	}
	return 0;
}

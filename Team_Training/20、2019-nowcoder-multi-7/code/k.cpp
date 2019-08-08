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

int T, n;

struct Min_25{
	static const int N = 1e6 + 8;
	int Sqr, m, p[N], id1[N], id2[N], tot, cntp;
	ll g[N], sp1[N], sp2[N], sp3[N], h[N], n, w[N];
	bool isp[N];

	ll f1(int p) {return p % 4;}
	
	ll f2(int p) {return 1;} 

	ll f3(int p) { if (p % 4 == 1) return 4;else return 1;}

	ll F(int p, int e) {if (p % 4 == 1) return e * 3 + 1; else return 1;}
	
	ll calc1(ll n) {
		ll x = (n - 1) / 4 + 1;
		ll y = (n - 2) / 4 + 1;
		ll z = (n - 3) / 4 + 1;
		ll tmp = 0;
		if (n >= 1) tmp += x;
		if (n >= 2) tmp += y * 2;
		if (n >= 3) tmp += z * 3;
		return tmp - 1;
		return x + 2 * y + 3 * z - 1;
	}

	ll calc2(ll n) {
		return n - 1;
	}

	ll calc3(ll n) {
		ll x = (n - 1) / 4 + 1;
		return n + 3 * x - 4;
	}

	void prime(int n) {
		cntp = 0; isp[1] = 1;
		rep(i, 2, n+1) {
			if (!isp[i]) p[++cntp]  = i;
			for (int j = 1; j <= cntp && i * p[j] <= n; j ++) {
				isp[i * p[j]] = 1;
				if (i % p[j] == 0) break;
			}
		}
		rep(i, 1, cntp+1) {
			sp1[i] = sp1[i-1] + f1(p[i]);
			sp2[i] = sp2[i-1] + f2(p[i]);
			sp3[i] = sp3[i-1] + f3(p[i]);
		}
		p[++cntp] = INT_MAX;
	}

	ll S(ll x, int y) {
		if (x <= 1 || p[y] > x) return 0;
		int k = (x <= Sqr ? id1[x] : id2[n / x]);
		ll ret = 6 * (h[k] + 1) - 2 * g[k] + (g[k] - h[k] - 1) / 2 - sp3[y-1]; 
		for (int i = y; i <= tot && 1ll * p[i] * p[i] <= x; i ++) {
			ll t1 = p[i], t2 = 1ll * p[i] * p[i];
			for (int e = 1; t2 <= x; e++, t1 = t2, t2 *= p[i]) {
				if (F(p[i], e)) ret += S(x / t1, i + 1) * F(p[i], e);
				ret += F(p[i], e+1);
			}
		}
		return ret;
	}

	ll solve(ll _n) {
		n = _n; if (n == 0) return 0;
		m = 0; Sqr = sqrt(n);
		ll ans = 0, tmp = 0;
		rep(j, 1, _n+1) {
			ll t = 1, n = j;
			rep(i, 1, cntp + 1) if (n % p[i] == 0) {
				int cnt = 0;
				while (n % p[i] == 0) n /= p[i], cnt++;
				if (p[i] % 4 == 1)  t = t * (3 * cnt + 1);
			}
			ans += t;
		}
		//de(ans);
		//
		//de(calc1(10));
		tot = upper_bound(p + 1, p + cntp + 1, Sqr) - (p + 1);
		for (ll i = 1, j; i <= n; i = j + 1) {
			j = n / (n / i);
			w[++m] = n / i;
			g[m] = calc1(w[m]);
			h[m] = calc2(w[m]);
			w[m] <= Sqr ? id1[w[m]] = m : id2[j] = m;
		}
		rep(j, 1, tot+1) 
			for (int i = 1; i <= m && 1ll * p[j] * p[j] <= w[i]; i++) {
				ll t = w[i] / p[j];
				int k = t <= Sqr ? id1[t] : id2[n / t];
				g[i] -= f1(p[j]) * (g[k] - sp1[j - 1]);
				h[i] -= f2(p[j]) * (h[k] - sp2[j - 1]);
			}
			dd(w[1]), de(g[1]);
		return S(n, 1) + 1;
	}

} _U;

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> T;
	_U.prime(1e5);
	rep(cas, 0, T) {
		cin >> n;
		cout << _U.solve(n) << endl;
	}
	return 0;
}

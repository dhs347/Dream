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

const int P = 998244353;

ll c1, inv2, nn;
int ans, ans2;

int add(int a, int b) {
	if ((a += b) >= P) a -= P;
	return a < 0 ? a + P : a;
}

int mul(int a, int b) {
	return 1ll * a * b % P;
}

struct min_25{
	static const int N = 1e6 + 10;
	int Sqr, m, p[N], id1[N], id2[N], tot, cntp;
	ll g[N], sp[N], h[N], n, w[N], sp2[N];
	bool isp[N];

	int f(ll n) {return 1;}
	
	int f2(ll n) {return n % P;}

	int calc(ll n) { return (n - 1) % P;}

	int calc2(ll n) { return add(mul(inv2, mul(n, n + 1)), -1);}

	void prime(int n) {
		cntp = 0; isp[1] = 1;
		rep(i, 2, n+1) {
			if (!isp[i]) {
				p[++cntp] = i;
				ll now = 1;
				while (now * i <= nn) {
					now = now * i; ll t = nn / now % P;
					ans = add(ans, mul(c1, t));
					ans = add(ans, -mul(now, t));
					ans = add(ans, -mul(now, mul(t, t)));
				}
			}
			for (int j = 1; j <= cntp && i * p[j] <= n; j++) {
				isp[i * p[j]] = 1;
				if (i % p[j] == 0) break;
			}
		}
		rep(i, 1, cntp+1) sp[i] = add(sp[i-1], f(p[i]));
		rep(i, 1, cntp+1) sp2[i] = add(sp2[i-1] ,f2(p[i]));
		p[++cntp] = INT_MAX;
		int w = 0;
		rep(i, 1, n+1) {
			int t = i, cnt = 0;
			rep(j, 1, cntp+1) {
				if (p[j] > t) break;
				while (t % p[j] == 0) t /= p[j], cnt++;
			}
			w = add(w, cnt);
			
			ans2 = add(ans2, w);
		}
	}
	
	int get1(ll n) {
		if (n <= 0) return 0;
		int k = n <= Sqr  ? id1[n] : id2[nn / n];
		return g[k];
	}

	int get2(ll n) {
		if (n <= 0) return 0;
		int k = n <= Sqr  ? id1[n] : id2[nn / n];
		return h[k];
	}

	void solve(ll _n) {
		n = _n; if (n == 0) return;
		m = 0; Sqr = sqrt(n);
		tot = upper_bound(p + 1, p + cntp + 1, Sqr) - (p + 1);
		for (ll i = 1, j; i <= n; i = j + 1) {
			j = n / (n / i);
			w[++m] = n / i;
			g[m] = calc(w[m]);
			h[m] = calc2(w[m]);
			w[m] <= Sqr ? id1[w[m]] = m : id2[j] = m;
		}
		rep(j, 1, tot + 1) {
			for (int i = 1; i <= m && 1ll * p[j] * p[j] <= w[i]; i++) {
				ll t = w[i] / p[j];
				int k = t <= Sqr ? id1[t] : id2[n / t];
				g[i] = add(g[i], -mul(f(p[j]), add(g[k], -sp[j-1])));
				h[i] = add(h[i], -mul(f2(p[j]), add(h[k], -sp2[j-1])));
			}
		}
		for (ll l = 1, r; l <= n; l = r + 1) {
			r = n / (n / l);
			ll t = n / l % P;
			ans = add(ans, mul(add(get1(r), -get1(l-1)), mul(c1, t)));
			ans = add(ans, -mul(add(get2(r), -get2(l-1)), t));
			ans = add(ans, -mul(add(get2(r), -get2(l-1)), mul(t, t)));
		}
	}

} _U;

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> nn;
	c1 = mul(2, (nn+1) % P);
	inv2  = P / 2 + 1;
	_U.prime(nn);	
	de(ans2);
	//_U.prime(sqrt(nn));
	//_U.solve(nn);
	cout << mul(ans, inv2) << endl;
	return 0;
}

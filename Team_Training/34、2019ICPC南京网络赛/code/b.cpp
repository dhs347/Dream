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

const int N = 1000000;
int T, a[N], aa, b, P;

unordered_map<int, int> M;

int phi(int n) {
	if (M.count(n)) return M[n];
	int r = n, nn = n;
	for (int i = 2; i * i  <= n; i ++) if (n % i == 0) {
		r = r / i * (i - 1);
		while (n % i == 0) n /= i;
	}
	if (n > 1) r = r / n * (n - 1);
	return M[nn] = r;
}

ll qpow(ll a, ll b, ll mod) {
	ll res = 1; bool ok = (b > 0 && a >= mod);
	while (b) {
		if (b & 1) {
			res = res * a;
			ok |= (res >= mod);
			res %= mod;
		}
		a = a * a;
		ok |= (b > 1 && a >= mod);
		a %= mod;
		b >>= 1;
	}
	return res + mod * ok;
}

ll work(int l, int r, int mod) {
	if (mod == 1) return 1;
	if (l == r) return a[l];
	return qpow(a[l], work(l+1, r, phi(mod)), mod);
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int n = 1e5;
	rep(i, 1, n+1) a[i] = phi(i);
	sort(a+1, a+n+1);
	int m = unique(a+1, a+n+1) - a;
	cout << m << endl;
	return 0;
	cin >> T;
	rep(cas, 0, T) {
		cin >> aa >> b >> P;
		if (b == 0) {
			cout << 1 % P << endl;
			continue;
		}
		b = min(b, 300);
		rep(i, 1, b+1) a[i] = aa;
		cout << work(1, b, P) % P << endl;
	}
	return 0;
}

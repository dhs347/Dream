#include<bits/stdc++.h>
using namespace std;
#define fi first 
#define se second
#define mp make_pair
#define pb push_back
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define de(x) cout << #x << " = " << x << endl
#define dd(x) cout << #x << " = " << x << " "
#define endl '\n'
#define pw(x) (1ll<<(x))
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()
typedef long long ll;
typedef double db;
typedef vector<int> vi;
typedef pair<int, int> pii;

const int P = 998244353;

const int N = 1e7 + 7;
int jc[N], inv[N], L, d, m, f[3005], dp[N], s[N], ans;
pii a[3005];

int add(int a, int b) { a = (a + b) % P; return a < 0 ? a + P : a;}

int mul(int a, int b) {return 1ll * a * b % P;}

int kpow(int a, int b) {
	int r = 1;
	while (b) {
		if (b & 1) r = mul(r, a);
		a = mul(a, a);
		 b >>= 1;
	}
	return r;
}

int C(ll n, ll m) {
	if (n < 0 || m < 0 || n < m) return 0;
	return mul(jc[n], mul(inv[m],  inv[n - m]));
}

int h(int l, int r, int k) {
	 r -= l;
	 if (k <= 0 || r <= 0) return 0;
	return C(r - 1ll * k * (d - 1) - 1, k - 1);
}

int main() {
	de(pow(1e5, 5.0 / 3));
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> L >> d >> m;
	dp[0] = s[0] = 1;
	rep(i, 1, L+1) {
		if (i >= d) dp[i] = s[i - d];
		s[i] = add(s[i-1], dp[i]);
	}

	jc[0] = 1; rep(i, 1, N) jc[i] = mul(jc[i-1], i);
	inv[N - 1] = kpow(jc[N - 1], P - 2);
	per(i, 0, N - 1) inv[i] = mul(inv[i+1], i+1);
	rep(i, 1, m+1) cin >> a[i].fi >> a[i].se;
	sort(a+1, a+m+1);
	m = unique(a + 1, a + m + 1) - (a + 1);
	rep(i, 1, m+1) {
		f[i] = h(0, a[i].se, a[i].fi);
		//de(f[i]);
		rep(j, 1, i) f[i] = add(f[i], -mul(f[j], h(a[j].se, a[i].se, a[i].fi - a[j].fi)));
		ans = add(ans, mul(f[i], dp[L - a[i].se]));
	}
	cout << add(dp[L], -ans) << endl;
	return 0;
}

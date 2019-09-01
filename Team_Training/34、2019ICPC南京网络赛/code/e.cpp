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

const int P = 1e9 + 7; 
const int N = 1e6 + 6;
ll w, ans;
int M, p[N], g[N], f[N], u[N], T, s[N];

int add(int a, int b) {
	if ((a += b) >= P) a -= P;
	return a < 0 ? a + P : a;
}

int mul(int a, int b) {
	return 1ll * a * b % P;
}

int kpow(int a, int b) {
	int r = 1;
	while (b) {
		if (b & 1) r = mul(r, a);
		a = mul(a, a);
		b >>= 1;
	}
	return r;
}

void prime(int n) {
	u[1] = 1;
	rep(i, 2, n+1) {
		if (!f[i]) {
			p[++M] = i;
			f[i] = g[i] = i;
			u[i] = -1;
		}
		for (int j = 1, k; j <= M && p[j] <= f[i] && i * p[j] <= n; j ++) {
			f[k = i * p[j]] = p[j];
			if (p[j] < f[i]) {
				g[k] = p[j];
				u[k] = u[i] * u[p[j]];
			}else {
				g[k] = g[i] * p[j];
				u[k] = 0;
			}
		}
	}
	rep(i, 1, n+1) for (int j = i; j <= n; j += i) {
		s[j] = add(s[j], mul(mul(i, i), u[j / i]));
	}
	rep(i, 1, n+1) s[i] = add(s[i-1], s[i]);
}

int inv6 = kpow(6, P - 2);

unordered_map<int, int> S;

int F(int n) {
	if (n <= 1e6) return s[n];
	if (S.count(n)) return S[n];
	int res = mul(n, mul(n + 1, 2 * n + 1));
	res = mul(res, inv6);
	for (int l = 2, r; l <= n; l = r + 1) {
		r = n / (n / l);
		res = add(res, - mul(r - l + 1, F(n / l)));
	}
	return S[n] = res;
}

int n, k, kk;
string ss;

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	prime(1000000);
	cin >> T;
	rep(cas, 0, T) {
		cin >> n >> ss; ans = 0; k = 0; kk = 0;
		rep(i, 0, sz(ss)) k = (1ll * k * 10 + ss[i] - '0') % (P - 1), kk = (1ll * kk * 10 + ss[i] - '0') % P;
		if (k == 0) k = P - 1;
		for (int l = 1, r; l <= n; l = r + 1) {
			int t = n / l;
			r = n / t;
			if (t == 1) w = kk - 1; else w = 1ll * t * t % P * (1 - kpow(t, k-1)) % P * (kpow(1 - t, P - 2)) % P;
			ans = add(ans, mul(w, add(F(r), -F(l - 1))));
		}
		ans = (ans % P + P) % P;
		cout << ans << endl;
	}
	return 0;
}

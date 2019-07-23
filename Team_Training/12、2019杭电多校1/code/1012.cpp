#include<bits/stdc++.h>
using namespace std;
#define fi first 
#define se second
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define mp make_pair
#define pb push_back
#define de(x) cout << #x << " = " << x << endl
#define dd(x) cout << #x << " = " << x << " "
#define endl '\n'
#define all(a) a.begin(), a.end()
#define sz(a) (int)a.size()
#define pw(x) (1ll << (x))
typedef long long ll;
typedef pair<int, int> pii;
typedef double db;
typedef vector<int> vi;

const int M = 1 << 20 << 1;
int a[M], b[M], c[M], d[M], n, m, cnt[10], T;
ll jc[M], inv[M], ans;
const int G = 3, P = 998244353;

struct NTT{
	int N, na, nb, w[2][M], rev[M];
	ll kpow(ll a, int b) {
		ll c = 1;
		for (;b;b >>= 1, a = a * a % P) if (b & 1) c = c * a % P;
		return c;
	}
	void FFT(int *a, int f) {
		rep(i, 0, N) if (i < rev[i]) swap(a[i], a[rev[i]]);
		for (int i = 1; i < N; i <<= 1) 
			for (int j = 0, t = N / (i << 1); j < N; j += i << 1) 
				for (int k = 0, l = 0, x, y; k < i; k ++, l += t) 
					x = (ll) w[f][l] * a[j+k+i] % P, y = a[j + k], a[j+k] = (y + x) % P, a[j + k + i] = (y - x + P) % P;
		if (f) for (int i = 0, x = kpow(N, P-2); i < N; i++) a[i] = (ll) a[i] * x % P;			
	}
	void work() {
		int d = __builtin_ctz(N);
		w[0][0] = w[1][0] = 1;
		for (int i = 1, x = kpow(G, (P - 1) / N), y = kpow(x, P - 2); i < N; i++) {
			rev[i] = (rev[i>>1] >> 1)| ((i & 1) << (d - 1));
			w[0][i] = (ll)x * w[0][i-1] % P, w[1][i] = (ll) y * w[1][i-1] % P;
		}
	}
	void doit(int n) {
		for (N = 1; N < n * 4 + 6; N <<= 1);
		rep(i, n, N) a[i] = b[i] = c[i] = d[i] = 0;
		work(); 
		FFT(a, 0);
		FFT(b, 0);
		FFT(c, 0);
		FFT(d, 0);
		rep(i, 0, N) a[i] = (ll)a[i] * b[i] % P * c[i] % P * d[i] % P;
		FFT(a, 1);
	}
} ntt;

int C(int n,int m) {
	if (n == m) return 1;
	if (m < 0 || n < m) return 0;
	return jc[n] * inv[m] % P * inv[n - m] % P;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> T;
	n = 1e6;
	jc[0] = 1; rep(i, 1, n+1) jc[i] = jc[i-1] * i % P;
	inv[n] = ntt.kpow(jc[n], P - 2); per(i, 0, n) inv[i] = inv[i+1] * (i + 1) % P;

	rep(cas, 0, T) {
		cin >> n >> m;
		rep(i, 0, n) cin >> a[i];
		cnt[1] = cnt[2] = cnt[3] = 0; int x;
		rep(i, 1, m+1) cin >> x, cnt[x] ++;
		rep(i, 0, n) b[i] = c[i] = d[i] = 0;
		for (int k = 0; k < n; k ++) b[k] = C(cnt[1] - 1 + k, cnt[1] - 1);
		for (int k = 0; k < n; k += 2) c[k] = C(cnt[2] - 1 + k / 2, cnt[2] - 1);
		for (int k = 0; k < n; k += 3) d[k] = C(cnt[3] - 1 + k / 3, cnt[3] - 1);
		ntt.doit(n);
		ans = 0;
		rep(i, 1, n+1) ans ^= (ll)a[i-1] * i;
		cout << ans << endl;
	} 
	return 0;
}

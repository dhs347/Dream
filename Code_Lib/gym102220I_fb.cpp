#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define rep(i, a, b) for(int i=(a); i<(b); i++)
#define per(i, a, b) for(int i=(b)-1; i>=(a); i--)
#define sz(a) (int)a.size()
#define de(a) cout << #a << " = " << a << endl
#define dd(a) cout << #a << " = " << a << " "
#define all(a) (a).begin(), (a).end()
#define pw(x) (1ll<<(x))
#define lb(x) ((x) & -(x))
#define endl "\n"
typedef double db;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;
const int P = 998244353;
int add(int a, int b) {if((a += b) >= P) a -= P; return a < 0 ? a + P : a;}
int mul(int a, int b) {return 1ll * a * b % P;}
int kpow(int a, int b) {int r=1;for(;b;b>>=1,a=mul(a,a)) {if(b&1)r=mul(r,a);}return r;}
//----

const int M = 1 << 17 << 2;
int a[M], b[M], jc[M], inv[M], w[M], T, n, ans;
unordered_map<int, int> f[M];
struct NTT{
	static const int G = 3; //P = C*2^k + 1
	int N, na, nb, w[2][M], rev[M];
	ll kpow(ll a, int b){
		ll c = 1;
		for (; b; b >>= 1,a = a * a % P) if (b & 1) c = c * a %P;
		return c;
	}
	void FFT(int *a, int f){
		rep(i, 0, N) if (i < rev[i]) swap(a[i], a[rev[i]]);
		for (int i = 1; i < N; i <<= 1)
			for (int j = 0, t = N / (i << 1); j < N; j += i << 1)
				for (int k = 0, l = 0, x, y; k < i; k++, l += t)
					x = (ll) w[f][l] * a[j+k+i] % P, y = a[j+k], a[j+k] = (y+x) % P, a[j+k+i] = (y-x+P) % P;
		if (f) for (int i = 0, x = kpow(N, P-2); i < N; i++) a[i] = (ll)a[i] * x % P;
	}
	void work(){
		int d = __builtin_ctz(N);
		w[0][0] = w[1][0] = 1;
		for (int i = 1, x = kpow(G, (P-1) / N), y = kpow(x, P-2); i < N; i++) {
			rev[i] = (rev[i>>1] >> 1) | ((i&1) << (d-1));
			w[0][i] = (ll)x * w[0][i-1] % P, w[1][i] = (ll) y * w[1][i-1] % P;
		}
	}
	void doit(int *a, int *b, int na, int nb){ // [0, na)
		if (na <= 0 || nb <= 0) return;
		for (N = 1; N < na + nb - 1; N <<= 1);
		rep(i, na, N) a[i] = 0;
		rep(i, nb, N) b[i] = 0;
		work(), FFT(a,0), FFT(b,0);
		rep(i, 0, N) a[i] = (ll)a[i] * b[i] % P;
		FFT(a, 1);
		//rep(i, 0, N) cout << a[i] << endl;
	}
} ntt;

 
int C(int n, int m) {
	if (m > n || m < 0) return 0;
	return mul(jc[n], mul(inv[m], inv[n - m]));
}

void solve(int l, int r, int d) {
	int mid = l + r >> 1, up = w[mid+1];
	if (l == r) {
		rep(i, d, w[l]+1) f[i][l] = add(f[i][l], add(f[i-1][l], f[i][l-1]));
		return;
	}
	if (up >= d) {
		solve(l, mid, d);
		l = mid + 1;
		rep(i, l, r+1) f[d][i] = add(f[d][i], f[d-1][i]);
		rep(i, d, up+1) f[i][l] = add(f[i][l], f[i][l-1]);
	
		if (up > d) {
			rep(i, d+1, up+1) a[i - d - 1] = mul(f[i][l], inv[up - i]);
			rep(i, 0, r - d - 1 - (l + 1 - up) + 1) b[i] = jc[up - l + i + (l + 1 - up)];
			ntt.doit(a, b, up - d, r - d - 1 - (l + 1 - up) + 1);
			rep(i, l+1, r+1) f[up][i] =  add(f[up][i], mul(inv[i - l], a[i - d - 1 - (l + 1 - up)]));
			
			rep(i, l, r+1) a[i - l] = mul(f[d][i], inv[up - d]);
			rep(i, 0, r - l + 1) b[i] = mul(jc[up - d + i], inv[i]);
			ntt.doit(a, b, r - l + 1, r - l + 1);
			rep(i, l+1, r+1) f[up][i] =  add(f[up][i], a[i - l]);	
		}
		if (l < r) {
			rep(i, d+1, up) a[i - d - 1] = mul(f[i][l], inv[r - l]);
			rep(i, 0, up - 1 - d) b[i] = mul(inv[i], jc[i + r - l]);
			ntt.doit(a, b, up - d - 1, up - d - 1);
			rep(i, d+1, up) if (i - d - 1 >= 0) f[i][r] =  add(f[i][r], a[i - d - 1]);
		
			rep(i, l, r+1) a[i - l] = mul(f[d][i], inv[r - i]);
			rep(i, 0, up - 1 - l - (d + 1 - r) + 1) b[i] = jc[r - d + (i + (d + 1 - r))];
			ntt.doit(a, b, r - l + 1, up - 1 - l - (d + 1 - r) + 1);
			rep(i, d+1, up) f[i][r] =  add(f[i][r], mul(inv[i - d], a[i - l - (d + 1 - r)]));
		}
		rep(i, d+1, up+1) f[i][l] = add(f[i][l], f[i-1][l]);
		rep(i, l+1, r+1) f[d][i] = add(f[d][i], f[d][i-1]);
		//rep(j, l, r + 1) rep(i, d, up+1) de(f[i][j]);
	}
	solve(mid+1, r, up+1);
}

int main() {
	freopen("a.in","r",stdin);
	ios::sync_with_stdio(0);
	cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	cin >> T;
	n = 5e5;
	jc[0] = 1;rep(i, 1, n+1) jc[i] = mul(jc[i-1], i);
	inv[n] = kpow(jc[n], P - 2);
	per(i, 0, n) inv[i] = mul(inv[i+1], i+1);
	rep(cas, 0, T) {
		cin >> n;
		rep(i, 0, n+2) f[i].clear();
		rep(i, 1, n+1) cin >> w[i];
		f[1][1] = 1;
		solve(1, n, 1);
		ans = 0;
		rep(i, 1, w[n]+1) ans = add(f[i][n], ans);
		cout << ans << endl;
	}
	return 0;
}



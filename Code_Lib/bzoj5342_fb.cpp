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

const int M = 1 << 17 << 1;

int f[M], a[M], b[M], T, n, ok, len, ans[M], g[M]; 
stack<pii> sta;

struct NTT{
	static const int M = :: M, G = 3, P = 998244353; //P = C*2^k + 1
	int N, na, nb, a[M], b[M], w[2][M], rev[M];
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
		rep(i, 0, N){
			int x = i, y = 0;
			for (int k = 1; k < N; x>>=1, k<<=1) (y<<=1) |= x&1;
			rev[i] = y;
		}
		w[0][0] = w[1][0] = 1;
		for (int i = 1, x = kpow(G, (P-1) / N), y = kpow(x, P-2); i < N; i++)
			w[0][i] = (ll)x * w[0][i-1] % P, w[1][i] = (ll) y * w[1][i-1] % P;
	}
	void doit(int *a, int *b, int na, int nb){ // [0, na)
		for (N = 1; N < na + nb - 1; N <<= 1);
		rep(i, na, N) a[i] = 0;
		rep(i, nb, N) b[i] = 0;
		work(), FFT(a,0), FFT(b,0);
		rep(i, 0, N) a[i] = (ll)a[i] * b[i] % P;
		FFT(a, 1);
		//rep(i, 0, N) cout << a[i] << endl;
	}
} ntt;


void solve(int l, int r) {
	if (l == r) {
		f[l] = add(mul(f[l-1], l - 1), f[l]);
		return;
	}
	int mid = l + r >> 1;
	solve(l, mid);
	if (r >= l * 2) {
		int ed = min(mid, r - l);
		rep(i, l, ed + 1) a[i - l] = mul(f[i], i - 1);
		rep(i, l, ed + 1) b[i - l] = f[i]; 
		ntt.doit(a, b, ed - l + 1, ed - l + 1);
		rep(i, max(2 * l, mid + 1), r+1) if (i <= 2 * ed) f[i] = add(f[i], a[i - 2 * l]); else break;
	} 
	if (l + 2 <= r && l + l - 1 >= mid + 1) {
		int ed = min(l - 1, r - l);
		rep(i, l, mid+1) a[i - l] = mul(f[i], i - 1);
		rep(i, 2, ed + 1) b[i - 2] = f[i]; 
		ntt.doit(a, b, mid + 1 - l, ed + 1 - 2);
		rep(i, max(l+2, mid+1), r+1) if (i <= mid + ed) f[i] = add(f[i], a[i - l - 2]);else break;
		rep(i, l, mid+1) a[i - l] = f[i];
		rep(i, 2, ed + 1) b[i - 2] = mul(f[i], i - 1); 
		ntt.doit(a, b, mid + 1 - l, ed + 1 - 2);
		rep(i, max(l+2, mid+1), r+1) if (i <= mid + ed) f[i] = add(f[i], a[i - l - 2]);else break;
	}
	solve(mid+1, r);
}

int main() {
	freopen("a.in","r",stdin);
	ios::sync_with_stdio(0);
	cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	cin >> T >> n;
	f[0] = 1; f[1] = 2;
	solve(2, n);
	rep(cas, 0, T) {
		ok = 1;
		while (!sta.empty()) sta.pop();
		rep(i, 1, n+1) {
			cin >> len;
			int tmp = 1, cnt = 0;
			if (!ok) continue; 
			while (!sta.empty() && sta.top().fi - sta.top().se >= i - len) {
				cnt++;tmp = mul(tmp, ans[sta.top().fi]); sta.pop();
			}
			if (!sta.empty() && i - len + 1 <= sta.top().fi) ok = 0;
			sta.push(mp(i, len)); 
			ans[i] = mul(tmp, f[cnt]);
		} 
		if (!ok || sz(sta) > 1) cout << 0 << endl;else cout << ans[n] << endl;
	}
	return 0;
}


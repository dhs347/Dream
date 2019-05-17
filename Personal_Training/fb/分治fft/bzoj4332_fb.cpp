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
int P;
int add(int a, int b) {if((a += b) >= P) a -= P; return a < 0 ? a + P : a;}
int mul(int a, int b) {return 1ll * a * b % P;}
int kpow(int a, int b) {int r=1;for(;b;b>>=1,a=mul(a,a)) {if(b&1)r=mul(r,a);}return r;}
//----

const int N = 1e4 + 67;
int m, n, o, s, u, f[N], g[N], ans, res[N];

const int M = 1 << 17 << 1;
const db pi = acos(-1);

struct vir{
	db r, i;
	vir(db r = 0.0, db i = 0.0) : r(r), i(i){}
	void print() {printf("%f %f\n", r, i);}
	vir operator +(const vir &c) {return vir(r + c.r, i + c.i);}
	vir operator -(const vir &c) {return vir(r - c.r, i - c.i);}
	vir operator *(const vir &c) {return vir(r * c.r - i * c.i, r * c.i + i * c.r);}
} a[M], b[M], w[2][M];

struct FFT{
	int N, na, nb, rev[M], ok;
	void fft(vir *a, int f){
		vir x, y;
		rep(i, 0, N) if (i < rev[i]) swap(a[i], a[rev[i]]);
		for (int i = 1; i < N; i <<= 1)
			for (int j = 0, t = N/(i<<1); j < N; j += i<<1)
				for (int k = 0, l = 0; k < i; k++, l += t) 
					x = w[f][l] * a[j+k+i], y = a[j+k], a[j+k] = y+x, a[j+k+i] = y-x;
		if (f) rep(i, 0, N) a[i].r /= N;
	}
	void work(){
		int d = __builtin_ctz(N);
		rep(i, 0, N) {
			rev[i] = (rev[i>>1] >> 1) | ((i&1) << (d-1));
			w[1][i] = w[0][i] = vir(cos(2*pi*i/N), sin(2*pi*i/N));
			w[1][i].i = -w[1][i].i;
		}
	}	
	void doit(vir *a, vir *b, int na, int nb){ // [0, na)
		if (!ok) for (N = 1; N < na + nb - 1; N <<= 1);
		rep(i, na, N) a[i] = vir(0, 0);
		rep(i, nb, N) b[i] = vir(0, 0);
		if (!ok) work(); 
		fft(a, 0), fft(b, 0);
		rep(i, 0, N) a[i] = a[i] * b[i];
		fft(a, 1);
		ok = 1;
		//rep(i, 0, N) a[i].print();
	}
} fft;

void solve(int n) {
	if (n == 1) {
		rep(i, 0, m+1) res[i] = g[i] = f[i];
		return;
	}
	if (n & 1) {
		solve(n - 1);
		rep(i, 0, m+1) a[i] = vir(g[i], 0);
		rep(i, 0, m+1) b[i] = vir(f[i], 0);
		fft.doit(a, b, m+1, m+1);
		rep(i, 0, m+1) g[i] = ((int)(a[i].r + 0.5) + f[i]) % P;
		rep(i, 0, m+1) a[i] = vir(res[i], 0);
		rep(i, 0, m+1) b[i] = vir(f[i], 0);
		fft.doit(a, b, m+1, m+1);
		rep(i, 0, m+1) res[i] = ((int)(a[i].r + 0.5)) % P;
	}else {
		solve(n / 2);
		rep(i, 0, m+1) a[i] = vir(g[i], 0);
		rep(i, 0, m+1) b[i] = vir(res[i], 0); b[0].r += 1;
		fft.doit(a, b, m+1, m+1);
		rep(i, 0, m+1) g[i] = ((int)(a[i].r + 0.5)) % P;
		rep(i, 0, m+1) a[i] = vir(res[i], 0);
		rep(i, 0, m+1) b[i] = vir(res[i], 0);
		fft.doit(a, b, m+1, m+1);
		rep(i, 0, m+1) res[i] = ((int)(a[i].r + 0.5)) % P;
	}
}

int main() {
	freopen("a.in","r",stdin);
	ios::sync_with_stdio(0);
	cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	cin >> m >> P;
	cin >> n >> o >> s >> u;
	rep(i, 1, m+1) f[i] = o * i * i % P + s * i % P + u, f[i] %= P;
	solve(n);
	cout << g[m] << endl;
	return 0;
}



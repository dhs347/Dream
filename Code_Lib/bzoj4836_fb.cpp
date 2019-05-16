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
const int P = 1e9 + 7;
int add(int a, int b) {if((a += b) >= P) a -= P; return a < 0 ? a + P : a;}
int mul(int a, int b) {return 1ll * a * b % P;}
int kpow(int a, int b) {int r=1;for(;b;b>>=1,a=mul(a,a)) {if(b&1)r=mul(r,a);}return r;}
//----

const int M = 1 << 17;
const db pi = acos(-1);

struct vir{
	db r, i;
	vir(db r = 0.0, db i = 0.0) : r(r), i(i){}
	void print() {printf("%lf %lf\n", r, i);}
	vir operator +(const vir &c) {return vir(r + c.r, i + c.i);}
	vir operator -(const vir &c) {return vir(r - c.r, i - c.i);}
	vir operator *(const vir &c) {return vir(r * c.r - i * c.i, r * c.i + i * c.r);}
} a[M*2], b[M*2], W[2][M*2];



struct FFT{
	int N, na, nb, rev[M*2];
	void fft(vir *a, int f){
		vir x, y;
		rep(i, 0, N) if (i < rev[i]) swap(a[i], a[rev[i]]);
		for (int i = 1; i < N; i <<= 1)
			for (int j = 0, t = N/(i<<1); j < N; j += i<<1)
				for (int k = 0, l = 0; k < i; k++, l += t) 
					x = W[f][l] * a[j+k+i], y = a[j+k], a[j+k] = y+x, a[j+k+i] = y-x;
		if (f) rep(i, 0, N) a[i].r /= N;
	}
	void work(){
		int d = __builtin_ctz(N);
		rep(i, 0, N) {
			rev[i] = (rev[i>>1] >> 1) | ((i&1) << (d-1));
			W[1][i] = W[0][i] = vir(cos(2*pi*i/N), sin(2*pi*i/N));
			W[1][i].i = -W[1][i].i;
		}
	}	
	void doit(vir *a, vir *b, int na, int nb, int op){
		if (op == 1) for (N = 1; N < na + nb - 1; N <<= 1);
		rep(i, na, N) a[i] = vir(0, 0);
		rep(i, nb, N) b[i] = vir(0, 0);
		if (op == 1) work();
		fft(a, 0), fft(b, 0);
		rep(i, 0, N) a[i] = a[i] * b[i];
		fft(a, 1);
		//rep(i, 0, N) a[i].print();
	}
} fft;


int  s1[M], s2[M], T, n, x, ma, q, m; 
ll ans[M];

void solve(int l, int r) {
	if (l == r) {
		ans[0] += 1ll * s1[l] * s2[l];
		return;
	}
	int mid = l + r >> 1;
	rep(i, l, mid+1) a[i - l] = vir(s1[i], 0);
	rep(i, mid+1, r+1) b[i - mid - 1] = vir(s2[i], 0);
	fft.doit(a, b, mid + 1 - l, r - mid, 1);
	rep(i, 0, r - l) ans[i + l + mid + 1] += (ll)(a[i].r + 0.5);
	rep(i, mid+1, r+1) a[i - mid - 1] = vir(s1[i], 0);
	rep(i, l, mid+1) b[i - l] = vir(s2[i], 0);
	reverse(b, b + mid + 1 - l);
	fft.doit(a, b, r - mid, mid + 1 - l, 0);
	rep(i, 0, r - l) ans[i + 1] += (ll)(a[i].r + 0.5); 
	solve(l, mid);
	solve(mid+1, r);
}

int main() {
	freopen("a.in","r",stdin);
	ios::sync_with_stdio(0);
	cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	cin >> T;
	rep(cas, 0, T) {
		cin >> n >> m >> q; ma = 0;
		rep(i, 1, n+1) {
			cin >> x; s1[x]++;
			ma = max(ma, x);
		}
		rep(i, 1, m+1) {
			cin >> x; s2[x]++;
			ma = max(ma, x);
		}
		solve(0, ma);
		rep(i, 0, q) {
			cin >> x;
			cout << ans[x] << endl;
		}
		rep(i, 0, ma+1) s1[i] = s2[i] = 0; 
		rep(i, 0, ma*2+1) ans[i] = 0;
	}
	return 0;
}



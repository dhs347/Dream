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
//---

const int NN = 40005;
const int mod = 1e9+7;

struct Edge{
	int u, v, w;
	int p[NN];
} edge[105];

ll cnt;
int n, m, t, fine, dis[55][55], u, v, w, k;

db f[55][NN], tmp, g[105][NN];

const int M = 1 << 16;
const db pi = acos(-1);

struct vir{
	db r, i;
	vir(db r = 0.0, db i = 0.0) : r(r), i(i){}
	void print() {printf("%lf %lf\n", r, i);}
} a[M*2], b[M*2], W[2][M*2];

vir operator +(const vir &a, const vir &b) {return vir(a.r + b.r, a.i + b.i);}
vir operator -(const vir &a, const vir &b) {return vir(a.r - b.r, a.i - b.i);}
vir operator *(const vir &a, const vir &b) {return vir(a.r * b.r - a.i * b.i, a.r * b.i + a.i * b.r);}

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
		rep(i, 0, N){
			int x = i, y = 0;
			for (int k = 1; k < N; x >>= 1, k <<= 1) (y<<=1)|=x&1;
			rev[i] = y;
		}
		rep(i, 0, N) {
			W[0][i] = vir(cos(2*pi*i/N), sin(2*pi*i/N));
			W[1][i] = vir(cos(2*pi*i/N), -sin(2*pi*i/N));
		}
	}	
	void doit(vir *a, vir *b, int na, int nb, int tid){
		if (tid == 1) for (N = 1; N < nb + na - 1; N <<= 1);
		rep(i, na, N) a[i] = vir(0, 0);
		rep(i, nb, N) b[i] = vir(0, 0);
		if (tid == 1) work();
		fft(a, 0), fft(b, 0);
		rep(i, 0, N) a[i] = a[i] * b[i];
		fft(a, 1);
		//rep(i, 0, N) a[i].print();
	}
} fft;

void calc(int l, int r) {
	int mid = (l + r) >> 1;
	rep(i, 1, m+1) {
		int v = edge[i].v;
		rep(j, mid+1, r+1) a[j - mid - 1] = {f[v][j], 0};
		rep(j, 0, r - l) b[j] = {1.0 * edge[i].p[r - l - j] / 100000, 0};
		fft.doit(a, b, r - mid, r - l, i);
		rep(j, l, mid+1) g[i][j] += a[j - mid - 1 + r - l].r;
	}
}

void solve(int l, int r) {	
	if (l == r) {
		rep(i, 1, m + 1) {
			u = edge[i].u; v = edge[i].v; w = edge[i].w;
			f[u][l] = min(f[u][l], g[i][l] + w);
		}
		return; 
	} 
	int mid = (l + r) >> 1;
	solve(mid + 1, r);
	calc(l, r);
	solve(l, mid);
}

int main(){
	freopen("a.in","r",stdin);
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout << setiosflags(ios::fixed);
	cout << setprecision(8);
	cin >> n >> m >> t >> fine;
	memset(dis, 0x3f, sizeof(dis));
	rep(i, 1, n+1) dis[i][i] = 0;
	rep(i, 1, m+1) {
		cin >> u >> v >> w;
		edge[i] = {u, v, w};
		dis[u][v] = min(dis[u][v], w);
		rep(j, 1, t+1) cin >> edge[i].p[j];
	}
	rep(k, 1, n+1) 
		rep(i, 1, n+1) 
			rep(j, 1, n+1) dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]); 
	rep(i, 1, n) rep(j, 0, t+1) f[i][j] = 1e9;
	rep(i, 1, n) rep(j, t, 2 * t + 1) f[i][j] = fine + dis[i][n];
	rep(j, t+1, 2 * t + 1) f[n][j] = fine;
	calc(0, t * 2);
	solve(0, t);
	cout << f[1][0];
	return 0;
}

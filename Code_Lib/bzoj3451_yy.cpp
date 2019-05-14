#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define sz(a) (int)a.size()
#define all(a) a.begin(), a.end()
#define pw(x) (1ll <<(x))
#define endl "\n"
#define de(a) cout << #a << " = " << a << endl
#define dd(a) cout << #a << " = " << a << " "
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef double db;

const int N = 101010;
const db eps = 0.1;

int n;
int sz[N];
ll ans[N];
bool vis[N];
vi g[N], vec[N];

const int M = 1<<15;
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
	void doit(vir *a, vir *b, int na, int nb){
		for (N = 1; N < na + nb - 1; N <<= 1);
		rep(i, na, N) a[i] = vir(0, 0);
		rep(i, nb, N) b[i] = vir(0, 0);
		work(), fft(a, 0), fft(b, 0);
		rep(i, 0, N) a[i] = a[i] * b[i];
		fft(a, 1);
		rep(i, 0, N) ans[i + 1] += (int)(a[i].r + eps);
	}
} fft;

void dfssz(int c, int fa, int Sz, int &rt) {
	sz[c] = 1;
	rep(i, 0, sz(g[c])) {
		int t = g[c][i];
		if(!vis[t] && t != fa) dfssz(t, c, Sz, rt), sz[c] += sz[t];
	}
	if(!rt && sz[c] * 2 > Sz) rt = c;
}

void dfs2(int u, int fa, int dep, int rt) {
	if(sz(vec[rt]) < dep + 1) vec[rt].pb(1);
	else ++vec[rt][dep];
	rep(i, 0, sz(g[u])) {
		int v = g[u][i];
		if(!vis[v] && v != fa) dfs2(v, u, dep + 1, rt);
	}
}

void dfs(int c) {
	int rt = 0; dfssz(c, 0, 0, rt); dfssz(c, 0, sz[c], rt = 0);
	vis[rt] = 1;
	vector<pii> ord;
	rep(i, 0, sz(g[rt])) {
		int u = g[rt][i];
		if(!vis[u]) {
			vec[u].clear();
			vec[u].pb(0);
			dfs2(u, rt, 1, u);
			ord.pb(mp(sz(vec[u]), u));
		}
	}
	sort(all(ord));
	ans[1]++;
	int pre = 0;
	rep(i, 0, sz(ord)) {
		int u = ord[i].se;
		rep(j, 0, sz(vec[u])) ans[j + 1] += vec[u][j];
		if(pre) {
			rep(t, 0, sz(vec[pre])) a[t] = vir(vec[pre][t], 0);
			rep(t, 0, sz(vec[u]  )) b[t] = vir(vec[u][t]  , 0);
			fft.doit(a, b, sz(vec[pre]), sz(vec[u]));
			rep(t, 0, sz(vec[pre])) vec[u][t] += vec[pre][t];
		}
		pre = u;
	}
	rep(i, 0, sz(g[rt])) if(!vis[g[rt][i]]) dfs(g[rt][i]);
}

int main() {
	cin >> n;
	rep(i, 1, n) {
		int u, v;
		scanf("%d%d", &u, &v);
		++u; ++v;
		g[u].pb(v);
		g[v].pb(u);
	}
	dfs(1);
	db res = 0;
	rep(i, 2, n + 1) ans[i] *= 2;
	rep(i, 1, n + 1) res += ans[i] * 1. / i;
	printf("%.4f\n", res);
	return 0;
}

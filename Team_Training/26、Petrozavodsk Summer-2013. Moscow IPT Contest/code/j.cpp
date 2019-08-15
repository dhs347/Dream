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
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()
#define endl '\n'
#define pw(x) (1ll<<(x))
typedef long long ll;
typedef pair<int, int> pii;
typedef double db;
typedef vector<int> vi;

const int N = 202020;

int n;
ll cnt[N];
int dis[N];
vi g[N], vec[N];

const int M = pw(19);
const db pi = acos(-1);

struct vir {
	db r, i;
	vir(db r = 0, db i = 0) : r(r), i(i) {}
	vir operator + (const vir &c) { return vir(r + c.r, i + c.i); }
	vir operator - (const vir &c) { return vir(r - c.r, i - c.i); }
	vir operator * (const vir &c) {
		return vir(r * c.r - i * c.i, r * c.i + i * c.r);
	}
}a[M], b[M], w[2][M];
int na, nb;

struct FFT {
	int N, na, nb, rev[M];
	void fft(vir * a, int f) {
		vir x, y;
		rep(i, 0, N) if(i < rev[i]) swap(a[i], a[rev[i]]);
		for(int i = 1; i < N; i <<= 1) {
			for(int j = 0, t = N / (i << 1); j < N; j += i << 1) {
				for(int k = 0, l = 0; k < i; k++, l += t) {
					x = w[f][l] * a[j + k + i], y = a[j + k], a[j + k] = y + x, a[j + k + i] = y - x;
				}
			}
		}
		if(f) rep(i, 0, N) a[i].r /= N;
	}
	void work() {
		int d = __builtin_ctz(N);
		rep(i, 0, N) {
			rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (d - 1));
			w[1][i] = w[0][i] = vir(cos(2 * pi * i / N), sin(2 * pi * i / N));
			w[1][i].i = -w[1][i].i;
		}
	}
	void doit(vir *a, vir *b, int na, int nb) {
		for(N = 1; N < na + nb - 1; N <<= 1);
		//rep(i, na, N) a[i] = vir(0, 0);
		//rep(i, nb, N) b[i] = vir(0, 0);
		work(), fft(a, 0), fft(b, 0);
		rep(i, 0, N) a[i] = a[i] * b[i];
		fft(a, 1);
	}
}fft;

bool vis[N];
int sz[N];
void dfssz(int c, int fa, int Sz, int &rt) {
	sz[c] = 1;
	for(auto t : g[c]) if(!vis[t] && t != fa) dfssz(t, c, Sz, rt), sz[c] += sz[t];
	if(!rt && sz[c] * 2 > Sz) rt = c;
}
void dfs(int u, int fa, int tp) {
	dis[u] = dis[fa] + 1;
	if(sz(g[u]) == 1) vec[tp].pb(u);
	for(auto v : g[u]) if(v != fa && !vis[v]) dfs(v, u, tp);
}
void dfs(int c) {
	int rt = 0;
	dfssz(c, 0, 0, rt);
	dfssz(c, 0, sz[c], rt = 0);
	vis[rt] = 1;
//	de(rt);

	dis[rt] = 0; for(auto u : g[rt]) if(!vis[u]) vec[u].clear(), dfs(u, rt, u);

	for(auto u : g[rt]) if(!vis[u]) {
		for(auto v : vec[u]) {
		//	dd(v), dd(u), de(dis[v]);
			a[dis[v]].r += 1;
			na = max(na, dis[v] + 1);
		}
	}
	nb = na; rep(i, 0, nb) b[i] = a[i];//, dd(a[i].r), de(a[i].i);
	//de(na);
	fft.doit(a, b, na, nb);
//	rep(i, 0, na << 1) dd(i), dd(a[i].r), de(a[i].i);
	rep(i, 0, na << 1) cnt[i] += round(a[i].r);
	rep(i, 0, fft.N) a[i] = b[i] = vir(0, 0); na = nb = 0;

	for(auto u : g[rt]) if(!vis[u] && sz(vec[u])) {
		for(auto v : vec[u]) {
			a[dis[v]].r += 1;
			na = max(na, dis[v] + 1);
			if(sz(g[rt]) == 1) cnt[dis[v]] += 2;
		}
		nb = na; rep(i, 0, nb) b[i] = a[i];
		fft.doit(a, b, na, nb);
		rep(i, 0, na << 1) cnt[i] -= round(a[i].r);
		rep(i, 0, fft.N) a[i] = b[i] = vir(0, 0); na = nb = 0;
	}

	for(auto t : g[rt]) if(!vis[t]) dfs(t);
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n;
	if(n == 1) {
		cout << 0 << endl;
		return 0;
	}
	rep(i, 1, n) {
		int u, v; cin >> u >> v;
		g[u].pb(v), g[v].pb(u);
	}
	dfs(1);
	int c = 0;
	rep(i, 1, n + 1) c += (cnt[i] > 0);
	cout << c << endl;
	rep(i, 1, n + 1) if(cnt[i]) {
	//	dd(i), de(cnt[i]);
		cout << i << endl;
	}
	return 0;
}

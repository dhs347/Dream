#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) -1; i >= (a); --i)
#define endl "\n"
#define pw(a) (1ll << (a))
#define all(a) a.begin(), a.end()
#define sz(a) (int)a.size()
#define de(x) cout << #x << " = " << x << endl
#define dd(x) cout << #x << " = " << x << " "
typedef long long ll;
typedef pair<int, int> pii;
typedef double db;
typedef vector<int> vi;

const int N = 101010;

int n, lg[N << 2], sta[N], ss[N << 2], tt[N << 2], ty[N], top, tmp[N], ct;
ll ans, val[N << 1], Add;

struct Gra {
	static const int N = ::N << 2;
	int L, hd[::N << 1], ne[N], fr[N], to[N]; ll val[N];
	inline void init(int n) { rep(i, 1, n + 1) hd[i] = -1; }
	inline void _add(int u, int v, ll w) { fr[L] = u; to[L] = v; val[L] = w; ne[L] = hd[u]; hd[u] = L++; }
	inline void add(int u, int v, ll w) { _add(u, v, w); _add(v, u, w); }
	inline void read() { init(n); rep(i, 1, n) { int u, v; ll w; cin >> u >> v >> w; add(u, v, w); } }
};
struct Gra3 {
	static const int N = ::N << 2;
	int L, hd[::N << 2], ne[N], to[N];
	inline void init(int n) { rep(i, 1, n + 1) hd[i] = -1; }
	inline void add(int u, int v) { to[L] = v; ne[L] = hd[u]; hd[u] = L++; }
};
struct LCARMQ {
	static const int N = ::N << 2;
	int a[21][N], lft[N], dep[N], L; ll dis[N];
	inline int rmin(int x, int y) { return dep[x] < dep[y] ? x : y; }
	inline void add(int x) { a[0][L++] = x; }
	void dfs(int c, int fa, const Gra &g) {
		lft[c] = L; add(c);
		for(int i = g.hd[c]; ~i; i = g.ne[i]) if(g.to[i] != fa) {
			int t = g.to[i];
			dep[t] = dep[c] + 1;
			dis[t] = dis[c] + g.val[i];
			dfs(t, c, g);
			add(c);
		}
	}
	inline void build(const Gra &g) {
		L = 0; dfs(1, 0, g); dep[0] = -1;
		rep(i,1,21){
			int lim = L+1-(1<<i);
			rep(j,0,lim) a[i][j] = rmin(a[i-1][j] , a[i-1][j+(1<<i>>1)]);
		}
	}
	inline int lca(const int &_x,const int &_y){
		int x = lft[_x] , y = lft[_y];
		if(x > y) swap(x , y);
		int i = lg[y-x+1];
		return rmin(a[i][x] , a[i][y+1-(1<<i)]);
	}
	inline ll Dis(const int &x, const int &y) { return dis[x] + dis[y] - 2 * dis[lca(x, y)]; }
}R1, R2, R3;
namespace T3 {
	Gra g;
}
namespace T2 {
	const int N = ::N << 1;
	Gra g; int tp[N], _, del[N], cntd, l[N], cntl;
	pii dp[N][2];
	ll dval[N][2];
	void init() { rep(i, 0, N) rep(j, 0, 2) dp[i][j] = mp(-1, -1); }
	inline bool cmp(int x, int y) { return R2.lft[x] < R2.lft[y]; }
	inline ll gao(const int &x, const int &y) { return val[x] + val[y] + R3.Dis(x, y); }
	inline void gao(const pii &a, const pii &b, ll c) {
		if(a.fi == -1 || b.fi == -1) return ;
		ans = max(ans, gao(a.fi, b.fi) + c);
		ans = max(ans, gao(a.fi, b.se) + c);
		ans = max(ans, gao(a.se, b.fi) + c);
		ans = max(ans, gao(a.se, b.se) + c);
	}
	inline void upd(pii &a, const pii &b, ll &va, ll &vb) {
		pii ans = a; ll res = va;
		if(a.fi == -1 || (b.fi != -1 && vb > va)) ans = b, res = vb;
		int arr[2] = {a.fi, a.se};
		int brr[2] = {b.fi, b.se};
		rep(i, 0, 2) if(arr[i] != -1) rep(j, 0, 2) if(brr[j] != -1) {
			ll t = gao(arr[i], brr[j]);
			if(res < t) {
				res = t;
				ans = mp(arr[i], brr[j]);
			}
		}
		a = ans, va = res;
	}
	inline void add(int u) {
		if(ty[u] != -1) dp[u][ty[u]] = mp(u, u), dval[u][ty[u]] = 0;
	}
	inline void solve(int u, int v) {
		gao(dp[u][0], dp[v][1], Add - 2 * R2.dis[u]);
		gao(dp[u][1], dp[v][0], Add - 2 * R2.dis[u]);
		upd(dp[u][0], dp[v][0], dval[u][0], dval[v][0]);
		upd(dp[u][1], dp[v][1], dval[u][1], dval[v][1]);
	}
	inline void solve0(int ss, int tt) {
		_ = cntd = 0; del[++cntd] = tp[_++] = sta[ss], add(del[cntd]);
		rep(i, ss + 1, tt + 1) {
			int lca = R2.lca(tp[_ - 1], sta[i]);
			cntl = 0; while(_ > 0 && R2.dep[lca] < R2.dep[tp[_-1]]) l[++cntl] = tp[--_];
			if(_ == 0 || lca != tp[_-1]) del[++cntd] = tp[_++] = lca, add(del[cntd]);
			l[++cntl] = tp[_-1]; del[++cntd] = tp[_++] = sta[i], add(del[cntd]);
			rep(i, 2, cntl + 1) {
				int u = l[i], v = l[i - 1];
				solve(u, v);
			}
		}
		per(i, 0, _ - 1) {
			int u = tp[i], v = tp[i + 1];
			solve(u, v);
		}
		rep(i, 1, cntd + 1) {
			int u = del[i];
			dp[u][0] = dp[u][1] = mp(-1, -1);
		}
	}
}
namespace T1 {
	const int N = ::N << 1;
	Gra G, g; Gra3 T;
	int L, n, sz[N], S, U, I, cnt[2];
	bool vis[N << 1];
	void rebuild(int u, int fa) {
		if(u == 1) L = n = ::n, g.init(n << 1), T.init(n << 2);
		bool F = 0; int pre = u;
		for(int i = G.hd[u]; ~i; i = G.ne[i]) if(G.to[i] != fa) {
			if(F) {
				if(~G.ne[i]) {
					g.add(pre, ++n, 0);
					g.add(n, G.to[i], G.val[i]);
					pre = n;
				} else {
					g.add(pre, G.to[i], G.val[i]);
				}
			} else {
				g.add(u, G.to[i], G.val[i]);
				F = 1;
			}
			rebuild(G.to[i], u);
		}
	}
	void dfs(int u, int fa) {
		sz[u] = 1;
		for(int i = g.hd[u]; ~i; i = g.ne[i]) if(!vis[i] && g.to[i] != fa) {
			dfs(g.to[i], u);
			sz[u] += sz[g.to[i]];
		}
	}
	void dfs(int u, int fa, int tot) {
		for(int i = g.hd[u]; ~i; i = g.ne[i]) if(!vis[i] && g.to[i] != fa) {
			int v = g.to[i];
			dfs(v, u, tot);
			if(S > max(sz[v], tot - sz[v])) {
				S = max(sz[v], tot - sz[v]);
				I = i;
			}
		}
	}
	int build(int u) {
		dfs(u, 0); if(sz[u] == 1) return u;
		S = N; dfs(u, 0, sz[u]);
		vis[I] = vis[I ^ 1] = 1;
		int _ = (I >> 1) + 1 + n, st = g.fr[I >> 1 << 1], ed = g.to[I >> 1 << 1];
		T.add(_, build(st));
		T.add(_, build(ed));
		return _;
	}
	void solve(int u) {
		if(u <= n) {
			if(u <= L) ss[u] = tt[u] = ++top, sta[top] = u;
			else ss[u] = top + 1, tt[u] = top;
			return ;
		}
		int st = -1, ed = -1;
		for(int i = T.hd[u]; ~i; i = T.ne[i]) {
			solve(T.to[i]);
			(ed == -1) ? (ed = T.to[i]) : (st = T.to[i]);
		}
		int I = (u - 1 - n) << 1, fr = g.fr[I], to = g.to[I];
		ss[u] = ss[ed], tt[u] = tt[st], Add = g.val[I];
		rep(i, ss[st], tt[st] + 1) ty[sta[i]] = 0, val[sta[i]] = R1.Dis(fr, sta[i]);
		rep(i, ss[ed], tt[ed] + 1) ty[sta[i]] = 1, val[sta[i]] = R1.Dis(to, sta[i]);
		rep(i, ss[u], tt[u] + 1) val[sta[i]] += R2.dis[sta[i]];
		ct = ss[u];
		int p = ss[st], q = ss[ed];
		while(p <= tt[st] && q <= tt[ed]) {
			int a = sta[p], b = sta[q];
			if(R2.lft[a] < R2.lft[b]) {
				tmp[ct++] = a; ++p;
			} else {
				tmp[ct++] = b; ++q;
			}
		}
		while(p <= tt[st]) tmp[ct++] = sta[p++];
		while(q <= tt[ed]) tmp[ct++] = sta[q++];
		rep(i, ss[u], tt[u] + 1) sta[i] = tmp[i];
		if(ss[st] <= tt[st] && ss[ed] <= tt[ed]) T2::solve0(ss[u], tt[u]);
		rep(i, ss[u], tt[u] + 1) ty[sta[i]] = -1;
	}
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	rep(i, 2, N << 2) lg[i] = lg[i >> 1] + 1;
	cin >> n; T1::G.read(); T2::g.read(); T3::g.read();
	memset(ty, -1, sizeof(ty)); T2::init(); R2.build(T2::g); R3.build(T3::g);
	T1::rebuild(1, 0); R1.build(T1::g); T1::solve(T1::build(1)); 
	cout << ans << endl;
	return 0;
}

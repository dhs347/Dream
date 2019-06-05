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

const int N = 5e5 + 5;

int n, m;
int id[N];
char s[N];
vi g[N << 1];

// read untill EOF (xint)

struct FastIO {

	static const int S = 1310720;

	int wpos;

	char wbuf[S];

	bool ed;

	FastIO() : wpos(0), ed(0) { }

	inline int xchar() {

		static char buf[S];

		static int len = 0, pos = 0;

		if (pos == len) pos = 0, len = fread(buf, 1, S, stdin);

		if (pos == len) return -1;

		return buf[pos++];

	}

	inline int xint() {

		int c = xchar(), x = 0, s = 1;

		while (c <= 32) {

			if(!~c) return ed = 1;

			c = xchar();

		}

		if (c == '-') s = -1, c = xchar();

		for (; '0' <= c && c <= '9'; c = xchar()) x = x * 10 + c - '0';

		return x * s;

	}

	inline int xuint() {

		int c = xchar(), x = 0;

		while (c <= 32) c = xchar();

		for (; '0' <= c && c <= '9'; c = xchar()) x = x * 10 + c - '0';

		return x;

	}

	inline void xstring(char *s) {

		int c = xchar();

		while (c <= 32) c = xchar();

		for (; c >  32; c = xchar()) *s++ = c;

		*s = 0;

	}

	inline void wchar(int x) {

		if (wpos == S) fwrite(wbuf, 1, S, stdout), wpos = 0;

		wbuf[wpos++] = x;

	}

	inline void wint(int x) {

		if (x < 0) wchar('-'), x = -x;

		char s[24];

		int n = 0;

		while (x || !n) s[n++] = '0' + x % 10, x /= 10;

		while (n--) wchar(s[n]);

	}

	inline void wll(ll x) {

		if (x < 0) wchar('-'), x = -x;

		char s[48];

		int n = 0;

		while (x || !n) s[n++] = '0' + x % 10, x /= 10;

		while (n--) wchar(s[n]);

	}

	inline void wstring(const char *s) {

		while (*s) wchar(*s++);

	}

	~FastIO() {

		if (wpos) fwrite(wbuf, 1, wpos, stdout), wpos = 0;

	}

} io;

struct SAM {
	static const int N = ::N << 1, M = 26;
	int par[N], l[N], ne[N][M], cnt[N], cur[N], bla[N];
	int rt, last, L;
	void add(int c) {
		int p = last, np = ++L;
		fill(ne[np], ne[np] + M, 0);
		l[np] = l[p] + 1;
		last = np;
		while(p && !ne[p][c]) ne[p][c] = np, p = par[p];
		if(!p) par[np] = rt;
		else{
			int q = ne[p][c];
			if(l[q] == l[p] + 1) par[np] = q;
			else {
				int nq = ++L;
				l[nq] = l[p] + 1;
				copy(ne[q], ne[q] + M, ne[nq]);
				par[nq] = par[q];
				par[q] = par[np] = nq;
				while(p && ne[p][c] == q) ne[p][c] = nq, p = par[p];
			}
		}
	}
	void ini() {
		rt = last = L = 1;
		fill(ne[rt], ne[rt] + M, 0);
		l[0] = -1;
	}
	void build() {
		rep(i, 1, L + 1) g[par[i]].pb(i);
		int p = rt;
		rep(i, 1, n + 1) {
			p = ne[p][s[i] - 'a'];
			id[n - i + 1] = p;
		}
	}
}sam;
// N is 2 size of tree , id of nodes start from 1
struct LCARMQ{
	static const int N = ::N << 2;
	int a[22][N] , lft[N] , dep[N] , lg[N] , L;
	int rmin(int x,int y){return dep[x] < dep[y] ? x : y;}
	void add(int x){ a[0][L++] = x;}
	void dfs(int c,int fa,const vi g[]){
		lft[c]=L;add(c);
		rep(i, 0, sz(g[c])) {
			int t = g[c][i];
			if(t!=fa) dep[t]=dep[c]+1,dfs(t,c,g),add(c);
		}
	}
	void Build(const vi g[]){
		L = 0;dfs(1,0,g);dep[0] = -1;
		rep(i,2,L) lg[i]=lg[i>>1]+1;
		rep(i,1,22){
			int lim = L+1-(1<<i);
			rep(j,0,lim) a[i][j] = rmin(a[i-1][j] , a[i-1][j+(1<<i>>1)]);
		}
	}
	int lca(int x,int y){
		x = lft[x] , y = lft[y];
		if(x > y) swap(x , y);
		int i = lg[y-x+1];
		return rmin(a[i][x] , a[i][y+1-(1<<i)]);
	}
}R;

namespace Vtree{
	const int N = ::N << 1;
	int tp[N] , _, cnt[N];
	ll ans;
	int del[N], cntd;
	int l[N], cntl;
	void solve(vi&v,LCARMQ&R){
		rep(i, 0, sz(v)) ++cnt[v[i]];
		_ = cntd = 0;
		del[++cntd] = tp[_++] = v[0];
		rep(i,1,sz(v)){
			int lca = R.lca(tp[_-1] , v[i]);
			cntl = 0;
			while(_ > 0 && R.dep[lca] < R.dep[tp[_-1]]) l[++cntl] = tp[--_];
			if(_ == 0 || lca != tp[_-1]) del[++cntd] = tp[_++] = lca;
			l[++cntl] = tp[_-1]; del[++cntd] = tp[_++] = v[i];
			rep(i, 2, cntl + 1) {
				int u = l[i], v = l[i - 1];
				ans += cnt[u] * 1ll * cnt[v] * sam.l[u];
				cnt[u] += cnt[v];
			}
		}
		per(i,0,_-1) {
			int u = tp[i], v = tp[i + 1];
			ans += cnt[u] * 1ll * cnt[v] * sam.l[u];
			cnt[u] += cnt[v];
		}
		rep(i, 1, cntd + 1) {
			int t = del[i];
			cnt[t] = 0;
		}
		io.wll(ans);
		io.wchar('\n');
		ans = 0;
	}
}
bool cmp(int i, int j) {
	return R.lft[i] < R.lft[j];
}

int main() {
	n = io.xint();
	m = io.xint();
	io.xstring(s + 1);
	sam.ini();
	reverse(s + 1, s + 1 + n);
	rep(i, 1, n + 1) sam.add(s[i] - 'a');
	sam.build();
	R.Build(g);
	while(m--) {
		vi v;
		int k = io.xint();
		while(k--) {
			int x = io.xint();
			v.pb(id[x]);
		}
		sort(all(v), cmp);
		v.erase(unique(all(v)), v.end());
		if(sz(v) <= 1) {
			io.wint(0);
			io.wchar('\n');
			continue;
		}
		Vtree::solve(v, R);
	}
	return 0;
}

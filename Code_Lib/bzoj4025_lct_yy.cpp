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

const int N = 101010, M = 202020;

int n, m, T, cnt;
pair<pii, pii> e[M];
pii E[M];
vi vec[N];

struct Node { int id, mi, cnt, fa, son[2]; bool rev; };
struct LCT {
	static const int N = ::N + ::M;
	Node nd[N]; int sta[N];
	// if(no root) return 1
	bool nrt(int x) {
		int fa = nd[x].fa;
		return nd[fa].son[0] == x || nd[fa].son[1] == x;
	}
	void init() {
		rep(i, 1, n + 1) nd[i].id = 0;
		rep(i, 1, m + 1) nd[i + n].id = i;
	}
	void up(int x) {
		if(!x) return ;
		nd[x].mi = nd[x].id;
		nd[x].cnt = (x > n);
		rep(o, 0, 2) if(nd[x].son[o]) {
			int s = nd[x].son[o];
			if(e[nd[s].mi].se.se < e[nd[x].mi].se.se) nd[x].mi = nd[s].mi;
			nd[x].cnt += nd[s].cnt;
		}
	}
	void gao(int x) {
		if(!x) return ;
		nd[x].rev ^= 1, swap(nd[x].son[0], nd[x].son[1]);
	}
	void down(int x) { if(nd[x].rev) gao(nd[x].son[0]), gao(nd[x].son[1]), nd[x].rev = 0; }
	int id(int u) { return nd[nd[u].fa].son[1] == u; }
	void rot(int x) {
		int y = nd[x].fa, z = nd[y].fa;
		int l = id(x), r = (l ^ 1), s = nd[x].son[r];
		if(nrt(y)) nd[z].son[id(y)] = x; nd[x].son[r] = y; nd[y].son[l] = s;
		if(s) nd[s].fa = y; nd[y].fa = x; nd[x].fa = z;
		up(y), up(x);
	}
	void splay(int x) {
		int top = 0;
		for(int i = x; ; i = nd[i].fa) {
			sta[++top] = i;
			if(!nrt(i)) break;
		}
		while(top) down(sta[top--]);
		while(nrt(x)) {
			int y = nd[x].fa;
			if(nrt(y)) (id(x) ^ id(y)) ? rot(x) : rot(y);
			rot(x);
		}
	}
	void access(int x) { for(int y = 0; x ; y = x, x = nd[x].fa) splay(x), nd[x].son[1] = y, up(x); }
	// 换根
	void makeroot(int x) { access(x); splay(x); gao(x); } 
	// 找根
	int findroot(int x) {
		access(x); splay(x);
		while(nd[x].son[0]) down(x), x = nd[x].son[0];
		splay(x);
		return x;
	}
	// 加边
	void link(int x, int y) { 
		makeroot(x); 
		if(findroot(y) != x) nd[x].fa = y; 
	}
	// 删边
	void cut(int x, int y) {
		makeroot(x);
		if(findroot(y) == x && nd[y].fa == x && !nd[y].son[0]) nd[y].fa = nd[x].son[1] = 0, up(x);
	}
	void cut(int id) {
		if(E[id].fi == 0) {
		} else if(E[id].fi == -1) {
			--cnt;
		} else {
			cut(e[id].fi.fi, id + n);
			cut(e[id].fi.se, id + n);
		}
	}
	void link(int id) {
		int u = e[id].fi.fi, v = e[id].fi.se, ed = e[id].se.se;
		int w = id + n;
		if(findroot(u) == findroot(v)) {
			path(u, v);
			int y = v, mi = nd[y].mi;
			if(ed < e[mi].se.se) {
				if(nd[y].cnt % 2 == 0) {
					E[id] = mp(-1, -1);
					++cnt;
				} else {
					E[id] = mp(0, 0);
				}
			} else {
				int U = E[mi].fi, V = E[mi].se;
				if(nd[y].cnt % 2 == 0) {
					E[mi] = mp(-1, -1);
					++cnt;
				} else {
					E[mi] = mp(0, 0);
				}
				cut(U, mi + n); cut(V, mi + n);
				link(u, w); link(v, w);
				E[id] = mp(u, v);
			}
		} else {
			link(u, w); link(v, w);
			E[id] = mp(u, v);
		}
	}
	// nd[y]: 路径信息
	void path(int x, int y) { makeroot(x); access(y); splay(y); }
}lct;

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n >> m >> T;
	rep(i, 1, m + 1) {
		int u, v, st, ed;
		cin >> u >> v >> st >> ed;
		e[i] = mp(mp(u, v), mp(st, ed));
		vec[st].pb(i);
		vec[ed].pb(-i);
	}
	e[0].se.se = M;
	lct.init();
	rep(i, 0, T) {
		rep(j, 0, sz(vec[i])) {
			int id = vec[i][j];
			if(id > 0) {
				lct.link(id);
			} else {
				lct.cut(-id);
			}
		}
		cout << (cnt ? "No" : "Yes") << endl;
	}
	return 0;
}

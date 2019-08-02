#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define dd(x) cout << #x << " = " << x << " "
#define de(x) cout << #x << " = " << x << endl
#define pw(x) (1ll<<(x))
#define endl "\n"
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef double db;

const int N = 101010;

int n, m;

// init
// id starts from 1
// 不要修改 0 节点的值
struct Node { int val, ma, cnt, sz, ls, rs; ll r; bool rev;};
struct fhqTreap {
	static const int N = ::N;
	int rt, L; Node nd[N];
	void init() { rt = L = 0; srand(time(0)); }
	ll Rand() { return ((rand() * 1ll << 32) ^ (rand() * 1ll << 16) ^ rand()); }
	int newnode(int c) {
		nd[++L].r = Rand();
		nd[L].ma = nd[L].val = c;
		nd[L].cnt = nd[L].sz = 1;
		nd[L].ls = nd[L].rs = nd[L].rev = 0;
		return L;
	}
	void up(int x) {
		if(!x) return ;
		int ls = nd[x].ls, rs = nd[x].rs;
		nd[x].sz = nd[ls].sz + nd[rs].sz + nd[x].cnt;
		nd[x].ma = nd[x].val;
		if(ls) nd[x].ma = max(nd[x].ma, nd[ls].ma);
		if(rs) nd[x].ma = max(nd[x].ma, nd[rs].ma);
	}
	void gao(int x) {
		if(!x) return ;
		nd[x].rev ^= 1, swap(nd[x].ls, nd[x].rs);
	}
	void down(int x) {
		if(nd[x].rev) gao(nd[x].ls), gao(nd[x].rs), nd[x].rev = 0;
	}
	// u -> (<= c) (> c)
	void splitc(int u, int c, int &x, int &y) {
		if(u) {
			down(u);
			if(nd[u].val <= c) x = u, splitc(nd[u].rs, c, nd[u].rs, y);
			else y = u, splitc(nd[u].ls, c, x, nd[u].ls);
			up(u);
		} else {
			x = y = 0;
		}
	}
	// u -> (< c) (else)
	void split(int u, int c, int &x, int &y) {
		if(u) {
			down(u);
			int &ls = nd[u].ls, &rs = nd[u].rs;
			if(nd[u].val < c && nd[ls].ma < c) x = u, split(rs, c, rs, y);
			else y = u, split(ls, c, x, ls);
			up(u);
		} else {
			x = y = 0;
		}
	}
	// u -> (1 ~ k) (k+1 ~ L)
	// !!!: nd[].cnt == 1
	void splitk(int u, int k, int &x, int &y) {
		if(u) {
			down(u);
			int sz = nd[nd[u].ls].sz;
			if(sz < k) x = u, splitk(nd[u].rs, k - sz - 1, nd[u].rs, y);
			else y = u, splitk(nd[u].ls, k, x, nd[u].ls);
			up(u);
		} else {
			x = y = 0;
		}
	}
	int merge(int x, int y) {
		if(x && y) {
			if(nd[x].r < nd[y].r) { down(x), nd[x].rs = merge(nd[x].rs, y), up(x); return x; } 
			else { down(y), nd[y].ls = merge(x, nd[y].ls), up(y); return y; }
		} else return x + y;
	}
	void build() {
		rep(i, 1, n + 1) {
			int c; cin >> c;
			rt = merge(rt, newnode(c));
		}
	}
	int go(int rt, int k) {
		int ls = nd[rt].ls, rs = nd[rt].rs;
		if(nd[ls].sz >= k) return go(ls, k);
		if(nd[ls].sz + 1 == k) return nd[rt].val;
		return go(rs, k - nd[ls].sz - 1);
	}
	void solve() {
		int o; cin >> o;
		if(o == 1) {
			int l, m, r; cin >> l >> m >> r;
			int x, y, z;
			splitk(rt, m, x, y);
			splitk(y, r - m, y, z);
			rt = 0;
			while(x && y) {
				int p = go(x, 1), q = go(y, 1);
				if(p > q) swap(x, y), swap(p, q);
				int t;
				split(x, q, t, x);
				rt = merge(rt, t);
			}
			rt = merge(rt, x);
			rt = merge(rt, y);
			rt = merge(rt, z);
		} else {
			int k; cin >> k;
			cout << go(rt, k) << endl;
		}
	}
}T;

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n >> m;
	T.init();
	T.build();
	rep(i, 1, m + 1) T.solve();
	return 0;
}

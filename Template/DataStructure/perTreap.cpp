// init
// id starts from 1
// 不要修改 0 节点的值
struct Node { int val, cnt, sz, ls, rs; ll r, sum; bool rev; };
struct fhqTreap {
	static const int N = 3e7;
	int rt[::N], L; Node nd[N];
	void init() { L = 0; srand(time(0)); }
	ll Rand() { return ((rand() * 1ll << 32) ^ (rand() * 1ll << 16) ^ rand()); }
	int newnode(int c) {
		nd[++L].r = Rand();
		nd[L].val = nd[L].sum = c;
		nd[L].cnt = nd[L].sz = 1;
		nd[L].ls = nd[L].rs = nd[L].rev = 0;
		return L;
	}
	int newcopy(int x) {
		nd[++L] = nd[x];
		return L;
	}
	void up(int x) {
		if(!x) return ;
		int ls = nd[x].ls, rs = nd[x].rs;
		nd[x].sz = nd[ls].sz + nd[rs].sz + nd[x].cnt;
		nd[x].sum = nd[ls].sum + nd[rs].sum + nd[x].val;
	}
	void gao(int &x) {
		if(!x) return ;
		x = newcopy(x);
		nd[x].rev ^= 1, swap(nd[x].ls, nd[x].rs);
	}
	void down(int x) {
		if(nd[x].rev) gao(nd[x].ls), gao(nd[x].rs), nd[x].rev = 0;
	}
	// u -> (<= c) (> c)
	void splitc(int u, int c, int &x, int &y) {
		if(u) {
			u = newcopy(u), down(u);
			if(nd[u].val <= c) x = u, splitc(nd[u].rs, c, nd[u].rs, y);
			else y = u, splitc(nd[u].ls, c, x, nd[u].ls);
			up(u);
		} else {
			x = y = 0;
		}
	}
	// u -> (1 ~ k) (k+1 ~ L)
	// !!!: nd[].cnt == 1
	void splitk(int u, int k, int &x, int &y) {
		if(u) {
			u = newcopy(u), down(u);
			int sz = nd[nd[u].ls].sz;
			if(sz < k) x = u, splitk(nd[u].rs, k - sz - 1, nd[u].rs, y);
			else y = u, splitk(nd[u].ls, k, x, nd[u].ls);
			up(u);
		} else {
			x = y = 0;
		}
	}
	// sometimes do not need to newcopy
	int merge(int x, int y) {
		if(x && y) {
			if(nd[x].r < nd[y].r) { x = newcopy(x), down(x), nd[x].rs = merge(nd[x].rs, y), up(x); return x; } 
			else { y = newcopy(y), down(y), nd[y].ls = merge(x, nd[y].ls), up(y); return y; }
		} else return x + y;
	}
}T;

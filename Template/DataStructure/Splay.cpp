// init
// id starts from 1
// if go to vertex p, must splay(p)
struct Node { int val, fa, son[2], cnt, sz; bool rev; };
struct Splay {
	static const int N = ::N;
	int rt, L; Node nd[N];
	int newnode(int c, int fa = 0, int o = 0) {
		nd[++L].fa = fa;
		nd[fa].son[o] = L;
		nd[L].val = c;
		nd[L].son[0] = nd[L].son[1] = nd[L].rev = 0;
		nd[L].cnt = nd[L].sz = 1;
		return L;
	}
	void init(int n) { rt = L = 0; }
	void gao(int u) {
		if(!u) return ;
		nd[u].rev ^= 1, swap(nd[u].son[0], nd[u].son[1]);
	}
	void down(int u) {
		if(nd[u].rev) gao(nd[u].son[0]), gao(nd[u].son[1]), nd[u].rev = 0;
	}
	void up(int u) {
		if(!u) return ;
		int ls = nd[u].son[0], rs = nd[u].son[1];
		nd[u].sz = nd[ls].sz + nd[rs].sz + nd[u].cnt;
	}
	int id(int u) { return nd[nd[u].fa].son[1] == u; }
	void rot(int x) {
		int y = nd[x].fa, z = nd[y].fa;
		down(z), down(y), down(x);
		int l = id(x), r = (l ^ 1);
		nd[x].fa = z;
		if(z) nd[z].son[id(y)] = x;
		int &s = nd[y].son[l]; s = nd[x].son[r];
		if(s) nd[s].fa = y;
		nd[x].son[r] = y;
		nd[y].fa = x;
		up(y), up(x);
	}
	void splay(int x, int g = 0) {
		while(nd[x].fa != g) {
			int y = nd[x].fa, z = nd[y].fa;
			if(z != g) (id(x) ^ id(y)) ? rot(x) : rot(y);
			rot(x);
		}
		if(!g) rt = x;
	}
}T;

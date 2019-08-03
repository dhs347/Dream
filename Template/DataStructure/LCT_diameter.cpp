int fir(multiset<int> st) { return sz(st) ? *(st.rbegin()) : 0; }
int sec(multiset<int> st) { return sz(st) > 1 ? *(++st.rbegin()) : 0; }
void Era(multiset<int> &s, int x) { s.erase(s.find(x)); }
struct Node { int fa, son[2], lmx, rmx, mxs, sum; bool rev; multiset<int> chain, path; };
struct LCT {
	static const int N = 30303;
	Node nd[N]; int sta[N];
	void del(int x, int y) { Era(nd[x].chain, nd[y].lmx), Era(nd[x].path, nd[y].mxs); }
	void add(int x, int y) { nd[x].chain.insert(nd[y].lmx), nd[x].path.insert(nd[y].mxs); }
	void init() {
		rep(i, 1, n + m + 1) {
			nd[i].fa = nd[i].son[0] = nd[i].son[1] = nd[i].rev = 0;
			nd[i].lmx = nd[i].rmx = nd[i].mxs = nd[i].sum = 0;
			nd[i].chain.clear(), nd[i].path.clear();
		}
	}
	void up(int x) {
		if(!x) return ;
		int p = x, ls = nd[x].son[0], rs = nd[x].son[1];
		// 以下考虑的都是链 p 与 链 p 的所有虚子树
		nd[p].sum = nd[ls].sum + nd[rs].sum + (p > n); // 当前链的长度
		int cha = fir(nd[p].chain); // 从 p 沿虚儿子走的最远距离
		int L = max(cha, nd[ls].rmx) + (p > n); // 从 p 沿父亲走的最远距离
		int R = max(cha, nd[rs].lmx) + (p > n); // 从 p 沿实儿子走的最远距离
		nd[p].lmx = max(nd[ls].lmx, nd[ls].sum + R); // 从链顶出发的最远距离
		nd[p].rmx = max(nd[rs].rmx, nd[rs].sum + L); // 从链底出发的最远距离
		nd[p].mxs = max(nd[ls].mxs, nd[rs].mxs); // mxs[p] 表示当前范围的直径 
		Ma(nd[p].mxs, fir(nd[p].path)); // 虚子树的直径
		Ma(nd[p].mxs, nd[ls].rmx + R); // 经过 p 父边的答案
		Ma(nd[p].mxs, nd[rs].lmx + L); // 经过 u 向下实边的答案
		Ma(nd[p].mxs, cha + sec(nd[p].chain) + (p > n)); // 虚子树中到根路径最长的两条拼起来
	}
	void gao(int x) {
		if(!x) return ;
		nd[x].rev ^= 1;
		swap(nd[x].son[0], nd[x].son[1]);
		swap(nd[x].lmx, nd[x].rmx);
	}
	void access(int x) {
		for(int y = 0; x ; y = x, x = nd[x].fa) {
			splay(x);
			int &rs = nd[x].son[1];
			if(y) del(x, y);
			if(rs) add(x, rs);
			rs = y, up(x);
		}
	}
	void link(int x, int y) {
		makeroot(x);
		if(findroot(y) != x) makeroot(y), nd[x].fa = y, add(y, x), up(y);
	}
	int getAns() { access(1); splay(1); return nd[1].mxs; }
}lct;

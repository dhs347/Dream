int n, m, a[N], f[N][2];
namespace DP {
	struct Node { int fa, son[2]; Mat val, sum; };
	struct LCT {
		inline void up(int x) {
			nd[x].sum = nd[x].val;
			if(ls) nd[x].sum = nd[ls].sum * nd[x].sum;
			if(rs) nd[x].sum = nd[x].sum * nd[rs].sum;
		}
		inline void access(int x) {
			for(int y = 0; x; y = x, x = nd[x].fa) {
				splay(x);
				if(nd[x].son[1]) {
					// upd val[x]
				}
				if(y) {
					// upd val[x]
				}
				nd[x].son[1] = y; up(x);
			}
		}
		inline int upd(int x, int y) {
			access(x); splay(x); nd[x].val.a[1][0] += y - a[x];
			up(x); a[x] = y; 
			return max(nd[x].sum.a[0][0], nd[x].sum.a[1][0]);
		}
	}lct;
}

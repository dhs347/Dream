// O(nlogn)
// 区间取 max, 区间求和 
struct Seg {
#define ls rt << 1
#define rs ls | 1
	static const int N = ::N << 2;
	ll sum[N];
	int mi[N][2], cnt[N];
	void up(int rt) {
		sum[rt] = sum[ls] + sum[rs];
		rep(i, 0, 2) mi[rt][i] = min(mi[ls][i], mi[rs][i]);
		cnt[rt] = 0;
		rep(i, 0, 2) {
			if(mi[rt][0] == mi[ls | i][0]) cnt[rt] += cnt[ls | i];
			else mi[rt][1] = min(mi[rt][1], mi[ls | i][0]);
		}
	}
	void build(int l, int r, int rt) {
		if(l == r) {
			sum[rt] = mi[rt][0] = l; //modify
			mi[rt][1] = inf;
			cnt[rt] = 1;
			return ;
		}
		int mid = l + r >> 1;
		build(l, mid, ls);
		build(mid + 1, r, rs);
		up(rt);
	}
	void gao(int rt, int c) {
		if(c <= mi[rt][0]) return ;
		sum[rt] += 1ll * cnt[rt] * (c - mi[rt][0]);
		mi[rt][0] = c;
	}
	void down(int rt) {
		gao(ls, mi[rt][0]);
		gao(rs, mi[rt][0]);
	}
	void upd(int L, int R, int c, int l, int r, int rt) {
		if(L > R) return ;
		if(L <= l && r <= R && c < mi[rt][1]) {
			gao(rt, c);
			return ;
		}
		int mid = l + r >> 1;
		down(rt);
		if(L <= mid) upd(L, R, c, l, mid, ls);
		if(R > mid) upd(L, R, c, mid + 1, r, rs);
		up(rt);
	}
}seg;

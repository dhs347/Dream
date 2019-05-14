/*
 * 这里是覆盖次数大于 1 次的 
 */
struct Seg {
#define ls rt << 1
#define rs ls | 1
	static const int N = ::N << 2;
	int la[N], len[2][N];
	void up(int rt, int l, int r) {
		if(la[rt] >= 2) {
			len[0][rt] = r - l + 1;
			len[1][rt] = r - l + 1;
		} else if(la[rt] >= 1) {
			len[0][rt] = r - l + 1;
			len[1][rt] = (l == r) ? 0 : len[0][ls] + len[0][rs];
		} else {
			len[0][rt] = (l == r) ? 0 : len[0][ls] + len[0][rs];
			len[1][rt] = (l == r) ? 0 : len[1][ls] + len[1][rs];
		}
	}
	void upd(int L, int R, int c, int l, int r, int rt) {
		if(L <= l && r <= R) {
			la[rt] += c;
			up(rt, l, r);
			return ;
		}
		int mid = l + r >> 1;
		if(L <= mid) upd(L, R, c, l, mid, ls);
		if(R > mid) upd(L, R, c, mid + 1, r, rs);
		up(rt, l, r);
	}
}seg;

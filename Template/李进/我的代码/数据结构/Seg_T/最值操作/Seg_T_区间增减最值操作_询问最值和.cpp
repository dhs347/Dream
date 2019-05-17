struct node {
    int p, t, se;
    node () {}
    node (int p, int t, int se) : p(p), t(t), se(se) {}
    inline friend node combineMax(const node &a, const node &b) {
        node c;
        if (a.p < b.p) c.p = b.p, c.t = b.t, c.se = max(a.p, b.se);
		if (a.p > b.p) c.p = a.p, c.t = a.t, c.se = max(a.se, b.p);
        if (a.p == b.p) c.p = a.p, c.t = a.t + b.t, c.se = max(a.se, b.se);
        return c;
    }
    inline friend node combineMin(const node &a, const node &b) {
        node c;
        if (a.p > b.p) c.p = b.p, c.t = b.t, c.se = min(a.p, b.se);
        if (a.p < b.p) c.p = a.p, c.t = a.t, c.se = min(a.se, b.p);
		if (a.p == b.p) c.p = a.p, c.t = a.t + b.t, c.se = min(a.se, b.se);
        return c;
    }
    inline friend node operator + (const node &a, int p) {
        return node(a.p + p, a.t, a.se + p);
    }
};

struct Seg_T {
    node mx[N<<2], mi[N<<2]; int tag[N<<2],n,*a; ll s[N<<2],temp[3];
    # define ls (x<<1)
    # define rs (x<<1|1)
    inline void up(int x) {
        mx[x] = combineMax(mx[ls], mx[rs]);
        mi[x] = combineMin(mi[ls], mi[rs]);
        s[x] = s[ls] + s[rs];
    }
    inline void pushmax(int x, int l, int r, int p) {
        s[x] += 1ll * mi[x].t * (p - mi[x].p);
        mi[x].p = p; mx[x].p = max(mx[x].p, p);
        if (mi[x].p == mx[x].p) {
            mi[x].se = oo, mx[x].se = -oo;
            mi[x].t = mx[x].t = r-l+1;
            s[x] = 1ll * mi[x].p * (r-l+1);
        } else mx[x].se = max(mx[x].se, p);
    }
    inline void pushmin(int x, int l, int r, int p) {
        s[x] += 1ll * mx[x].t * (p - mx[x].p);
        mx[x].p = p; mi[x].p = min(mi[x].p, p);
        if (mi[x].p == mx[x].p) {
            mi[x].se = oo, mx[x].se = -oo;
            mi[x].t = mx[x].t = r-l+1;
            s[x] = 1ll * mi[x].p * (r-l+1);
        } else mi[x].se = min(mi[x].se, p);
    }
    inline void pushtag(int x, int l, int r, int p) {
        tag[x] += p; s[x] += 1ll * (r-l+1) * p;
        mx[x] = mx[x] + p, mi[x] = mi[x] + p;
    }
    inline void down(int x, int l, int r) {
        int mid = l+r>>1;
        if (tag[x]) {
            pushtag(ls, l, mid, tag[x]); pushtag(rs, mid+1, r, tag[x]);
            tag[x] = 0;
        }    
        if (mx[ls].p > mx[x].p && mx[ls].se < mx[x].p) pushmin(ls, l, mid, mx[x].p);
        if (mx[rs].p > mx[x].p && mx[rs].se < mx[x].p) pushmin(rs, mid+1, r, mx[x].p);
        if (mi[ls].p < mi[x].p && mi[ls].se > mi[x].p) pushmax(ls, l, mid, mi[x].p);
        if (mi[rs].p < mi[x].p && mi[rs].se > mi[x].p) pushmax(rs, mid+1, r, mi[x].p);    
    }
    void B(int x, int l, int r) {
        tag[x] = 0;
        if (l == r) {
            mx[x].p = mi[x].p = s[x] = (a!=NULL) ? a[l]:0, mx[x].t = mi[x].t = 1, mx[x].se = -oo, mi[x].se = oo;
            return ;
        }
        int mid = l+r>>1; B(ls, l, mid); B(rs, mid+1, r); up(x);
    }
    void upd(int x, int l, int r, int L, int R, int p) {
        if (L <= l && r <= R) { pushtag(x, l, r, p); return; }
        down(x, l, r); int mid = l+r>>1;
        if (L <= mid) upd(ls, l, mid, L, R, p);
        if (R > mid) upd(rs, mid+1, r, L, R, p); up(x);
    }
    void upd_min(int x, int l, int r, int L, int R, int p) {
        if (mx[x].p <= p) return ;
        if (L <= l && r <= R && mx[x].se < p) { pushmin(x, l, r, p); return; }
        down(x, l, r); int mid = l+r>>1;
        if (L <= mid) upd_min(ls, l, mid, L, R, p);
        if (R > mid) upd_min(rs, mid+1, r, L, R, p); up(x);
    }
    void upd_max(int x, int l, int r, int L, int R, int p) {
        if (mi[x].p >= p) return ;
        if (L <= l && r <= R && mi[x].se > p) { pushmax(x, l, r, p); return; }
        down(x, l, r); int mid = l+r>>1;
        if (L <= mid) upd_max(ls, l, mid, L, R, p);
        if (R > mid) upd_max(rs, mid+1, r, L, R, p); up(x);
    }
    int qmax(int x, int l, int r, int L, int R) {
        if (L <= l && r <= R) return mx[x].p;
        down(x, l, r); int mid = l+r>>1, ret = -oo;
        if (L <= mid) ret = max(ret, qmax(ls, l, mid, L, R));
        if (R > mid) ret = max(ret, qmax(rs, mid+1, r, L, R)); return ret;
    }
    int qmin(int x, int l, int r, int L, int R) {
        if (L <= l && r <= R) return mi[x].p;
        down(x, l, r); int mid = l+r>>1, ret = oo;
        if (L <= mid) ret = min(ret, qmin(ls, l, mid, L, R));
        if (R > mid) ret = min(ret, qmin(rs, mid+1, r, L, R)); return ret;
    }
    ll qsum(int x, int l, int r, int L, int R) {
        if (L <= l && r <= R) return s[x];
        down(x, l, r); int mid = l+r>>1; ll ret = 0;
        if (L <= mid) ret += qsum(ls, l, mid, L, R);
        if (R > mid) ret += qsum(rs, mid+1, r, L, R); return ret;
    }
	void Init(int _n,int *_a=NULL){ n=_n,a=_a; B(1,1,n); }
    void print(int x, int l, int r) {
        printf("%d %d %d [%d %d %d] [%d %d %d] %I64d\n", x, l, r, mx[x].p, mx[x].t, mx[x].se, mi[x].p, mi[x].t, mi[x].se, s[x]);
        if (l == r) return ;
        int mid = l+r>>1; print(ls, l, mid); print(rs, mid+1, r);
    }
    # undef ls
    # undef rs
};

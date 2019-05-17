# include <stdio.h>
# include <string.h>
# include <iostream>
# include <algorithm>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
const int N = 5e5 + 10, SN = 1048576 + 5;
const int mod = 1e9+7, inf = 1e9;

inline int getint() {
    int x = 0, f = 1; char ch = getchar();
    while(!isdigit(ch)) {
        if(ch == '-') f = 0;
        ch = getchar();
    }
    while(isdigit(ch)) {
        x = (x<<3) + (x<<1) + ch - '0';
        ch = getchar();
    }
    return f ? x : -x;
}

int n, a[N];
struct node {
    int p, t, se;
    node () {}
    node (int p, int t, int se) : p(p), t(t), se(se) {}
    inline friend node combineMax(node a, node b) {
        node c;
        if(a.p < b.p) {
            c.p = b.p; c.t = b.t;
            c.se = max(a.p, b.se);
        } else if(a.p > b.p) {
            c.p = a.p; c.t = a.t;
            c.se = max(a.se, b.p);
        } else {
            c.p = a.p; c.t = a.t + b.t;
            c.se = max(a.se, b.se);
        }
        return c;
    }
    inline friend node combineMin(node a, node b) {
        node c;
        if(a.p > b.p) {
            c.p = b.p; c.t = b.t;
            c.se = min(a.p, b.se);
        } else if(a.p < b.p) {
            c.p = a.p; c.t = a.t;
            c.se = min(a.se, b.p);
        } else {
            c.p = a.p; c.t = a.t + b.t;
            c.se = min(a.se, b.se);
        }
        return c;
    }
    inline friend node operator + (node a, int p) {
        return node(a.p + p, a.t, a.se + p);
    }
};

struct SMTbeats {
    node mx[SN], mi[SN];
    int tag[SN]; ll s[SN];
    # define ls (x<<1)
    # define rs (x<<1|1)
    inline void up(int x) {
        mx[x] = combineMax(mx[ls], mx[rs]);
        mi[x] = combineMin(mi[ls], mi[rs]);
        s[x] = s[ls] + s[rs];
    }
    
    // a = max(a, t)
    inline void pushmax(int x, int l, int r, int p) {
        s[x] += 1ll * mi[x].t * (p - mi[x].p);
        mi[x].p = p; mx[x].p = max(mx[x].p, p);
        if(mi[x].p == mx[x].p) {
            mi[x].se = inf, mx[x].se = -inf;
            mi[x].t = mx[x].t = r-l+1;
            s[x] = 1ll * mi[x].p * (r-l+1);
        } else mx[x].se = max(mx[x].se, p);
    }
    // a = min(a, t)
    inline void pushmin(int x, int l, int r, int p) {
        s[x] += 1ll * mx[x].t * (p - mx[x].p);
        mx[x].p = p; mi[x].p = min(mi[x].p, p);
        if(mi[x].p == mx[x].p) {
            mi[x].se = inf, mx[x].se = -inf;
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
        if(tag[x]) {
            pushtag(ls, l, mid, tag[x]); pushtag(rs, mid+1, r, tag[x]);
            tag[x] = 0;
        }    
        if(mx[ls].p > mx[x].p && mx[ls].se < mx[x].p) pushmin(ls, l, mid, mx[x].p);
        if(mx[rs].p > mx[x].p && mx[rs].se < mx[x].p) pushmin(rs, mid+1, r, mx[x].p);
        if(mi[ls].p < mi[x].p && mi[ls].se > mi[x].p) pushmax(ls, l, mid, mi[x].p);
        if(mi[rs].p < mi[x].p && mi[rs].se > mi[x].p) pushmax(rs, mid+1, r, mi[x].p);    
    }
    
    inline void build(int x, int l, int r) {
        tag[x] = 0;
        if(l == r) {
            mx[x].p = mi[x].p = s[x] = a[l], mx[x].t = mi[x].t = 1, mx[x].se = -inf, mi[x].se = inf;
            return ;
        }
        int mid = l+r>>1;
        build(ls, l, mid);
        build(rs, mid+1, r);
        up(x);
    }
    
    inline void edt(int x, int l, int r, int L, int R, int p) {
        if(L <= l && r <= R) {
            pushtag(x, l, r, p);
            return ;
        }
        down(x, l, r);
        int mid = l+r>>1;
        if(L <= mid) edt(ls, l, mid, L, R, p);
        if(R > mid) edt(rs, mid+1, r, L, R, p);
        up(x);
    }
    
    inline void edtmin(int x, int l, int r, int L, int R, int p) {
        if(mx[x].p <= p) return ;
        if(L <= l && r <= R && mx[x].se < p) {
            pushmin(x, l, r, p);
            return ;
        }
        down(x, l, r);
        int mid = l+r>>1;
        if(L <= mid) edtmin(ls, l, mid, L, R, p);
        if(R > mid) edtmin(rs, mid+1, r, L, R, p);
        up(x);
    }
    
    inline void edtmax(int x, int l, int r, int L, int R, int p) {
        if(mi[x].p >= p) return ;
        if(L <= l && r <= R && mi[x].se > p) {
            pushmax(x, l, r, p);
            return ;
        }
        down(x, l, r);
        int mid = l+r>>1;
        if(L <= mid) edtmax(ls, l, mid, L, R, p);
        if(R > mid) edtmax(rs, mid+1, r, L, R, p);
        up(x);
    }
    
    inline int gmax(int x, int l, int r, int L, int R) {
        if(L <= l && r <= R) return mx[x].p;
        down(x, l, r);
        int mid = l+r>>1, ret = -inf;
        if(L <= mid) ret = max(ret, gmax(ls, l, mid, L, R));
        if(R > mid) ret = max(ret, gmax(rs, mid+1, r, L, R));
        return ret;
    }
    
    inline int gmin(int x, int l, int r, int L, int R) {
        if(L <= l && r <= R) return mi[x].p;
        down(x, l, r);
        int mid = l+r>>1, ret = inf;
        if(L <= mid) ret = min(ret, gmin(ls, l, mid, L, R));
        if(R > mid) ret = min(ret, gmin(rs, mid+1, r, L, R));
        return ret;
    }
    
    inline ll gsum(int x, int l, int r, int L, int R) {
        if(L <= l && r <= R) return s[x];
        down(x, l, r);
        int mid = l+r>>1; ll ret = 0;
        if(L <= mid) ret += gsum(ls, l, mid, L, R);
        if(R > mid) ret += gsum(rs, mid+1, r, L, R);
        return ret;
    }

    inline void debug(int x, int l, int r) {
        printf("%d %d %d [%d %d %d] [%d %d %d] %I64d\n", x, l, r, mx[x].p, mx[x].t, mx[x].se, mi[x].p, mi[x].t, mi[x].se, s[x]);
        if (l == r) return ;
        int mid = l+r>>1;
        debug(ls, l, mid);
        debug(rs, mid+1, r);
    }
    
    # undef ls
    # undef rs
}T;



int main() {
    n = getint();
    for (int i=1; i<=n; ++i) a[i] = getint();
    T.build(1, 1, n);
    int Q, op, l, r, x; cin >> Q;
    while(Q--) {
//        T.debug(1, 1, n);
        op = getint(), l = getint(), r = getint();
        if(op == 1) {
            x = getint();
            T.edt(1, 1, n, l, r, x);
        } else if(op == 2) {
            x = getint();
            T.edtmax(1, 1, n, l, r, x);
        } else if(op == 3) {
            x = getint();
            T.edtmin(1, 1, n, l, r, x);
        } else if(op == 4) printf("%lld\n", T.gsum(1, 1, n, l, r));
        else if(op == 5) printf("%d\n", T.gmax(1, 1, n, l, r));
        else printf("%d\n", T.gmin(1, 1, n, l, r));
    }
    return 0;
}

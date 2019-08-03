#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define de(c) cout << #c << " = " << c << endl
#define dd(c) cout << #c << " = " << c << " "
#define all(c) c.begin(), c.end()
#define sz(x) (int)x.size()
#define endl '\n'
#define pw(x) (1ll << (x))
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef double db;
 
const int N = 20202;
 
int n, q;
 
struct EE {
    int u, v, w;
    void read() { cin >> u >> v >> w; if(u > v) swap(u, v); }
    bool operator < (const EE &c) const {
        if(u != c.u) return u < c.u;
        if(v != c.v) return v < c.v;
        return w < c.w;
    }
    bool operator == (const EE &c) const {
        return u == c.u && v == c.v && w == c.w;
    }
};
 
vector<EE> ve; int F(EE e) { return lower_bound(all(ve), e) - ve.begin() + 1; }
vi pre[N];
int cnte;
 
struct QQ {
    int o; EE e;
    inline void read() { cin >> o; e.read(); ve.pb(e); }
}Q[N];
 
int fir(multiset<int> st) {
    if(!sz(st)) return -1e9;
    auto t = st.end();
    --t;
    return *t;
}
int sec(multiset<int> st) {
    if(sz(st) <= 1) return -1e9;
    auto t = st.end();
    --t; --t;
    return *t;
}
void upd(int &a, int b) { if(a < b) a = b; }
void Era(multiset<int> &s, int x) {
    auto u = s.find(x);
    if(u == s.end()) de("ERR");
    else s.erase(u);
}
struct Node { int ma, fa, son[2], lmx, rmx, mxs, sum; bool rev; multiset<int> chain, path; };
struct LCT {
    static const int N = 30303;
    Node nd[N]; int sta[N];
    void init() {
        rep(i, 1, n + sz(ve) + 1) {
            nd[i].ma = nd[i].fa = nd[i].son[0] = nd[i].son[1] = nd[i].rev = 0;
            nd[i].lmx = nd[i].rmx = nd[i].mxs = nd[i].sum = 0;
            nd[i].chain.clear(), nd[i].path.clear();
        }
        rep(i, 1, sz(ve) + 1) nd[i + n].ma = i;
    }
    // if(no root) return 1
    bool nrt(int x) {
        int fa = nd[x].fa;
        return nd[fa].son[0] == x || nd[fa].son[1] == x;
    }
    void up(int x) {
        if(!x) return ;
        nd[x].ma = x <= n ? 0 : x - n;
        rep(o, 0, 2) {
            int s = nd[x].son[o];
            if(nd[s].ma) {
                if(!nd[x].ma || ve[nd[s].ma - 1].w > ve[nd[x].ma - 1].w) nd[x].ma = nd[s].ma;
            }
        }
        int p = x, ls = nd[x].son[0], rs = nd[x].son[1];
        nd[p].sum = nd[ls].sum + nd[rs].sum + (p > n);
        int cha = max(0, fir(nd[p].chain));
        int L = max(cha, nd[ls].rmx) + (p > n);
        int R = max(cha, nd[rs].lmx) + (p > n);
        nd[p].lmx = max(nd[ls].lmx, nd[ls].sum + R);
        nd[p].rmx = max(nd[rs].rmx, nd[rs].sum + L);
        nd[p].mxs = max(nd[ls].mxs, nd[rs].mxs);
        upd(nd[p].mxs, fir(nd[p].path));
        upd(nd[p].mxs, nd[ls].rmx + R);
        upd(nd[p].mxs, nd[rs].lmx + L);
        upd(nd[p].mxs, cha + sec(nd[p].chain) + (p > n));
        upd(nd[p].mxs, cha + (p > n));
    }
    void gao(int x) {
        if(!x) return ;
        nd[x].rev ^= 1, swap(nd[x].son[0], nd[x].son[1]);
        swap(nd[x].lmx, nd[x].rmx);
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
    void access(int x) {
        for(int y = 0; x ; y = x, x = nd[x].fa) {
            splay(x);
            int &rs = nd[x].son[1];
            if(y) {
                Era(nd[x].chain, nd[y].lmx); //dd(-__LINE__), dd(x), de(nd[y].lmx);
                Era(nd[x].path, nd[y].mxs);
            }
            if(rs) {
                nd[x].chain.insert(nd[rs].lmx);// dd(__LINE__), dd(x), de(nd[rs].lmx);
                nd[x].path.insert(nd[rs].mxs);
            }
            rs = y, up(x);
        }
    }
    void cut(int i) {
        int u = ve[i - 1].u, v = ve[i - 1].v;
        cut(u, i + n);
        cut(v, i + n);
        --cnte;
    }
    void link(int i) {
        int u = ve[i - 1].u, v = ve[i - 1].v;
        link(u, i + n);
        link(v, i + n);
        ++cnte;
    }
    void add(int i, vector<pii> &sta) {
        int u = ve[i - 1].u, v = ve[i - 1].v, w = ve[i - 1].w;
        if(findroot(u) == findroot(v)) {
            path(u, v);
            int j = nd[v].ma;
            if(ve[j - 1].w > w) cut(j), link(i), sta.pb(mp(j, -1)), sta.pb(mp(i, 1));;
        } else link(i), sta.pb(mp(i, 1));
    }
    void makeroot(int x) { access(x); splay(x); gao(x); }
    int findroot(int x) {
        access(x); splay(x);
        while(nd[x].son[0]) down(x), x = nd[x].son[0];
        splay(x);
        return x;
    }
    void link(int x, int y) {
        makeroot(x);
        if(findroot(y) != x) {
            makeroot(y);
            nd[x].fa = y;
            nd[y].chain.insert(nd[x].lmx);// dd(__LINE__), dd(y), de(nd[x].lmx);
            nd[y].path.insert(nd[x].mxs);
            up(y);
        }
    }
    void cut(int x, int y) {
        makeroot(x);
        if(findroot(y) == x && nd[y].fa == x && !nd[y].son[0]) nd[y].fa = nd[x].son[1] = 0, up(x);
    }
    void path(int x, int y) { makeroot(x); access(y); splay(y); }
}lct;
 
void print() {
    if(cnte != n - 1) {
        cout << -1 << endl;
        return ;
    }
    lct.access(1);
    lct.splay(1);
    cout << lct.nd[1].mxs << endl;
}
 
struct Seg {
#define ls rt << 1
#define rs ls | 1
    static const int N = ::N << 2;
    vi ad[N];
    void dfs(int l, int r, int rt) {
        vector<pii> sta;
        for(auto i : ad[rt]) lct.add(i, sta);
        if(l < r) {
            int mid = l + r >> 1;
            dfs(l, mid, ls);
            dfs(mid + 1, r, rs);
        } else {
            print();
        }
        per(u, 0, sz(sta)) {
            int i = sta[u].fi, j = sta[u].se;
            j > 0 ? lct.cut(i) : lct.link(i);
        }
    }
    void init(int n) { rep(i, 0, n << 2) ad[i].clear(); }
    void upd(int L, int R, int p, int l, int r, int rt) {
        if(L > R) return ;
        if(L <= l && r <= R) return ad[rt].pb(p), void();
        int mid = l + r >> 1;
        if(L <= mid) upd(L, R, p, l, mid, ls);
        if(R > mid) upd(L, R, p, mid + 1, r, rs);
    }
}seg;
 
void solve() {
    cnte = 0;
    ve.clear(); seg.init(q);
    rep(i, 1, q + 1) pre[i].clear();
    rep(i, 1, q + 1) Q[i].read();
    sort(all(ve)); ve.erase(unique(all(ve)), ve.end());
    rep(i, 1, q + 1) {
        int p = F(Q[i].e);
        if(Q[i].o) {
            pre[p].pb(i);
        } else {
            seg.upd(pre[p].back(), i - 1, p, 1, q, 1);
            pre[p].pop_back();
        }
    }
    rep(i, 1, sz(ve) + 1) if(sz(pre[i])) seg.upd(pre[i][0], q, i, 1, q, 1);
    lct.init();
    seg.dfs(1, q, 1);
}
 
int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    cin >> n >> q; solve();
    return 0;
}

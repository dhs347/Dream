#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define endl "\n"
#define pw(x) (1ll << (x))
#define all(x) x.begin(), x.end()
#define sz(a) (int)a.size()
#define de(x) io.wint(x), io.wchar('\n')
#define dd(x) io.wint(x), io.wchar(' ')
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int N = 1e6 + 7, inf = 1e9;

// read untill EOF (xint)
struct FastIO {
    static const int S = 1310720;
    int wpos;
    char wbuf[S];
    bool ed;
    FastIO() : wpos(0), ed(0) { }
    inline int xchar() {
        static char buf[S];
        static int len = 0, pos = 0;
        if (pos == len) pos = 0, len = fread(buf, 1, S, stdin);
        if (pos == len) return -1;
        return buf[pos++];
    }
    inline int xint() {
        int c = xchar(), x = 0, s = 1;
        while (c <= 32) {
            if(!~c) return ed = 1;
            c = xchar();
        }
        if (c == '-') s = -1, c = xchar();
        for (; '0' <= c && c <= '9'; c = xchar()) x = x * 10 + c - '0';
        return x * s;
    }
    inline int xuint() {
        int c = xchar(), x = 0;
        while (c <= 32) c = xchar();
        for (; '0' <= c && c <= '9'; c = xchar()) x = x * 10 + c - '0';
        return x;
    }
    inline void xstring(char *s) {
        int c = xchar();
        while (c <= 32) c = xchar();
        for (; c >  32; c = xchar()) *s++ = c;
        *s = 0;
    }
    inline void wchar(int x) {
        if (wpos == S) fwrite(wbuf, 1, S, stdout), wpos = 0;
        wbuf[wpos++] = x;
    }
    inline void wint(int x) {
        if (x < 0) wchar('-'), x = -x;
        char s[24];
        int n = 0;
        while (x || !n) s[n++] = '0' + x % 10, x /= 10;
        while (n--) wchar(s[n]);
    }
    inline void wstring(const char *s) {
        while (*s) wchar(*s++);
    }
    ~FastIO() {
        if (wpos) fwrite(wbuf, 1, wpos, stdout), wpos = 0;
    }
} io;

int n, m, a[N], sz[N], wson[N], f[N][2], h[N][2];
int to[N << 1], ne[N << 1], hd[N], _;

struct Mat {
    int a[2][2];
    inline Mat operator * (const Mat &c) const {
        Mat r;
        r.a[0][0] = max(a[0][0] + c.a[0][0], a[0][1] + c.a[1][0]);
        r.a[0][1] = max(a[0][0] + c.a[0][1], a[0][1] + c.a[1][1]);
        r.a[1][0] = max(a[1][0] + c.a[0][0], a[1][1] + c.a[1][0]);
        r.a[1][1] = max(a[1][0] + c.a[0][1], a[1][1] + c.a[1][1]);
        return r;
    }
};

inline void ae(int u, int v) { to[++_] = v, ne[_] = hd[u], hd[u] = _; }
inline int max(int u, int v) { return u > v ? u : v; }

void dfs(int u, int fa) {
    f[u][1] = a[u], sz[u] = 1;
    for(int i = hd[u]; i; i = ne[i]) if(to[i] != fa) {
        int v = to[i];
        dfs(v, u);
        f[u][0] += max(f[v][0], f[v][1]);
        f[u][1] += f[v][0];
        sz[u] += sz[v];
        if(sz[v] > sz[wson[u]]) wson[u] = v;
    }
    int s = wson[u];
    h[u][0] = f[u][0], h[u][1] = f[u][1];
    if(s) h[u][0] -= max(f[s][0], f[s][1]), h[u][1] -= f[s][0];
}

struct BST {
    Mat val[N], sum[N];
    int fa[N], son[N][2], rt, sta[N], top, n;
    bool isr[N];
    inline void up(int x) {
        sum[x] = val[x];
        if(son[x][0]) sum[x] = sum[son[x][0]] * sum[x];
        if(son[x][1]) sum[x] = sum[x] * sum[son[x][1]];
    }
    inline int sbuild(int l, int r) {
        if(l > r) return 0;
        int tot = 0, now = 0;
        rep(i, l, r + 1) tot += sz[sta[i]] - sz[wson[sta[i]]];
        rep(i, l, r + 1) {
            now += sz[sta[i]] - sz[wson[sta[i]]];
            if((now << 1) >= tot) {
                int x = sta[i];
                son[x][0] = sbuild(l, i - 1);
                son[x][1] = sbuild(i + 1, r);
                fa[son[x][0]] = fa[son[x][1]] = x;
                up(x);
                return x;
            }
        }
        return 0;
    }
    int build(int tp, int f) {
        for(int u = tp; u; f = u, u = wson[u]) {
            for(int i = hd[u]; i; i = ne[i]) if(to[i] != f && to[i] != wson[u]) {
                fa[build(to[i], u)] = u;
            }
            val[u].a[0][0] = val[u].a[0][1] = h[u][0];
            val[u].a[1][0] = h[u][1];
            val[u].a[1][1] = -inf;
        }
        top = 0;
        for(int u = tp; u; u = wson[u]) sta[++top] = u;
        return sbuild(1, top);
    }
    void build(int _n) {
        n = _n; rt = build(1, 0);
        rep(i, 1, n + 1) isr[i] = (son[fa[i]][0] != i && son[fa[i]][1] != i);
    }
    int upd(int x, int y) {
        h[x][1] += y - a[x], a[x] = y;
        val[x].a[1][0] = h[x][1];
        while(x) {
            if(isr[x] && fa[x]) {
                int of0 = max(sum[x].a[0][0], sum[x].a[0][1]);
                int of1 = max(sum[x].a[1][0], sum[x].a[1][1]);
                up(x);
                int nf0 = max(sum[x].a[0][0], sum[x].a[0][1]);
                int nf1 = max(sum[x].a[1][0], sum[x].a[1][1]);
                int u = fa[x];
                h[u][0] += max(nf0, nf1) - max(of0, of1);
                h[u][1] += nf0 - of0;
                val[u].a[0][0] = val[u].a[0][1] = h[u][0];
                val[u].a[1][0] = h[u][1];
            } else {
                up(x);
            }
            x = fa[x];
        }
        int ans = -inf;
        rep(i, 0, 2) rep(j, 0, 2) ans = max(ans, sum[rt].a[i][j]);
        return ans;
    }
}bst;

int main() {
    n = io.xint();
    m = io.xint();
    rep(i, 1, n + 1) a[i] = io.xint();
    rep(i, 1, n) {
        int u = io.xint();
        int v = io.xint();
        ae(u, v), ae(v, u);
    }
    dfs(1, 0);
    bst.build(n);
    int ans = 0;
    while(m--) {
        int x = io.xint() ^ ans;
        int y = io.xint();
        ans = bst.upd(x, y);
        io.wint(ans);
        io.wchar('\n');
    }
    return 0;
}

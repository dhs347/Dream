#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define rep(i, a, b) for(int i=(a); i<(b); i++)
#define per(i, a, b) for(int i=(b)-1; i>=(a); i--)
#define sz(a) (int)a.size()
#define de(a) cout << #a << " = " << a << endl
#define dd(a) cout << #a << " = " << a << " "
#define all(a) a.begin(), a.end()
#define pw(x) (1ll<<(x))
#define endl "\n"
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef double db;

const int N = 202020;

int n, m;
char s[N];
struct Node {
    int l, r, k, ans;
    void read() {
        cin >> l >> r >> k;
    }
    void print() {
        if(~ans) cout << ans - (r - l + 1) + 1 << endl;
        else cout << ans << endl;
    }
}nd[N];

int rt[N], cntn;
int ls[N * 20], rs[N * 20], cnt[N * 20];

void upd(int &rt, int p, int l = 1, int r = n) {
    rt = ++cntn;
    cnt[rt] = 1;
    if(l == r) return ;
    int mid = l + r >> 1;
    if(p <= mid) upd(ls[rt], p, l, mid);
    else upd(rs[rt], p, mid + 1, r);
}
int qry(int l, int r, int rt, int k) {
    if(k > cnt[rt] || !rt) return -1;
    if(l == r) return l;
    int mid = l + r >> 1;
    if(cnt[ls[rt]] >= k) return qry(l, mid, ls[rt], k);
    else return qry(mid + 1, r, rs[rt], k - cnt[ls[rt]]);
}
int merge(int x, int y) {
    if(x && y) {
        cnt[x] += cnt[y];
        ls[x] = merge(ls[x], ls[y]);
        rs[x] = merge(rs[x], rs[y]);
        return x;
    } else return x + y;
}


struct SAM {
    static const int N = ::N, M = 26;
    int par[N], l[N], ne[N][M], fa[N][20], to[N], rig[N], cnt[N], cur[N];
    int rt, last, L;
    vi vec[N];
    void add(int c) {
        int p = last, np = ++L;
        fill(ne[np], ne[np] + M, 0);
        l[np] = l[p] + 1;
        last = np;
        while(p && !ne[p][c]) ne[p][c] = np, p = par[p];
        if(!p) par[np] = rt;
        else{
            int q = ne[p][c];
            if(l[q] == l[p] + 1) par[np] = q;
            else {
                int nq = ++L;
                l[nq] = l[p] + 1;
                copy(ne[q], ne[q] + M, ne[nq]);
                par[nq] = par[q];
                par[q] = par[np] = nq;
                while(p && ne[p][c] == q) ne[p][c] = nq, p = par[p];
            }
        }
    }
    void ini() {
        memset(::rt, 0, sizeof(::rt));
        memset(ls, 0, sizeof(ls));
        memset(rs, 0, sizeof(ls));
        memset(::cnt, 0, sizeof(ls));
        memset(to, 0, sizeof(to));
        rep(i, 0, L + 1) vec[i].clear(), rig[i] = 0;
        rt = last = L = 1;
        fill(ne[rt], ne[rt] + M, 0);
        l[0] = -1;
    }
    int gao(Node nd) {
        int p = to[nd.r];
        per(i, 0, 20) {
            int np = fa[p][i];
            if(l[np] >= nd.r - nd.l + 1) p = np;
        }
//        dd(nd.r - nd.l + 1), dd(l[par[p]]), de(l[p]);
        return p;
    }
    void solve() {
        rep(i, 1, L + 1) fa[i][0] = par[i];
        rep(i, 1, 20) rep(j, 1, L + 1) fa[j][i] = fa[fa[j][i - 1]][i - 1];
        int p = rt;
        rep(i, 0, n) {
            int c = s[i] - 'a';
            p = to[i + 1] = ne[p][c];
            rig[p] = i + 1;
        }
        rep(i, 1, m + 1) vec[gao(nd[i])].pb(i);
        cntn = 0;
        rep(i, 1, L + 1) {
            if(rig[i]) {
                upd(::rt[i], rig[i], 1, n);
            } else {
                ::rt[i] = 0;
            }
        }
        
        rep(i, 0, L + 1) cnt[i] = 0;
        rep(i, 1, L + 1) ++cnt[l[i]];
        rep(i, 1, L + 1) cnt[i] += cnt[i - 1];
        rep(i, 1, L + 1) cur[cnt[l[i]]--] = i;
        per(i, 1, L + 1) {
            int u = cur[i];
            for(auto v : vec[u]) nd[v].ans = qry(1, n, ::rt[u], nd[v].k);
            int v = par[u];
            ::rt[v] = merge(::rt[v], ::rt[u]);
            rig[par[u]] = rig[u];
        }
        rep(i, 1, m + 1) nd[i].print();
    }
}sam; 

void solve() {
    sam.ini();
    cin >> n >> m >> s;
    rep(i, 1, m + 1) nd[i].read();
    rep(i, 0, n) sam.add(s[i] - 'a');
    sam.solve();
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
//    freopen("03.in", "r", stdin);
    int T; cin >> T;
    while(T--) solve();
//    cout << setiosflags(ios::fixed);
//    cout << setprecision(3);
    return 0;
}


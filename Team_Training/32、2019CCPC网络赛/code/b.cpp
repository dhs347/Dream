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

const int N = 101010;
int n, m, a[N], rt[N];

struct Seg2 {
    static const int N = ::N * 20;
    int L, sum[N], ls[N], rs[N];
    void init() {
        L = 0;
    }
    void upd(int p, int pre, int &now, int l = 1, int r = n) {
        now = ++L;
        sum[now] = sum[pre] + 1;
        ls[now] = ls[pre];
        rs[now] = rs[pre];
        if(l == r) return ;
        int mid = l + r >> 1;
        if(p <= mid) upd(p, ls[pre], ls[now], l, mid);
        else upd(p, rs[pre], rs[now], mid + 1, r);
    }
    int qry(int L, int R, int l, int r, int rt) {
        if(!rt) return -1;
        if(L <= l && r <= R && (l == r || sum[rt] == 0)) {
            if(sum[rt] == 0) return -1;
            return l;
        }
        int mid = l + r >> 1;
        if(L <= mid) {
            int t = qry(L, R, l, mid, ls[rt]);
            if(~t) return t;
        }
        if(R > mid) {
            int t = qry(L, R, mid + 1, r, rs[rt]);
            if(~t) return t;
        }
        return -1;
    }
}seg2;

struct Seg {
#define ls rt << 1
#define rs ls | 1
    static const int N = ::N << 2;
    int sum[N];
    void init() {
        fill_n(sum, n << 2 | 1, 0);
    }
    void upd(int p, int l = 1, int r = n, int rt = 1) {
        ++sum[rt];
        if(l == r) return ;
        int mid = l + r >> 1;
        if(p <= mid) upd(p, l, mid, ls);
        else upd(p, mid + 1, r, rs);
    }
    int qry(int L, int R, int l, int r, int rt) {
        if(L <= l && r <= R && (l == r || sum[rt] == 0)) {
            if(sum[rt] == 0) return -1;
            return l;
        }
        int mid = l + r >> 1;
        if(L <= mid) {
            int t = qry(L, R, l, mid, ls);
            if(~t) return t;
        }
        if(R > mid) {
            int t = qry(L, R, mid + 1, r, rs);
            if(~t) return t;
        }
        return -1;
    }
}seg;

void solve() {
    cin >> n >> m;
    seg.init();
    seg2.init();
    rep(i, 1, n + 1) cin >> a[i];
    rt[n + 1] = 0;
    per(i, 1, n + 1) seg2.upd(a[i], rt[i + 1], rt[i]);
    int ans = 0;
    while(m--) {
        int o, x, y;
        cin >> o >> x; x ^= ans;
        if(o == 1) {
            seg.upd(a[x]);
        } else {
            cin >> y; y ^= ans;
            ans = n + 1;
            int t1 = seg.qry(y, n, 1, n, 1);
            int t2 = seg2.qry(y, n, 1, n, rt[x + 1]);
            if(~t1) ans = min(ans, t1);
            if(~t2) ans = min(ans, t2);
            cout << ans << endl;
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int T; cin >> T;
    while(T--) solve(); 
//    cout << setiosflags(ios::fixed);
//    cout << setprecision(3);
    return 0;
}

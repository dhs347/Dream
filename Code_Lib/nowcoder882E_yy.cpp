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
 
const int N = 5e4 + 5, M = 11, P = 1e9 + 7;
 
int n, m, q;
string s[N];
 
inline int add(int a, int b) {
    if((a += b) >= P) a -= P;
    return a;
}
inline int mul(int a, int b) {
    return 1ll * a * b % P;
}
 
struct Mat {
    int a[M][M];
    Mat() { rep(i, 1, m + 1) rep(j, 1, m + 1) a[i][j] = 0; }
    void init(string s) {
        int pre[M] = {0};
        rep(i, 1, m + 1) pre[i] = pre[i - 1] + (s[i - 1] - '0');
        rep(i, 1, m + 1) rep(j, i, m + 1) a[i][j] = (pre[j] - pre[i - 1] == 0);
        rep(i, 1, m + 1) rep(j, 1, i) a[i][j] = a[j][i];
        /*
        rep(i, 1, m + 1) {
            rep(j, 1, m + 1) cout << a[i][j];
            cout << endl;
        }
        cout << endl;
        */
    }
    Mat operator * (const Mat &c) const {
        Mat r;
        rep(i, 1, m + 1) rep(j, 1, m + 1) rep(k, 1, m + 1) r.a[i][j] = add(r.a[i][j], mul(a[i][k], c.a[k][j]));
        return r;
    }
};
 
struct Seg {
#define ls rt << 1
#define rs ls | 1
    static const int N = ::N << 2;
    Mat nd[N];
    void build(int l, int r, int rt) {
        if(l == r) {
            nd[rt].init(s[l]);
            return ;
        }
        int mid = l + r >> 1;
        build(l, mid, ls);
        build(mid + 1, r, rs);
        nd[rt] = nd[rs] * nd[ls];
    }
    void upd(int p, int l, int r, int rt) {
        if(l == r) {
            nd[rt].init(s[l]);
            return ;
        }
        int mid = l + r >> 1;
        if(p <= mid) upd(p, l, mid, ls);
        else upd(p, mid + 1, r, rs);
        nd[rt] = nd[rs] * nd[ls];
    }
}seg;
 
void solve() {
    seg.build(1, n, 1);
    while(q--) {
        int o, x, y;
        cin >> o >> x >> y;
        if(o == 1) {
            --y;
            s[x][y] = '0' + ((s[x][y] - '0') ^ 1);
            seg.upd(x, 1, n, 1);
        } else {
            cout << seg.nd[1].a[y][x] << endl;
        }
    }
}
 
int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    cin >> n >> m >> q;
    rep(i, 1, n + 1) cin >> s[i];
    solve();
    return 0;
}

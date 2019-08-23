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

const int N = 50505;
int U;

int n, m, q, cnt, qq[N];
vector<pii> g[N];
ll up; bool o;
vector<ll> ans;

void dfs(int u, ll dis) {
    if(cnt >= U) return ;
    if(dis > 0) {
        ++cnt;
        if(o) ans.pb(dis);
    }
    for(auto v : g[u]) {
        if(dis + v.fi > up) break;
        dfs(v.se, dis + v.fi);
        if(cnt >= U) return ;
    }
}

bool check(ll mid) {
    up = mid; cnt = 0;
    dfs(0, 0);
    return cnt >= U;
}

void solve() {
    ans.clear(); o = 0;
    cin >> n >> m >> q;
    rep(i, 0, n + 1) g[i].clear();
    rep(i, 1, n + 1) g[0].pb(mp(0, i));
    rep(i, 1, m + 1) {
        int u, v, w; cin >> u >> v >> w;
        g[u].pb(mp(w, v));
    }
    U = 0;
    rep(i, 1, q + 1) cin >> qq[i], U = max(U, qq[i]);
    
    rep(i, 1, n + 1) sort(all(g[i]));
    ll l = 1, r = 5e13, ans = 0;
    while(l <= r) {
        ll mid = l + r >> 1;
        if(check(mid)) {
            ans = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    o = 1; check(ans - 1);
    sort(all(::ans));
    while(sz(::ans) < U) ::ans.pb(ans);
    rep(i, 1, q + 1) {
        int k = qq[i] - 1;
        cout << ::ans[k] << endl;
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
//    freopen("04.in", "r", stdin);
    int T; cin >> T;
    while(T--) solve();
//    cout << setiosflags(ios::fixed);
//    cout << setprecision(3);
    return 0;
}

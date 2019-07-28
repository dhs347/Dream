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
 
const int N = 303030;
 
int n, a[N];
int ls[N], rs[N], st[N], ed[N];
ll sum[N];
 
int ct(int a[], int n) {
    a[n] = INT_MAX;
    vi v(1, n);
    fill_n(ls, n, -1), fill_n(rs, n, -1);
    rep(i, 0, n) {
        while(a[v.back()] < a[i]) ls[i] = v.back(), v.pop_back();
        v.pb(rs[v.back()] = i);
    }
    return v[1];
}
 
void dfs(int u) {
    st[u] = ed[u] = u;
    if(ls[u]) dfs(ls[u]), st[u] = st[ls[u]];
    if(rs[u]) dfs(rs[u]), ed[u] = ed[rs[u]];
}
 
void solve() {
    cin >> n;
    rep(i, 1, n + 1) cin >> a[i], sum[i] = sum[i - 1] + a[i];
    int rt = ct(a + 1, n) + 1;
    rep(i, 0, n) ls[i]++, rs[i]++;
    per(i, 1, n + 1) ls[i] = ls[i - 1], rs[i] = rs[i - 1];
    dfs(rt);
    ll ans = 0;
    rep(i, 1, n + 1) {
        int p = i, q = i;
        while(q + 1 <= ed[i] && sum[q + 1] - sum[i - 1] < 2 * a[i]) ++q;
        while(p >= st[i] && sum[i] - sum[p - 1] < 2 * a[i]) {
            while(sum[q] - sum[p - 1] >= 2 * a[i]) --q;
            ans += q - i + 1;
            p--;
        }
    }
    cout << n * 1ll * (n - 1) / 2 + n - ans << endl;
}
 
int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    int T; cin >> T;
    while(T--) solve();
    return 0;
}

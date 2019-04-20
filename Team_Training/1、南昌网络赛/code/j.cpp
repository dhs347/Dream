#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define sz(a) (int)a.size()
#define de(a) cout << #a << " = " << a << endl
#define dd(a) cout << #a << " = " << a << " "
#define all(a) a.begin(), a.end()
#define pw(x) (1ll << (x))
#define endl "\n"
typedef long long ll;
typedef pair<int, int> pii;
typedef double db;
typedef vector<int> vi;

const int N = 101010;

int n, m;
vi G[N];
vector<pii> g[N];
int rt[N];
vi V;

int Find(int x) {
  return lower_bound(all(V), x) - V.begin() + 1;
}

struct Seg {
  static const int N = ::N * 22;
  int ls[N], rs[N], cnt[N];
  int cntn;
  void upd(int pre, int &now, int l, int r, int p) {
    now = ++cntn;
    ls[now] = ls[pre];
    rs[now] = rs[pre];
    cnt[now] = cnt[pre] + 1;
    if(l == r) return ;
    int mid = l + r >> 1;
    if(p <= mid) upd(ls[pre], ls[now], l, mid, p);
    else upd(rs[pre], rs[now], mid + 1, r, p);
  }
  int qry(int t1, int t2, int t3, int l, int r, int L, int R) {
    if(L > R) return 0;
    if(L <= l && r <= R) return cnt[t1] + cnt[t2] - 2 * cnt[t3];
    int mid = l + r >> 1, ans = 0;
    if(L <= mid) ans += qry(ls[t1], ls[t2], ls[t3], l, mid, L, R);
    if(R > mid) ans += qry(rs[t1], rs[t2], rs[t3], mid + 1, r, L, R);
    return ans;
  }
}seg;

struct LR {
  static const int N = ::N << 1, M = 20;
  int a[M][N], lft[N], dep[N], lg[N], L;
  int rmin(int x,int y) {
    return dep[x] < dep[y] ? x : y;
  }
  void add(int x) {
    a[0][L++] = x;
  }
  void dfs(int c, int fa, const vi g[]) {
    lft[c] = L; add(c);
    for(auto t : g[c]) if(t != fa) dep[t] = dep[c] + 1, dfs(t, c, g), add(c);
  }
  void build( const vi g[])  {
    L = 0; dfs(1, 0, g);
    rep(i, 2, L) lg[i] = lg[i >> 1] + 1;
    rep(i, 1, M) {
      int lim = L + 1 - (1 << i);
      rep(j, 0, lim) a[i][j] = rmin(a[i - 1][j], a[i - 1][j + (1 << i >> 1)]);
    }
  }
  int lca(int x, int y) {
    x = lft[x], y = lft[y];
    if(x > y) swap(x, y);
    int i = lg[y - x + 1];
    return rmin(a[i][x], a[i][y + 1 - (1 << i)]);
  }
}R;

void dfs(int u, int fa) {
  for(auto v : g[u]) if(v.fi != fa) {
    seg.upd(rt[u], rt[v.fi], 1, sz(V), Find(v.se));
    dfs(v.fi, u);
  }
}
void solve() {
  int u, v, k;
  cin >> u >> v >> k;
  int lc = R.lca(u, v);
 // dd(u), dd(v), dd(k), de(lc);
  int p = upper_bound(all(V), k) - V.begin();
  cout << seg.qry(rt[u], rt[v], rt[lc], 1, sz(V), 1, p) << endl;
}

int main() {
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);
  cin >> n >> m;
  rep(i, 1, n) {
    int u, v, w;
    cin >> u >> v >> w;
    g[u].pb(mp(v, w));
    g[v].pb(mp(u, w));
    G[u].pb(v);
    G[v].pb(u);
    V.pb(w);
  }
  R.build(G);
  sort(all(V));
  V.erase(unique(all(V)), V.end());
  dfs(1, 0);
  while(m--) {
    solve();
  }
  return 0;
}

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

int n, q;
vi G[N];
vector<pii> g[N];

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
    L = 0; dfs(1, 0, g); dep[0] = -1;
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
namespace CG {
  const int N = ::N, M = 20;
  int pre[N][M];
  db f[N][M];
  void dfs(int u, int fa) {
    for(auto v : g[u]) if(v.fi != fa) {
      pre[v.fi][0] = u;
      f[v.fi][0] = v.se / 100.;
      rep(i, 1, M) {
      	int t = pre[v.fi][i - 1];
      	pre[v.fi][i] = pre[t][i - 1];
      	f[v.fi][i] = f[v.fi][i - 1] * f[t][i - 1];
      }
      dfs(v.fi, u);
    }
  }
  db qry(int u, int v) {
    if(R.dep[u] > R.dep[v]) swap(u, v);
    db ans = 1;
//    dd(u), de(v);
    per(i, 0, M) if(R.dep[pre[v][i]] >= R.dep[u]) {
  //    dd(i), dd(v), dd(pre[v][i]), de(f[v][i]);
      ans *= f[v][i];
      v = pre[v][i];
    }
    return 1 - ans;
  }
}
bool cmp(int a, int b) {
  return R.lft[a] < R.lft[b];
}
namespace VTree {
  const int N = ::N;
  int tp[N], _;
  vi g[N];
  vector<db> pre[N], suf[N];
  int tim, vis[N][2];
  db f[N], f2[N], ans[N];
  void dfs(int u) {
    f[u] = 1;
    for(auto v : g[u]) {
      dfs(v);
      f[u] *= f[v] + (1 - f[v]) * CG::qry(u, v);
      pre[u].pb(f[u]);
    }
    db t = 1;
    per(i, 0, sz(g[u])) {
      int v = g[u][i];
      t *= f[v] + (1 - f[v]) * CG::qry(u, v);
      suf[u].pb(t);
    }
    if(vis[u][0] == tim) f[u] = 0;
    reverse(all(suf[u]));
  }
  void dfs2(int u) {
    rep(i, 0, sz(g[u])) {
      int v = g[u][i];
      db F = f2[u];
      if(i) F *= pre[u][i - 1];
      if(i < sz(g[u]) - 1) F *= suf[u][i + 1];
      if(vis[u][0] == tim) F = 0;
      f2[v] = F + (1 - F) * CG::qry(v, u);
      ans[v] = 1 - f2[v] * f[v];
      dfs2(v);
    }
  }
  void solve(LR &R) {
    vi a[2], v;
    int k[2];
    cin >> k[0] >> k[1];
    ++tim;
    rep(o, 0, 2) rep(i, 0, k[o]) {
      int x; cin >> x;
      a[o].pb(x);
      v.pb(x);
      vis[x][o] = tim;
    }
    v.pb(1);
    sort(all(v), cmp);
    v.erase(unique(all(v)), v.end());
    _ = 0;
    vi del; del.pb(tp[_++] = v[0]);
    rep(i, 1, sz(v)) {
      int lca = R.lca(tp[_ - 1], v[i]);
      vi l; while(_ > 0 && R.dep[lca] < R.dep[tp[_ - 1]]) l.pb(tp[--_]);
      if(_ == 0 || lca != tp[_ - 1]) del.pb(tp[_++] = lca);
      l.pb(tp[_ - 1]); del.pb(tp[_++] = v[i]);
      rep(i, 1, sz(l)) g[l[i]].pb(l[i - 1]);
    }
    rep(i, 0, _ - 1) g[tp[i]].pb(tp[i + 1]);
    dfs(1);
    f2[1] = 1;
    ans[1] = 1 - f[1] * f2[1];
    dfs2(1);
    rep(i, 0, k[1]) cout << ans[a[1][i]] << " \n"[i == k[1] - 1];
    for(auto t : del) {
      g[t].clear();
      pre[t].clear();
      suf[t].clear();
    }
  }
};

void solve() {
  cin >> n >> q;
  rep(i, 1, n + 1) g[i].clear(), G[i].clear();
  rep(i, 1, n) {
    int u, v, w;
    cin >> u >> v >> w;
    g[u].pb(mp(v, w));
    g[v].pb(mp(u, w));
    G[u].pb(v);
    G[v].pb(u);
  }
  R.build(G);
  CG::dfs(1, 0);
  while(q--) {
    VTree::solve(R);
  }
}

int main() {
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);
  cout << setiosflags(ios::fixed);
  cout << setprecision(7);
  int T;
  cin >> T;
  while(T--) solve();
  return 0;
}

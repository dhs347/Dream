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
namespace VTree {
  const int N = ::N;
  int tp[N], _;
  vi g[N];
  void solve(vi &v, LR &R) {
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
    for(auto t : del) {
      g[t].clear();
    }
  }
};

int main() {
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);
  return 0;
}

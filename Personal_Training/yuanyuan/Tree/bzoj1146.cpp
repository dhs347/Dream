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

const int N = 80000 + 1, M = 1e7;

int n, m, L, dfn;
int val[N], rt[N], cnt[M], ls[M], rs[M], st[N], ed[N], fw[N], par[N];
pair<int, pii> Q[N];
vi V;
vi res[2], g[N];

int F(int x) {
  return lower_bound(all(V), x) - V.begin() + 1;
}

// N is 2 size of tree , id of nodes start from 1
struct LCARMQ{
  static const int N = ::N << 1;
  int a[20][N] , lft[N] , dep[N] , lg[N] , L;
  int rmin(int x,int y){return dep[x] < dep[y] ? x : y;}
  void add(int x){ a[0][L++] = x;}
  void dfs(int c,int fa,const vi g[]){
    lft[c]=L;add(c);
    rep(i, 0, sz(g[c])) {
      int t = g[c][i];
      if(t!=fa) dep[t]=dep[c]+1,dfs(t,c,g),add(c);
    }
  }
  void Build(const vi g[]){
    L = 0;dfs(1,0,g);dep[0] = -1;
    rep(i,2,L) lg[i]=lg[i>>1]+1;
    rep(i,1,20){
      int lim = L+1-(1<<i);
      rep(j,0,lim) a[i][j] = rmin(a[i-1][j] , a[i-1][j+(1<<i>>1)]);
    }
  }
  int lca(int x,int y){
    x = lft[x] , y = lft[y];
    if(x > y) swap(x , y);
    int i = lg[y-x+1];
    return rmin(a[i][x] , a[i][y+1-(1<<i)]);
  }
}R;

void upd(int &now, int pre, int p, int c, int l, int r) {
  now = ++L;
  cnt[now] = cnt[pre] + c;
  ls[now] = ls[pre];
  rs[now] = rs[pre];
  if(l == r) return ;
  int mid = l + r >> 1;
  if(p <= mid) upd(ls[now], ls[pre], p, c, l, mid);
  else upd(rs[now], rs[pre], p, c, mid + 1, r);
}

int qry(int k, int l, int r) {
  if(l == r) return l;
  int mid = l + r >> 1;
  int cntr = 0;
  rep(i, 0, sz(res[0])) cntr += cnt[rs[res[0][i]]];
  rep(i, 0, sz(res[1])) cntr -= cnt[rs[res[1][i]]];
  if(cntr >= k) {
    rep(i, 0, sz(res[0])) res[0][i] = rs[res[0][i]];
    rep(i, 0, sz(res[1])) res[1][i] = rs[res[1][i]];
    return qry(k, mid + 1, r);
  } else {
    rep(i, 0, sz(res[0])) res[0][i] = ls[res[0][i]];
    rep(i, 0, sz(res[1])) res[1][i] = ls[res[1][i]];
    return qry(k - cntr, l, mid);
  }
}

#define lb(x) ((x) & -(x))
void upd(int p, int o, int c) {
  for( ; p <= n; p += lb(p)) upd(fw[p], fw[p], c, o, 1, sz(V));
}

void dfs(int u, int fa) {
  st[u] = ++dfn;
  par[u] = fa;
  upd(rt[u], rt[fa], F(val[u]), 1, 1, sz(V));
  rep(i, 0, sz(g[u])) if(g[u][i] != fa) dfs(g[u][i], u);
  ed[u] = dfn;
}

int tt = 0;

void upd(int u, int o) {
  res[o].pb(rt[u]);
  int p = st[u];
  for( ; p; p ^= lb(p)) res[o].pb(fw[p]);
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  cin >> n >> m;
  rep(i, 1, n + 1) cin >> val[i], V.pb(val[i]);
  rep(i, 1, n) {
    int u, v;
    cin >> u >> v;
    g[u].pb(v), g[v].pb(u);
  }
  rep(i, 1, m + 1) {
    cin >> Q[i].fi >> Q[i].se.fi >> Q[i].se.se;
    if(!Q[i].fi) V.pb(Q[i].se.se);
  }
  sort(all(V));
  V.erase(unique(all(V)), V.end());
  R.Build(g);
  dfs(1, 0);
  rep(i, 1, m + 1) {
    if(!Q[i].fi) {
      int p = Q[i].se.fi, c = Q[i].se.se;
      upd(st[p], -1, F(val[p]));
      upd(ed[p] + 1, 1, F(val[p]));
      val[p] = c;
      upd(st[p], 1, F(val[p]));
      upd(ed[p] + 1, -1, F(val[p]));
    } else {
      rep(o, 0, 2) res[o].clear();
      int a = Q[i].se.fi, b = Q[i].se.se, k = Q[i].fi;
      int c = R.lca(a, b), d = par[c];
      int tot = R.dep[a] + R.dep[b] - R.dep[c] - R.dep[d];
      upd(a, 0);
      upd(b, 0);
      upd(c, 1);
      upd(d, 1);
      if(tot < k) {
	cout << "invalid request!" << endl;
      } else {
	cout << V[qry(k, 1, sz(V)) - 1] << endl;
      }
    }
  }
  return 0;
}

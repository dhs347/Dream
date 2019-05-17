int n, m, L, dfn, val[N], rt[N], cnt[M], ls[M], rs[M], st[N], ed[N], fw[N], par[N];
pair<int, pii> Q[N]; vi V, res[2], g[N]; LCARMQ R;
int F(int x) { return lower_bound(all(V), x) - V.begin() + 1; }
// seg
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
// build 主席树
void dfs(int u, int fa) {
  st[u] = ++dfn;
  par[u] = fa;
  upd(rt[u], rt[fa], F(val[u]), 1, 1, sz(V));
  rep(i, 0, sz(g[u])) if(g[u][i] != fa) dfs(g[u][i], u);
  ed[u] = dfn;
}
// fenwick
void upd(int p, int o, int c) { for( ; p <= n; p += lb(p)) upd(fw[p], fw[p], c, o, 1, sz(V)); }
void upd(int u, int o) {
  res[o].pb(rt[u]);
  int p = st[u]; for( ; p; p ^= lb(p)) res[o].pb(fw[p]);
}
void solve() {
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
      upd(a, 0); upd(b, 0);
      upd(c, 1); upd(d, 1);
      cout << V[qry(k, 1, sz(V)) - 1] << endl;
    } } }

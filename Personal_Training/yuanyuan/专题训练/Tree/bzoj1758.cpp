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

int n, L, R;
db ans;
vector<pair<int, ll> > g[N];
vector<ll> vec[N];
vector<pii> dep;

// id starts from 1
bool vis[N];
int sz[N];
void dfssz(int c,int fa,int Sz,int &rt){
  sz[c] = 1;
  rep(i, 0, sz(g[c])) {
    int t = g[c][i].fi;
    if(!vis[t]&&t!=fa) dfssz(t,c,Sz,rt) , sz[c]+=sz[t];
  }
  if(!rt && sz[c]*2>Sz) rt=c;
}
void dfs(int u, ll w, int dep, int fa, vector<ll> &vec, int &ma) {
  if(dep > R) return ;
  if(sz(vec) < dep + 1) vec.resize(dep + 1);
  vec[dep] = max(vec[dep], w);
  ma = max(ma, dep);
  rep(i, 0, sz(g[u])) {
    int v = g[u][i].fi;
    if(v != fa && !vis[v]) dfs(v, w + g[u][i].se, dep + 1, u, vec, ma);
  }
}
bool check(db k) {
  vector<ll> V = vector<ll>(sz(vec[dep.back().se]));
  int n = 1;
  rep(o, 0, sz(dep)) {
    int u = dep[o].se;
    int m = sz(vec[u]);
    vector<pair<db, int> > q; int l = 0, r = 0;
    per(i, 0, m) {
      while(r <= R - i && r < n) {
      	db c = V[r] - k * r;
      	while(l < sz(q) && c >= q.back().fi) q.pop_back();
      	q.pb(mp(c, r));
      	++r;
      }
      while(l < sz(q) && q[l].se < L - i) ++l;
      if(l < sz(q) && q[l].fi + vec[u][i] - k * i >= 0) return 1;
    }
    rep(i, 0, m) {
      while(i >= sz(V));
      V[i] = max(V[i], vec[u][i]);
    }
    n = m;
  }
  return 0;
}
void dfs(int c){
  int rt=0;dfssz(c,0,0,rt);dfssz(c,0,sz[c],rt=0);
  vis[rt] = true;
  dep.clear();
  rep(i, 0, sz(g[rt])) {
    int v = g[rt][i].fi;
    if(!vis[v]) {
      int ma = 0;
      vec[v].clear();
      dfs(v, g[rt][i].se, 1, rt, vec[v], ma);
      dep.pb(mp(ma, v));
    }
  }
  if(!sz(dep)) return ;
  sort(all(dep));
  db l = 0, r = 2e6;
  rep(tim, 0, 50) {
    db mid = (l + r) / 2;
    if(check(mid)) {
      ans = max(ans, mid);
      l = mid;
    } else {
      r = mid;
    }
  }
  rep(i, 0, sz(g[rt])) {
    int t = g[rt][i].fi;
    if(!vis[t]) dfs(t);
  }
}

int main() {
  scanf("%d%d%d", &n, &L, &R);
  rep(i, 1, n) {
    int u, v, w;
    scanf("%d%d%d", &u, &v, &w);
    g[u].pb(mp(v, w));
    g[v].pb(mp(u, w));
  }
  dfs(1);
  printf("%.3f\n", ans);
  return 0;
}

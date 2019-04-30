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

const int N  = 50505;

int n;
int a[N], pre[N], st[N], ed[N], id[N];
pii b[N];
vi g[N], vec[N];

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
  int dis(int x, int y) {
    int z = lca(x, y);
    return dep[x] + dep[y] - 2 * dep[z];
  }
}R;

int find(int x) {
  return x == pre[x] ? x : pre[x] = find(pre[x]);
}
int join(int x, int y) {
  x = find(x);
  y = find(y);
  pre[y] = x;
  vi vec; 
  vec.pb(st[x]); 
  vec.pb(ed[x]); 
  vec.pb(st[y]); 
  vec.pb(ed[y]); 
  int a = vec[0], b = vec[1];
  rep(i, 0, 4) rep(j, i, 4) if(R.dis(vec[i], vec[j]) > R.dis(a, b)) a = vec[i], b = vec[j];
  st[x] = a, ed[x] = b;
  return R.dis(a, b);
}

int main() {
  //	cout << setiosflags(ios::fixed);
  //	cout << setprecision(3);
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  cin >> n;
  rep(i, 1, n + 1) cin >> a[i], b[i] = mp(a[i], i);
  sort(b + 1, b + 1 + n);
  reverse(b + 1, b + 1 + n);
  rep(i, 1, n + 1) id[b[i].se] = i;
  rep(i, 1, n) {
    int u, v;
    cin >> u >> v;
    g[u].pb(v), g[v].pb(u);
    if(id[u] > id[v]) swap(u, v);
    vec[v].pb(u);
  }
  R.Build(g);
  rep(i, 1, n + 1) pre[i] = st[i] = ed[i] = i;
  ll ans = 0;
  rep(_, 1, n + 1) {
    int u = b[_].se;
    rep(i, 0, sz(vec[u])) {
      int v = vec[u][i];
      int len = join(u, v) + 1;
      ans = max(ans, len * 1ll * a[u]);
    }
  }
  cout << ans << endl;
  return 0;
}

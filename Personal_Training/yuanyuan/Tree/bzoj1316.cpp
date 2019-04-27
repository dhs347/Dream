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

const int N = 10101, M = 1010101;

int n, m, tim;
int Q[N], Vis[M];
vi vec;
vector<pair<int, ll> > g[N];
bool ans[N];

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
void dfs(int u, ll w, int fa) {
  if(w < M) vec.pb(w);
  rep(i, 0, sz(g[u])) if(!vis[g[u][i].fi] && g[u][i].fi != fa) dfs(g[u][i].fi, w + g[u][i].se, u);
}
void dfs(int c){
  int rt=0;dfssz(c,0,0,rt);dfssz(c,0,sz[c],rt=0);
  vis[rt] = true;

  ++tim;
  Vis[0] = tim;
  rep(i, 0, sz(g[rt])) if(!vis[g[rt][i].fi]) {
    vec.clear();
    dfs(g[rt][i].fi, g[rt][i].se, rt);
    rep(j, 0, sz(vec)) rep(k, 1, m + 1) if(!ans[k] && Q[k] >= vec[j]) ans[k] = (Vis[Q[k] - vec[j]] == tim);
    rep(j, 0, sz(vec)) Vis[vec[j]] = tim;
  }
  /*
   * calc
   * 注意计算以 rt 为起点的路径、只包含 rt 的路径
   * 注意 v != vis[rt] 
   */
  rep(i, 0, sz(g[rt])) {
    int t = g[rt][i].fi;
    if(!vis[t]) dfs(t);
  }
}

int main() {
  //	cout << setiosflags(ios::fixed);
  //	cout << setprecision(3);
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  cin >> n >> m;
  rep(i, 1, n) {
    int u, v, w;
    cin >> u >> v >> w;
    g[u].pb(mp(v, w));
    g[v].pb(mp(u, w));
  }
  rep(i, 1, m + 1) cin >> Q[i];
  dfs(1);
  rep(i, 1, m + 1) {
    if(!Q[i]) ans[i] = 1;
    cout << (ans[i] ? "Yes" : "No") << endl;
  }
  return 0;
}

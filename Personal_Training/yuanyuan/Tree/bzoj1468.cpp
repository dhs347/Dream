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

const int N = 40404, M = 1010101;

int n, k;
ll ans;
vector<pair<int, ll> > g[N];

// id starts from 1
bool vis[N];
int sz[N];
vector<ll> vec, tot;

void dfssz(int c,int fa,int Sz,int &rt){
  sz[c] = 1;
  rep(i, 0, sz(g[c])) {
    int t = g[c][i].fi;
    if(!vis[t]&&t!=fa) dfssz(t,c,Sz,rt) , sz[c]+=sz[t];
  }
  if(!rt && sz[c]*2>Sz) rt=c;
}
void dfs(int u, ll w, int fa) {
  vec.pb(w);
  rep(i, 0, sz(g[u])) {
    int v = g[u][i].fi;
    if(!vis[v] && v != fa) dfs(v, w + g[u][i].se, u);
  }
}
ll calc(vector<ll> &vec) {
  sort(all(vec));
  ll ans = 0;
  int p = sz(vec) - 1;
  rep(i, 0, sz(vec)) {
    while(p >= i && vec[i] + vec[p] > k) --p;
    if(p < i) break;
    ans += p - i;
  }
  return ans;
}
void dfs(int c){
  int rt=0;dfssz(c,0,0,rt);dfssz(c,0,sz[c],rt=0);
  vis[rt] = true;
  tot = vector<ll>(1, 0);
  rep(i, 0, sz(g[rt])) if(!vis[g[rt][i].fi]) {
    vec.clear();
    dfs(g[rt][i].fi, g[rt][i].se, rt);
    ans -= calc(vec);
    tot.insert(tot.end(), all(vec));
  }
  ans += calc(tot);
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
  cin >> n;
  rep(i, 1, n) {
    int u, v, w;
    cin >> u >> v >> w;
    g[u].pb(mp(v, w));
    g[v].pb(mp(u, w));
  }
  cin >> k;
  dfs(1);
  cout << ans << endl;
  return 0;
}
// #include {{{
#include <iostream>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <cmath>
#include <ctime>
#include <queue>
#include <set>
#include <map>
#include <stack>
#include <string>
#include <bitset>
#include <vector>
#include <complex>
#include <algorithm>
using namespace std;
// }}}
// #define {{{
typedef long long ll;
typedef double db;
typedef pair<int,int> pii;
typedef vector<int> vi;
#define de(x) cout << #x << "=" << x << endl
#define rep(i,a,b) for(int i=a;i<(b);++i)
#define per(i,a,b) for(int i=(b)-1;i>=(a);--i)
#define all(x) (x).begin(),(x).end()
#define sz(x) (int)(x).size()
#define mp make_pair
#define pb push_back
#define fi first
#define se second
// }}}
 
const int N = 1e5 + 10;
int n , m , Q , u[N] , v[N] , x[N] , y[N] , z[N];
int fa[N] , sz[N];
int l[N] , r[N];
vi q[N];
 
int F(int x) {return fa[x] == x ? x : fa[x] = F(fa[x]);}
void merge(int u,int v) {
  u = F(u) , v = F(v);
  if(u != v) {
    if(sz[u] < sz[v]) swap(u , v);
    sz[u] += sz[v];
    fa[v] = u;
  }
}
 
int main(){
  cin >> n >> m;
  rep(i,1,m+1) cin >> u[i] >> v[i];
  cin >> Q;
  rep(i,0,Q) {
    cin >> x[i] >> y[i] >> z[i];
    l[i] = 0 , r[i] = m;
  }
  while(true) {
    bool unsolved = false;
    rep(i,0,m+1) q[i].clear();
    rep(i,0,Q) {
      if(l[i] + 1 == r[i])
        continue;
      unsolved = true;
      int mid = (l[i] + r[i]) >> 1;
      q[mid].pb(i);
    }
    if(!unsolved) break;
    rep(i,1,n+1) fa[i] = i , sz[i] = 1;
    rep(i,1,m+1) {
      merge(u[i] , v[i]);
      for(auto c : q[i]) {
        int cnt = 0;
        int x = F(::x[c]);
        int y = F(::y[c]);
        cnt = x == y ? sz[x] : sz[x] + sz[y];
        if(cnt >= z[c]) r[c] = i;
        else l[c] = i;
      }
    }
  }
  rep(i,0,Q) printf("%d\n",r[i]);
  return 0;
}

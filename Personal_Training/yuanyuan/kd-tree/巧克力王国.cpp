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

// init
typedef int T;// modify
namespace KDT {
  const int N = 1e6 + 7, D = 2;
  const T INF = 1e9 + 7;
  const db al = 0.75;

  int rt,L,top,W,sta[N];
  struct P{ T x[D]; ll val; bool operator < (const P &c) const { return x[W] < c.x[W]; } }p[N];
  struct Node{ T mi[D],ma[D]; int son[2],sz; ll ans; P val; }nd[N];

  void init() { rt = L = top = 0; }
  int newnode() { return top ? sta[top--] : ++L; }
  void up(int k) {
    rep(i, 0, D) {
      nd[k].mi[i]=nd[k].ma[i]=nd[k].val.x[i];
      rep(o, 0, 2) if(nd[k].son[o]) {
	int s = nd[k].son[o];
	nd[k].mi[i] = min(nd[k].mi[i], nd[s].mi[i]);
	nd[k].ma[i] = max(nd[k].ma[i], nd[s].ma[i]);
      }
    }
    nd[k].sz = 1; rep(i, 0, 2) nd[k].sz += nd[nd[k].son[i]].sz;
    nd[k].ans = nd[k].val.val;
    rep(i, 0, 2) nd[k].ans += nd[nd[k].son[i]].ans;
  }
  int build(int l,int r,int w) {
    if(l > r) return 0;
    int mid = l + r >> 1, k = newnode();
    W=w,nth_element(p+l,p+mid,p+r+1),nd[k].val=p[mid];
    nd[k].son[0] = build(l,mid-1, (w + 1) % D);
    nd[k].son[1] = build(mid+1,r, (w + 1) % D);
    up(k); return k;
  }
  void qry(P p, int u, ll &ans) {
    int o = 0;
    o += (nd[u].mi[0] * 1ll * p.x[0] + nd[u].mi[1] * 1ll * p.x[1] < p.val);
    o += (nd[u].mi[0] * 1ll * p.x[0] + nd[u].ma[1] * 1ll * p.x[1] < p.val);
    o += (nd[u].ma[0] * 1ll * p.x[0] + nd[u].mi[1] * 1ll * p.x[1] < p.val);
    o += (nd[u].ma[0] * 1ll * p.x[0] + nd[u].ma[1] * 1ll * p.x[1] < p.val);
    if(o == 0) return ;
    if(o == 4) { ans += nd[u].ans; return ; }
    if(nd[u].val.x[0] * 1ll * p.x[0] + nd[u].val.x[1] * 1ll * p.x[1] < p.val) ans += nd[u].val.val;
    rep(i, 0, 2) if(nd[u].son[i]) qry(p, nd[u].son[i], ans);
  }
}

int main() {
  //	cout << setiosflags(ios::fixed);
  //	cout << setprecision(3);
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  int n, m;
  cin >> n >> m;
  rep(i, 1, n + 1) {
    rep(j, 0, 2) cin >> KDT::p[i].x[j];
    cin >> KDT::p[i].val;
  }
  KDT::rt = KDT::build(1, n, 0);
  rep(i, 1, m + 1) {
    KDT::P p;
    rep(j, 0, 2) cin >> p.x[j]; cin >> p.val;
    ll ans = 0;
    KDT::qry(p, KDT::rt, ans);
    cout << ans << endl;
  }
  return 0;
}

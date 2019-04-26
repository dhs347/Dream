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

int k;
priority_queue<pair<ll, int> > ans;
const ll INF = pw(60);

// init
typedef int T;// modify
namespace KDT {
  const int N = 1e5 + 7, D = 2;
  const db al = 0.75;

  int rt,L,top,W,sta[N];
  struct P{ T x[D]; int ind; bool operator < (const P &c) const { return x[W] != c.x[W] ? x[W] < c.x[W] : x[!W] < c.x[!W]; } }p[N];
  struct Node{ T mi[D],ma[D]; int son[2],sz; P val; }nd[N];

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
  }
  int build(int l,int r,int w) {
    if(l > r) return 0;
    int mid = l + r >> 1, k = mid;
    W=w,nth_element(p+l,p+mid,p+r+1),nd[k].val=p[mid];
    nd[k].son[0] = build(l,mid-1, (w + 1) % D);
    nd[k].son[1] = build(mid+1,r, (w + 1) % D);
    up(k); return k;
  }
  ll sqr(int x) {
    return 1ll * x * x;
  }
  ll Dis(P p, int u) {
    ll dis = 0;
    rep(d, 0, D) dis += max(sqr(p.x[d] - nd[u].mi[d]), sqr(p.x[d] - nd[u].ma[d]));
    return dis;
  }
  void qry(P p, int u) {
    ll dis = 0;
    rep(d, 0, D) dis += sqr(p.x[d] - nd[u].val.x[d]);
    ll dl = nd[u].son[0] ? Dis(p, nd[u].son[0]) : -1;
    ll dr = nd[u].son[1] ? Dis(p, nd[u].son[1]) : -1;
    ans.push(mp(-dis, nd[u].val.ind));
    ans.pop();
    int ls = nd[u].son[0], rs = nd[u].son[1];
    if(dl > dr) swap(dl, dr), swap(ls, rs);
    if(dr >= -ans.top().fi) qry(p, rs);
    if(dl >= -ans.top().fi) qry(p, ls);
  }
}

int main() {
  //	cout << setiosflags(ios::fixed);
  //	cout << setprecision(3);
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  int n;
  cin >> n;
  rep(i, 1, n + 1) {
    rep(j, 0, 2) cin >> KDT::p[i].x[j];
    KDT::p[i].ind = i;
  }
  KDT::rt = KDT::build(1, n, 0);
  int m;
  cin >> m;
  rep(i, 1, m + 1) {
    KDT::P p;
    rep(j, 0, 2) cin >> p.x[j];
    cin >> k;
    while(!ans.empty()) ans.pop();
    rep(j, 0, k) ans.push(mp(0, n + 1));
    KDT::qry(p, KDT::rt);
    cout << ans.top().se << endl;
  }
  return 0;
}

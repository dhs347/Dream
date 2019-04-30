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

priority_queue<ll> ans;

// init
typedef int T;// modify
namespace KDT {
  const int N = 1e5 + 7, D = 2;
  const T INF = 1e9 + 7;
  const db al = 0.75;

  int rt,L,top,W,sta[N];
  struct P{ T x[D]; int ind; bool operator < (const P &c) const { return x[W] < c.x[W]; } }p[N];
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
    int mid = l + r >> 1, k = newnode();
    W=w,nth_element(p+l,p+mid,p+r+1),nd[k].val=p[mid];
    nd[k].son[0] = build(l,mid-1, (w + 1) % D);
    nd[k].son[1] = build(mid+1,r, (w + 1) % D);
    up(k); return k;
  }
  ll sqr(ll x) {
    return x * x;
  }
  ll Dis(P p, int u) {
    ll ans = 0;
    rep(d, 0, D) ans += max(sqr(nd[u].mi[d] - p.x[d]), sqr(nd[u].ma[d] - p.x[d]));
    return ans;
  }
  void qry(P p, int u) {
    ll dis = 0;
    rep(d, 0, D) dis += sqr(nd[u].val.x[d] - p.x[d]);
    if(nd[u].val.ind > p.ind)
      ans.push(-dis), ans.pop();
    int ls = nd[u].son[0], rs = nd[u].son[1];
    ll dl = ls ? Dis(p, ls) : -1;
    ll dr = rs ? Dis(p, rs) : -1;
    if(dl > dr) swap(dl, dr), swap(ls, rs);
    if(dr > -ans.top()) qry(p, rs);
    if(dl > -ans.top()) qry(p, ls);
  }
}

int main() {
  //	cout << setiosflags(ios::fixed);
  //	cout << setprecision(3);
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  int n, k;
  cin >> n >> k;// k <<= 1;
  rep(i, 1, n + 1) {
    rep(j, 0, 2) cin >> KDT::p[i].x[j];
    KDT::p[i].ind = i;
  }
  KDT::rt = KDT::build(1, n, 0);
  rep(i, 0, k) ans.push(1);
  rep(i, 1, n + 1) {
    KDT::qry(KDT::p[i], KDT::rt);
    /*
       cout << KDT::p[i].x[0] << " " << KDT::p[i].x[1] << endl;
       auto tt = ans;
       while(!tt.empty()) cout << -tt.top() << " ", tt.pop();
       cout << endl << endl;
     */
  }
  cout << -ans.top() << endl;
  return 0;
}

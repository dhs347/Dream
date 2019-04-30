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
  struct P{ T x[D]; bool operator < (const P &c) const { return x[W] < c.x[W]; } }p[N];
  struct Node{ T mi[D],ma[D]; int son[2],sz;P val; }nd[N];

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
  inline T dis(P p,int k,int o) {
    T re=0;
    for(int i=0;i<D;++i) {
      re+= o ? max(0,p.x[i]-nd[k].ma[i])+max(0,nd[k].mi[i]-p.x[i]) :
               max(0,p.x[i]-nd[k].mi[i])+max(0,nd[k].ma[i]-p.x[i]);
    }
    return re;
  }
  inline T dis(P a, P b) {
    T ans = 0; rep(i, 0, D) ans += abs(a.x[i] - b.x[i]);
    return ans;
  }
  void qry(P p, int u, int &ans, bool o) {
    int d = dis(p, nd[u].val);
    if(d) o ? ans = min(ans, d) : ans = max(ans, d);
    int ls = nd[u].son[0], rs = nd[u].son[1];
    int dl = ls ? dis(p, ls, o) : (o ? INF : -1);
    int dr = rs ? dis(p, rs, o) : (o ? INF : -1);
    if((o && dl > dr) || (!o && dl < dr)) swap(ls, rs), swap(dl, dr);
    if((o && ans > dl) || (!o && ans < dl)) qry(p, ls, ans, o);
    if((o && ans > dr) || (!o && ans < dr)) qry(p, rs, ans, o);
  }
}

int n;

int main() {
  //	cout << setiosflags(ios::fixed);
  //	cout << setprecision(3);
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  cin >> n;
  rep(i, 1, n + 1) rep(j, 0, 2) cin >> KDT::p[i].x[j];
  KDT::rt = KDT::build(1, n, 0);
  int ans = KDT::INF;
  rep(i, 1, n + 1) {
    int ma = 0, mi = KDT::INF;
    KDT::qry(KDT::p[i], KDT::rt, ma, 0);
    KDT::qry(KDT::p[i], KDT::rt, mi, 1);
    ans = min(ans, ma - mi);
  }
  cout << ans << endl;
  return 0;
}

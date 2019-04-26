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
  const int N = 1e5 + 7, D = 2;
  const T INF = 1e9 + 7;
  const db al = 0.75;

  int rt,L,top,W,sta[N];
  struct P{ T x[D]; bool operator < (const P &c) const { return x[W] < c.x[W]; } }p[N];
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
  void pia(int k,int &cnt) {
    if(nd[k].son[0]) pia(nd[k].son[0],cnt);
    p[++cnt]=nd[k].val,sta[++top]=k;
    if(nd[k].son[1]) pia(nd[k].son[1],cnt);
  }
  void check(int &k,int w) {
    bool o = 0;
    rep(i, 0, 2) if(al * nd[k].sz < nd[nd[k].son[i]].sz) o = 1;
    if(o) { int cnt = 0; pia(k,cnt),k = build(1,cnt,w); }
  }
  void ins(P p,int &k,int w) {
    if(!k) {k=newnode(),nd[k].val=p,nd[k].son[0]=nd[k].son[1]=0,up(k);return;}
    ins(p, nd[k].son[nd[k].val.x[w] < p.x[w]], (w + 1) % D);
    up(k),check(k,w);
  }
  void qry(P p, int k, int u, T &ans) {
    int ma = 0, mi = 0;
    rep(d, 0, D) {
      mi += max(0, nd[u].mi[d] - p.x[d]) + max(0, p.x[d] - nd[u].ma[d]);
      ma += max(0, nd[u].ma[d] - p.x[d]) + max(0, p.x[d] - nd[u].mi[d]);
    }
    if(mi > k) return ;
    if(ma <= k) {ans += nd[u].sz; return ;}
    if(abs(nd[u].val.x[0] - p.x[0]) + abs(nd[u].val.x[1] - p.x[1]) <= k) ++ans;
    rep(i, 0, 2) if(nd[u].son[i]) qry(p, k, nd[u].son[i], ans);
  }
}

const int N = 101010;

int a[N];

int main() {
  //	cout << setiosflags(ios::fixed);
  //	cout << setprecision(3);
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  int n, m;
  cin >> n >> m;
  rep(i, 1, n + 1) KDT::p[i].x[0] = i, cin >> a[i], KDT::p[i].x[1] = a[i];
  KDT::rt = KDT::build(1, n, 0);
  rep(i, 1, m + 1) {
    string o;
    int x, k;
    cin >> o >> x >> k;
    assert(x > 0);
    if(o[0] == 'M') {
      KDT::P p;
      p.x[0] = x; 
      p.x[1] = k;
      KDT::ins(p, KDT::rt, 0);
      a[x] = k;
    } else {
      KDT::P p;
      p.x[0] = x;
      p.x[1] = a[x];
      int ans = 0;
      KDT::qry(p, k, KDT::rt, ans);
      cout << ans << endl;
    }
  }
  return 0;
}

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
  const int N = 1e6 + 7, D = 3;
  const T INF = 1e9 + 7;
  const db al = 0.75;

  int rt,L,top,W,sta[N];
  struct P{ T x[D]; int val; bool operator < (const P &c) const { return x[W] < c.x[W]; } }p[N];
  struct Node{ T mi[D],ma[D]; int son[2],sz,mx; P val; }nd[N];

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
    nd[k].mx = nd[k].val.val;
    rep(i, 0, 2) nd[k].mx = max(nd[k].mx, nd[nd[k].son[i]].mx);
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
  void qry(int l, int r, int u, int &ans) {
    if(nd[u].mi[0] >= l || nd[u].ma[1] <= r || nd[u].mi[2] > r || nd[u].ma[2] < l || nd[u].mx < ans) return ;
    if(nd[u].ma[0] < l && nd[u].mi[1] > r && l <= nd[u].mi[2] && nd[u].ma[2] <= r) {
      ans = max(ans, nd[u].mx);
      return ;
    }
    if(nd[u].val.x[0] < l && nd[u].val.x[1] > r && l <= nd[u].val.x[2] && nd[u].val.x[2] <= r) ans = max(ans, nd[u].val.val);
    rep(i, 0, 2) if(nd[u].son[i]) qry(l, r, nd[u].son[i], ans);
  }
}

const int N = 101010;

int a[N], f[N], pre[N], ne[N];

int main() {
  //	cout << setiosflags(ios::fixed);
  //	cout << setprecision(3);
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  int n, m;
  cin >> n >> m;
  rep(i, 1, n + 1) cin >> a[i];
  rep(i, 1, n + 1) pre[i] = f[a[i]], f[a[i]] = i;
  rep(i, 1, n + 1) f[i] = n + 1;
  per(i, 1, n + 1) ne[i] = f[a[i]], f[a[i]] = i;
  rep(i, 1, n + 1) {
    KDT::p[i].x[0] = pre[i];
    KDT::p[i].x[1] = ne[i];
    KDT::p[i].x[2] = i;
    KDT::p[i].val = a[i];
  }
  KDT::rt = KDT::build(1, n, 0);
  int ans = 0;
  rep(i, 1, m + 1) {
    int l, r;
    cin >> l >> r;
    l = (l + ans) % n + 1;
    r = (r + ans) % n + 1;
    if(l > r) swap(l, r);
    ans = 0;
    KDT::qry(l, r, KDT::rt, ans);
    cout << ans << endl;
  }
  return 0;
}

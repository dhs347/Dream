#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define sz(a) (int)a.size()
#define de(a) cout << #a << " = " << a << endl
#define dd(a) cout << #a << " = " << a << " "
#define all(a) a.begin(), a.end()
#define pw(x) (1ll << (x))
#define endl "\n"
typedef long long ll;
typedef pair<int, int> pii;
typedef double db;
typedef vector<int> vi;

struct FastIO {
  static const int S = 1310720;
  int wpos;
  char wbuf[S];
  bool ed;
  FastIO() : wpos(0), ed(0) { }
  inline int xchar() {
    static char buf[S];
    static int len = 0, pos = 0;
    if (pos == len) pos = 0, len = fread(buf, 1, S, stdin);
    if (pos == len) return -1;
    return buf[pos++];
  }
  inline int xint() {
    int c = xchar(), x = 0, s = 1;
    while (c <= 32) {
      if(!~c) return ed = 1;
      c = xchar();
    }
    if (c == '-') s = -1, c = xchar();
    for (; '0' <= c && c <= '9'; c = xchar()) x = x * 10 + c - '0';
    return x * s;
  }
  inline int xuint() {
    int c = xchar(), x = 0;
    while (c <= 32) c = xchar();
    for (; '0' <= c && c <= '9'; c = xchar()) x = x * 10 + c - '0';
    return x;
  }
  inline void xstring(char *s) {
    int c = xchar();
    while (c <= 32) c = xchar();
    for (; c >  32; c = xchar()) *s++ = c;
    *s = 0;
  }
  inline void wchar(int x) {
    if (wpos == S) fwrite(wbuf, 1, S, stdout), wpos = 0;
    wbuf[wpos++] = x;
  }
  inline void wint(int x) {
    if (x < 0) wchar('-'), x = -x;
    char s[24];
    int n = 0;
    while (x || !n) s[n++] = '0' + x % 10, x /= 10;
    while (n--) wchar(s[n]);
  }
  inline void wstring(const char *s) {
    while (*s) wchar(*s++);
  }
  ~FastIO() {
    if (wpos) fwrite(wbuf, 1, wpos, stdout), wpos = 0;
  }
} io;

int n, m;

typedef int T;
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
    nd[k].sz = 1;
    rep(i, 0, 2) nd[k].sz += nd[nd[k].son[i]].sz;
  }
  int build(int l,int r,int w) {
    if(l > r) return 0;
    int mid = l + r >> 1, k = newnode();
    W=w,nth_element(p+l,p+mid,p+r+1),nd[k].val=p[mid];
    nd[k].son[0] = build(l,mid-1, (w + 1) % D);
    nd[k].son[1] = build(mid+1,r, (w + 1) % D);
    up(k);
    return k;
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
  T dis(P p,int k) {
    T re=0;
    for(int i=0;i<D;++i) re+=max(0,p.x[i]-nd[k].ma[i])+max(0,nd[k].mi[i]-p.x[i]);
    return re;
  }
  T dis(P a, P b) {
    T ans = 0;
    rep(i, 0, D) ans += abs(a.x[i] - b.x[i]);
    return ans;
  }
  void qry(P p, int k, T &ans) {
    ans=min(ans,dis(p,nd[k].val));
    int ls = nd[k].son[0], rs = nd[k].son[1];
    T dl = ls ? dis(p, ls) : INF;
    T dr = rs ? dis(p, rs) : INF;
    if(dl > dr) swap(dl, dr), swap(ls, rs);
    if(dl<ans) qry(p,ls,ans);
    if(dr<ans) qry(p,rs,ans);
  }
  void solve() {
    n = io.xint();
    m = io.xint();
    for(int i=1;i<=n;++i) rep(j, 0, D) p[i].x[j] = io.xint();
    rt = build(1,n,0);
    while(m--) {
      int o;
      P p;
      o = io.xint();
      rep(i, 0, D) p.x[i] = io.xint();
      if(o==1) ins(p,rt,0);
      else {
	int ans=INF;
	qry(p,rt,ans);
	io.wint(ans);
	io.wchar('\n');
      }
    }
  }
}
int main() {
  KDT::solve();
  return 0;
}

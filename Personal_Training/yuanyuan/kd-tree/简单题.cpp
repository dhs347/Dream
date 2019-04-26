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

typedef int T;
namespace KDT {
  const int N = 2e5 + 7, D = 2;
  const T INF = 1e9 + 7;
  const db al = 0.75;

  int rt,L,top,W,sta[N];
  struct P{ T x[D], val; bool operator < (const P &c) const { return x[W] < c.x[W]; } }p[N];
  struct Node{ T mi[D],ma[D], ans; int son[2],sz;P val; }nd[N];

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
    nd[k].ans = nd[k].val.val;
    rep(i, 0, 2) {
      nd[k].sz += nd[nd[k].son[i]].sz;
      nd[k].ans += nd[nd[k].son[i]].ans;
    }
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
  T dis(P p,int k) {
    T re=0;
    for(int i=0;i<D;++i) re+=max(0,p.x[i]-nd[k].ma[i])+max(0,nd[k].mi[i]-p.x[i]);
    return re;
  }
  T dis(P a, P b) {
    T ans = 0; rep(i, 0, D) ans += abs(a.x[i] - b.x[i]);
    return ans;
  }
  int qry(int l[], int r[], int u) {
    if(!u) return 0;
    bool o = 1, ok = 1;
    rep(d, 0, D) {
      if(nd[u].ma[d] < l[d] || r[d] < nd[u].mi[d]) return 0;
      if(nd[u].val.x[d] < l[d] || r[d] < nd[u].val.x[d]) ok = 0;
      if(!(l[d] <= nd[u].mi[d] && nd[u].ma[d] <= r[d])) o = 0;
    }
    if(o) return nd[u].ans; 
    int ans = ok ? nd[u].val.val : 0;
    rep(i, 0, 2) if(nd[u].son[i]) ans += qry(l, r, nd[u].son[i]);
    return ans;
  }
}

int n;

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

int main() {
  n = io.xint();
  int ans = 0, o;
  while(o = io.xint(), 1) {
    if(o == 1) {
      int x, y, c;
      x = io.xint();
      y = io.xint();
      c = io.xint();
      x ^= ans;
      y ^= ans;
      c ^= ans;
      KDT::P p;
      p.x[0] = x; p.x[1] = y; p.val = c;
      KDT::ins(p, KDT::rt, 0);
    } else if(o == 2) {
      int l[2], r[2];
      l[0] = io.xint();
      l[1] = io.xint();
      r[0] = io.xint();
      r[1] = io.xint();
      rep(i, 0, 2) l[i] ^= ans, r[i] ^= ans, (l[i] > r[i]) && (swap(l[i], r[i]), 0);
      ans = KDT::qry(l, r, KDT::rt);
      io.wint(ans);
      io.wchar('\n');
    } else {
      return 0;
    }
  }
  return 0;
}

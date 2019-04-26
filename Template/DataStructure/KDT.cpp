// init
typedef int T;// modify
namespace KDT {
  const int N = 1e6 + 7, D = 2;
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
  // 抄上面这部分就好了，下面部分是视具体题目定的
  // 最近点
  T dis(P p,int k) {
    T ans = 0; rep(i, 0, D) ans += max(0, p.x[i] - nd[k].ma[i]) + max(0, nd[k].mi[i] - p.x[i]); // modify
    return ans;
  }
  T dis(P a, P b) {
    T ans = 0; rep(i, 0, D) ans += abs(a.x[i] - b.x[i]);
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
  // 矩形区域的最大值（伪代码）
  void qry(int u, int &ans) {
    if(no_in || ma < ans) return ;
    if(all_in) { ans = max(ans, ma); return ; }
    if(u_in) ans = max(ans, u_val);
    rep(i, 0, 2) if(nd[u].son[i]) qry(nd[u].son[i], ans);
  }
  // 距离点 u 第 k 远
  priority_queue<ll> ans;
  void init() {
    while(!ans.empty()) ans.pop();
    rep(i, 0, k) ans.push(1);
  }
  ll sqr(int x) { return 1ll * x * x; }
  ll Dis(P p, int u) {
    ll ans = 0; rep(d, 0, D) ans += max(sqr(nd[u].mi[d] - p.x[d]), sqr(nd[u].ma[d] - p.x[d]));
    return ans;
  }
  void qry(P p, int u) {
    ll dis = 0; rep(d, 0, D) dis += sqr(nd[u].val.x[d] - p.x[d]);
    ans.push(-dis), ans.pop();
    int ls = nd[u].son[0], rs = nd[u].son[1];
    ll dl = ls ? Dis(p, ls) : -1;
    ll dr = rs ? Dis(p, rs) : -1;
    if(dl > dr) swap(dl, dr), swap(ls, rs);
    if(dr > -ans.top()) qry(p, rs);
    if(dl > -ans.top()) qry(p, ls);
  }
}

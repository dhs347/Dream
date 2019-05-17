struct UFS{
    int n,tot,cnt,Now,pos,val,add,T[N],ls[N],rs[N],h[N],d[N],Time[N];//tot鑺傜偣鎬绘暟,cnt鐘舵€佹€绘暟,now 褰撳墠鏃跺埢
    inline void U(int x,int p,int q) { ls[x]=p,rs[x]=q; }
    inline void Push(int yes,int cnt) { if (yes) Time[++Now]=cnt; }
    inline void G(int &t) { if (!t) t=cnt; }
    int B(int l,int r) {
        int rt=++tot; if (l==r) { h[rt]=l; return rt; }
        int mid=(l+r)>>1; U(rt,B(l,mid),B(mid+1,r)); return rt;
    }
    int update(int t,int l,int r,int *a) {
        int rt=++tot; if (l==r) { h[rt]=h[t],d[rt]=d[t],a[rt]=a[rt]*val+add; return rt;}
        int mid=(l+r)>>1; if (pos<=mid) U(rt,update(ls[t],l,mid,a),rs[t]);
            else U(rt,ls[t],update(rs[t],mid+1,r,a)); return rt;
    }
    int query(int t,int l,int r) {
        if (l==r) return t; int mid=(l+r)>>1;
        return (pos<=mid)?query(ls[t],l,mid):query(rs[t],mid+1,r);
    }
    int _find(int x,int t) { pos=x; int p=query(t,1,n); return (x==h[p])?p:_find(h[p],t); }
    int Query(int x,int t=0,int yes=0) { G(t); Push(yes,cnt); return h[_find(x,T[t])]; } //yes琛ㄧず鏄惁浜х敓鏃跺埢鎺ㄨ繘
    bool is_H(int x,int y,int yes=0,int t=0) { G(t); Push(yes,cnt); return Query(x,t)==Query(y,t); }
    void Union(int x,int y,int yes=1) {
        ++cnt; Push(yes,cnt); T[cnt]=T[cnt-1];
        int p=_find(x,T[cnt]),q=_find(y,T[cnt]);
        if (h[p]==h[q]) return;
        if (d[p]>d[q]) swap(p,q);
        pos=h[p],val=0,add=h[q],T[cnt]=update(T[cnt],1,n,h);
        if (d[p]==d[q])  pos=h[q],val=1,add=1,T[cnt]=update(T[cnt],1,n,d);
    }
    void Back(int t,int yes=1) { ++cnt; Push(yes,cnt); T[cnt]=T[Time[t]]; }
    void Init(int _n) { n=_n; tot=cnt=Now=0; mem(d,0); T[0]=B(1,n); }
};

// 普通集合线性基
const int M=63;
struct LB{
    ll a[M];
    void Clear() { memset(a,0,sizeof(a)); }
    void ins(ll x){
        for(int i=M-1; ~i && x; --i) if (x>>i&1)
            if (a[i]) x^=a[i]; else { a[i]=x; break; }
    }
};


// 可持久化线性基 ( 序列前缀最右线性基 ) 
const int M=32;
struct LB{
    ll a[M]; int id[M];
    void Clear() { memset(a,0,sizeof(a)); }
    void Copy(const LB&L) {
        rep(i,0,M) a[i]=L.a[i],id[i]=L.id[i];
    }
    void Ins(LB &L,ll x,int no) {
        Copy(L);
        for (int i=M-1; ~i && x; --i)
            if (x>>i&1) {
                if (!a[i]) a[i]=x,id[i]=no; else
                    if (no>id[i]) swap(a[i],x),swap(id[i],no);
                x^=a[i];
            }
    }
    ll Qry(int l,ll x=0) {
        per(i,0,M) if (id[i]>=l) x=max(x,x^a[i]); return x;
    }
} B[N];


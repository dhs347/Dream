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

// 集合线性基求交与查询
const int M=33;
ll tmp[M];
struct LB{
    ll a[M]; 
    LB() { mem(a,0); }
    void Clear() { mem(a,0); }
    void Copy(LB &A) { rep(i,0,M) a[i]=A.a[i]; }
	// 向 this 中插入 x ， 返回 y 在后来插入元素中的投影
    bool I(ll x,ll &y) {
        y=x;
        for(int i=M-1; ~i && x; --i) if (x>>i&1)
            if (a[i]) x^=a[i],y^=tmp[i]; else { a[i]=x,tmp[i]=y; return 1; }
        return 0;
    }
    bool Q(ll x) {
        for(int i=M-1; ~i && x; --i) if (x>>i&1)
            if (a[i]) x^=a[i]; else return 0;
        return 1;
    }
    friend void Intersect(LB &A,LB &B,LB &C) {
        LB AA; ll y,z; AA.Copy(A),C.Clear(); mem(tmp,0);
        per(i,0,M) if (B.a[i]) if (!AA.I(B.a[i],y)) C.I(y,z);
    }
	// 化为最简型 ，方便线性空间的 hash
    void build () {
        per(i,0,M) per(j,0,i) a[i]=min(a[i],a[i]^a[j]);
    }
    void print() { debug_arr(a,M-1); }
};

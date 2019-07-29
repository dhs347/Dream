const int M=63;
struct LB{
    ll a[M];
    void Clear() { memset(a,0,sizeof(a)); }
    void ins(ll x){
        for(int i=M-1; ~i && x; --i) if (x>>i&1)
            if (a[i]) x^=a[i]; else { a[i]=x; break; }
    }
};

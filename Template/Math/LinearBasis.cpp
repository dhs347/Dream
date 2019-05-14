struct Base{
    ll a[63];
    Base() {memset(a,0,sizeof(a));}
    void ins(ll x){
        for(int i=62;~i;--i) {
            if(x>>i&1) {
                if(a[i]) x^=a[i];
                else{ a[i]=x; break; }
            }
        }
    }
};

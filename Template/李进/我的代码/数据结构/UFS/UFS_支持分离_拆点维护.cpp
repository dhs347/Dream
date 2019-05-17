struct UFS{
    int n,h[N],cnt[N],p,q; ll s[N],temp[2];
    void Init(int _n){
        n=_n; mem(cnt,0); mem(s,0);
        rep(i,1,n) h[i]=h[i+n]=i+n,cnt[i+n]=1,s[i+n]=i;
    }
    int _find(int x) { return (h[x]==x)?x:h[x]=_find(h[x]); }
    bool is_H(int x,int y) { p=_find(x),q=_find(y); return p==q;}
    void Union(int x,int y) { if (!is_H(x,y)) h[p]=q,cnt[q]+=cnt[p],s[q]+=s[p]; }
    void Move(int x,int y){ if (!is_H(x,y)) h[x]=q,++cnt[q],--cnt[p],s[q]+=x,s[p]-=x; }
    ll* Query(int x) { p=_find(x); temp[0]=cnt[p],temp[1]=s[p]; return temp; }
};

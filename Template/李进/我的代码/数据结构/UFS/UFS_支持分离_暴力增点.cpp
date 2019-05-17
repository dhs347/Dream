struct UFS{
    int n,h[N],cnt[N],id[N],p,q,tot; ll s[N],temp[2];
    void Init(int _n){
        n=tot=_n; mem(cnt,0); mem(s,0);
        rep(i,1,n) h[i]=id[i]=i,cnt[i]=1,s[i]=i;
    }
    int _find(int x) { return (h[x]==x)?x:h[x]=_find(h[x]); }
    bool is_H(int x,int y) { p=_find(id[x]),q=_find(id[y]); return p==q;}
    void Union(int x,int y) { if (!is_H(x,y)) h[p]=q,cnt[q]+=cnt[p],s[q]+=s[p]; }
    void Move(int x,int y){ if (!is_H(x,y)) h[id[x]=++tot]=q,++cnt[q],--cnt[p],s[q]+=x,s[p]-=x; }
    ll* Query(int x) { p=_find(id[x]); temp[0]=cnt[p],temp[1]=s[p]; return temp; }
};

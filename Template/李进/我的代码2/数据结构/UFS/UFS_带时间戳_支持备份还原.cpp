struct UFS{
    int h[2][N],t[N],n,T,p,q,l,r; pii D[N]; 
    inline void Init(int _n) { n=_n; rep(i,1,n) h[0][i]=i; mem(t,-1); T=0; l=0,r=-1; }
    inline void Clear() { ++T; l=0,r=-1; }
    inline void Store() { while (l<=r) U(D[l].fir,D[l].sec,0),++l; ++T; }
    inline int& G(int x,int k=1) { if (k&&t[x]!=T) h[1][x]=h[0][x],t[x]=T; return h[k][x]; }
    int Q(int x,int k=1) { return x==G(x,k) ? x : G(x,k)=Q(G(x,k),k); }
    inline bool U(int x,int y,int k=1) {
        p=Q(x,k),q=Q(y,k); if (p==q) return 0;
        if (k) D[++r]=mp(x,y); G(p,k)=q; T+=(k^1); return 1;
    }
};

struct Trie_Tu{
	static const int M=26; int go[N][M],pre[N],num[N],toop[N],dep[N],cnt,str_cnt,S,t,l,r,f,T; int vis[N]; ll sum[N],ans;
	inline int h(int c) { return c-'a'; }
	inline int new_node(int d=0) { ++cnt,pre[cnt]=num[cnt]=vis[cnt]=sum[cnt]=0,mem(go[cnt],0); dep[cnt]=d; return cnt; }
	inline void Init() { str_cnt=cnt=0; S=T=new_node(); rep(i,0,M-1) go[0][i]=S; } 
	inline ll trip(int p,int op=0) { if (p==S || vis[p]==T) return sum[p]; ll t=trip(pre[p],op)+num[p]; vis[p]=T,sum[p]=(!op)*t; return t; }
    inline void Go(int &p,int c,int f=1) { int &t=go[p][c]; p=t?t:t=new_node(dep[p]+1); if (f) ans+=trip(p,1); else /**/; }
    inline int Run(const char s[],int _n=0,int op=0,int f=1) {
        if (!_n) _n=strlen(s); int pos=S,p=op*(_n-1),q=(op?-1:_n); op=1-2*op,T+=f; ans=0;
        for (int i=p; i!=q; i+=op) Go(pos,h(s[i]),f); return pos;
    }
    inline void Insert(const char s[],int _n=0,int op=0) { str_cnt++,num[t=Run(s,_n,op,0)]++; /*...*/ }
    inline void Build() {
    	for (toop[l=r=1]=S; l<=r && (f=toop[l++]); )
    		rep(i,0,M-1) if (!go[f][i]) go[f][i]=go[pre[f]][i]; else
    			pre[t=go[f][i]]=go[pre[f]][i], t!=S ? toop[++r]=t : 0;
	}
	inline ll Q() { return ans; }
};

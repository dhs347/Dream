struct Trie_Tu{
	static const int M=26; int go[N][M],pre[N],toop[N],dep[N],temp[N],str_id[N],cnt,str_cnt,S,t,l,r,f,T; ll sum[N]; 
	inline int h(int c) { return c-'a'; }
	inline int new_node(int d=0) { ++cnt,pre[cnt]=0,mem(go[cnt],0); dep[cnt]=d; sum[cnt]=0; return cnt; }
	inline void Init() { str_cnt=cnt=0; S=new_node(); rep(i,0,M-1) go[0][i]=S; } 
    inline void Go(int &p,int c,int f=1) { int &t=go[p][c]; p=t?t:t=new_node(dep[p]+1); if (f) sum[p]++; else /**/; }
    inline int Run(const char s[],int _n=0,int op=0,int f=1) {
        if (!_n) _n=strlen(s); int pos=S,p=op*(_n-1),q=(op?-1:_n); op=1-2*op,T+=f; if (f) mem(sum,0);
        for (int i=p; i!=q; i+=op) Go(pos,h(s[i]),f); if (f) Count(); return pos;
    }
    inline void Insert(const char s[],int _n=0,int op=0) { str_cnt++,str_id[str_cnt]=t=Run(s,_n,op,0); /*...*/ }
    inline void Build() {
    	for (toop[l=r=1]=S; l<=r && (f=toop[l++]); )
    		rep(i,0,M-1) if (!go[f][i]) go[f][i]=go[pre[f]][i]; else
    			pre[t=go[f][i]]=go[pre[f]][i], t!=S ? toop[++r]=t : 0; Toop();
	}
	inline void Toop() {
        rep(i,0,cnt) temp[i]=0; rep(i,1,cnt) temp[dep[i]]++;
        rep(i,1,cnt) temp[i]+=temp[i-1]; per(i,cnt,1) toop[temp[dep[i]]--]=i;
    }
    inline void Merge(int x,int y) { sum[x]+=sum[y]; }
    inline void Count() { per(i,cnt,1) Merge(pre[toop[i]],toop[i]); }
	inline ll Q(int k) { return sum[str_id[k]]; }
};

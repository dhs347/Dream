struct SAM {
    int go[N<<1][M],pre[N<<1],step[N<<1],rr[N<<1],temp[N<<1],toop[N<<1],cnt,S,T,n,p,q,nq; static int M=26;
	inline int h(int c) { return c-'a'; }
    inline int new_node(int _s,int c) { step[++cnt]=_s,pre[cnt]=0,rr[cnt]=c; mem(go[cnt],0); return cnt; }
	inline void Clear() { n=cnt=0,S=T=new_node(0,0); }
	inline void I(int c) {
		++n,c=h(c),p=T,T=new_node(step[T]+1,c);
        for (; p && !go[p][c]; p=pre[p]) go[p][c]=T;
        if (!p) pre[T] = S; else {
            q=go[p][c];
            if (step[p]+1==step[q]) pre[T]=q; else {
                nq=new_node(step[p]+1,c);
                rep(j,0,M-1) go[nq][j] = go[q][j];
				for (; p && go[p][c] == q; p = pre[p]) go[p][c] = nq;
                pre[nq]=pre[q],pre[T]=pre[q]=nq;
            }
        }//...
	}
	inline void Insert(char s[],int _n=0,int op=0) {
		if (!_n) _n=strlen(s); 
		if (!op) rep(i,0,_n-1) I(s[i]); else per(i,_n-1,0) I(s[i]);
	}
    inline void Toop() {
        rep(i,0,n) temp[i]=0; rep(i,1,cnt) temp[step[i]]++;
        rep(i,1,n) temp[i]+=temp[i-1]; rep(i,1,cnt) toop[temp[step[i]]--]=i;
    }
    inline int Q() { Toop(); return 0; }//...
};

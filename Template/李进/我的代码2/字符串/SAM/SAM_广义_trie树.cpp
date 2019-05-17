struct SAM {
    static const int M=26; int go[N<<1][M],pre[N<<1],step[N<<1],rr[N<<1],temp[N<<1],toop[N<<1],num[N<<1],dep[N<<1],cnt,S,n,p,q,nq; ll dp[N<<1],ans=0;
	inline int h(int c) { return c-'a'; }
    inline int new_node(int _s,int c) { step[++cnt]=_s,pre[cnt]=num[cnt]=0,rr[cnt]=c; /* */mem(go[cnt],0); return cnt; }
	inline void Init() { n=cnt=0,S=new_node(0,0); }
	inline int I(int T,int c) {
		if (go[T][c=h(c)] && step[go[T][c]]==step[T]+1) return go[T][c];
		++n,p=T,T=new_node(step[T]+1,c);
        for (; p && !go[p][c]; p=pre[p]) go[p][c]=T;
        if (!p) pre[T] = S; else {
            q=go[p][c];
            if (step[p]+1==step[q]) pre[T]=q; else {
                nq=new_node(step[p]+1,c);
                rep(j,0,M-1) go[nq][j] = go[q][j];
				for (; p && go[p][c] == q; p = pre[p]) go[p][c] = nq;
                pre[nq]=pre[q],pre[T]=pre[q]=nq;
            }
        }
		num[T]++; return T; //...
	}
    inline void Go(int &p,int c) { while (p && !go[p][c]) p=pre[p]; if (p) p=go[p][c],ans+=dp[p]; }
    inline int Run(const char s[],int _n=0,int op=0) {
        if (!_n) _n=strlen(s); int pos=S,p=op*(_n-1),q=(op?-1:_n); op=1-2*op; ans=0;
        for (int i=p; i!=q; i+=op) if (pos) Go(pos,h(s[i])); else break; return pos;
    }
    inline int get_dep(int x) { return (!x || dep[x]) ? dep[x] : dep[x]=get_dep(pre[x])+1; }
    inline void Toop() {
        rep(i,0,n) temp[i]=0; rep(i,1,cnt) temp[get_dep(i)]++;
        rep(i,1,n) temp[i]+=temp[i-1]; per(i,cnt,1) toop[temp[dep[i]]--]=i;
    }
    inline void Count() { per(i,cnt,1) num[pre[toop[i]]]+=num[toop[i]]; }
    inline ll Q() {
		/* Toop(); Count(); */ll ans=0; rep(i,1,cnt) ans+=step[i]-step[pre[i]]; return ans; //...
	}
};

const int _N=1e5+5,_M=1e5+5;
struct Tu{
	int head[_N],nxt[_M*2],e[_M*2],id[_N],n,tot; ll v[_N],w[_M*2]; SAM M;
	inline void Init(int _n) { n=_n,mem(head,0),tot=0; M.Clear(); id[0]=M.S; }
	inline void I(int x,int y,ll _w=0) { e[++tot]=y,w[tot]=_w; nxt[tot]=head[x],head[x]=tot; }
	void dfs(int x,int f){
		id[x]=M.I(id[f],v[x]);
		for (int i=head[x]; i; i=nxt[i]) if (e[i]!=f) dfs(e[i],x);
	}
	inline void Q() { /* */ }
};

//此版本注意：N=2*M*V(结点数)

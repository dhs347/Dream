template <class V>
struct Seg_T{
	int rt[N],ls[N*22],rs[N*22],cnt,L,R,pos,m; V v[N*22],x;
	void Init(int _m) { v[cnt=0]=0; mem(rt,0); m=_m; }
	void push_up(int t) { v[t]=v[ls[t]]+v[rs[t]]; }
	int new_node(int p=0,int q=0,V x=0) { ls[++cnt]=p,rs[cnt]=q,v[cnt]=x; return cnt; }
	void U(int &t,int l,int r) {
		if (!t) t=new_node();
		if (l==r) { v[t]=x; return; }
		int mid=(l+r)>>1;
		if (pos<=mid) U(ls[t],l,mid); else U(rs[t],mid+1,r);
		push_up(t); 
	}
	int M(int a,int b,int l){
		if (!a || !b) return a+b;
		int c=new_node(M(ls[a],ls[b],l-(l>>1)),M(rs[a],rs[b],l>>1),v[a]+v[b]);
		if (l==1) v[c]=max(v[a],v[b]);
		if (ls[c] || rs[c]) push_up(c); return c;
	} 
	V Q(int t,int l,int r) {
		if (!t) return 0;
		if (L<=l && r<=R) return v[t];
		int mid=(l+r)>>1; V ans=0;
		if (L<=mid) ans+=Q(ls[t],l,mid);
		if (R>mid) ans+=Q(rs[t],mid+1,r);
		return ans;
	}
	void Update(int &t,int _pos,V _x) { pos=_pos,x=_x,U(t,1,m); }
	int Query(int &t,int l,int r) { L=l,R=r; return Q(t,1,m); }
}; 

struct SAM {
    static const int M=26; ll dp[N<<1],ans; Seg_T<ll> SS;
    int go[N<<1][M],pre[N<<1],step[N<<1],rr[N<<1],temp[N<<1],toop[N<<1],id[N<<1],dep[N<<1],str_cnt,cnt,S,T,n,p,q,nq;
    inline int h(int c) { return c-'a'; }
    inline int new_node(int _s,int c) { step[++cnt]=_s,pre[cnt]=dep[cnt]=0,rr[cnt]=c; /* */mem(go[cnt],0); return cnt; }
    inline void Init(int _k) { n=cnt=str_cnt=0,S=T=new_node(0,0); SS.Init(_k); }
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
        }
        id[n]=T; SS.Update(SS.rt[T],str_cnt,1); //...
    }
    inline void Insert(const char s[],int _n=0,int op=0) {
        if (!_n) _n=strlen(s); ++str_cnt; T=S;
        if (!op) rep(i,0,_n-1) I(s[i]); else per(i,_n-1,0) I(s[i]);
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
    inline void Merge(int x,int y) { SS.rt[x]=SS.M(SS.rt[x],SS.rt[y],str_cnt); }
    inline void Count() { per(i,cnt,1) Merge(pre[toop[i]],toop[i]); }
    inline void Q() { 
        Toop(),Count(); rep(i,1,cnt) if (SS.Query(SS.rt[i],1,str_cnt)>=k) dp[i]=step[i]-step[pre[i]]; else dp[i]=0;
        rep(i,1,cnt) dp[toop[i]]+=dp[pre[toop[i]]]; rep(i,1,str_cnt) Run(st[i].c_str()),printf("%lld ",ans);
    }//...
};

//可参见合并版本线段树模板说明


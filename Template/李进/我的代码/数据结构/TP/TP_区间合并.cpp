struct TP{
	int l[N],r[N],ans[N][3],len[N],n,cnt; ll ans0;
	inline void Init(int _n) {
		cnt=n=_n; ans0=0; rep(i,0,n) l[i]=i-1,r[i]=i+1,len[i]=1; l[0]=n,r[n]=0;
	}
	inline void M(int x,int y) { len[x]+=len[y]; } //...
	inline void C(int x,int op) {  } //...
	inline void D(int x) {
		C(l[x],-1); C(x,-1); M(l[x],x); C(l[x],1);
		r[l[x]]=r[x]; l[r[x]]=l[x]; --cnt;
	}
}; 

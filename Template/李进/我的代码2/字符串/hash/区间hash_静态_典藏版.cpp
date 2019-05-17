struct STR{
	ll _B[N],h[N],base,_p;
	inline void init_h(char st[],int n,ll _base=163,ll __p=1e9+7,char c='a'){
		base=_base,_p=__p,h[0]=st[0]-c;
		rep(i,1,n-1) h[i]=(h[i-1]*base+st[i]-c)%_p;
		if (_B[0]==1) return; _B[0]=1;
		rep(i,1,N-1) _B[i]=_B[i-1]*base %_p;
	}
	inline ll H(int l,int r) {
		if (!l) return h[r]<0 ? h[r]+_p : h[r];
		ll ans=(h[r]-h[l-1]*_B[r-l+1])%_p;
		return ans<0 ? ans+_p:ans;
	}
};

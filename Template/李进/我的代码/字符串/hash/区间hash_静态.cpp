ll _B[N],base=163,pp=1e9+7;

inline void init_h(char st[],int n,ll h[]){
	h[0]=st[0]-'a';//去掉pp就是自动溢出
	rep(i,1,n-1) h[i]=(h[i-1]*base+st[i]-'a')%pp;
	if (_B[0]==1) return; _B[0]=1;
	rep(i,1,N-1) _B[i]=_B[i-1]*base %pp;
}

inline ll H(int l,int r,ll h[]) {
	if (!l) return h[r]<0 ? h[r]+pp : h[r];
	ll ans=(h[r]-h[l-1]*_B[r-l+1])%pp;
	return ans<0 ? ans+pp:ans;
}

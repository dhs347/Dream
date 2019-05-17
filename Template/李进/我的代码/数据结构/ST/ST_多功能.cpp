struct ST{
	int n,log[N]; ll dp[25][N];
	ll h(ll x,ll y) { return max(x,y); }
	void Init(int _n,ll *a){
		n=_n,log[0]=-1; rep(i,1,n) log[i]=log[i>>1]+1,dp[0][i]=a[i];
		rep(i,1,log[n]) rep(j,1,n+1-(1<<i)) dp[i][j]=h(dp[i-1][j],dp[i-1][j+(1<<(i-1))]);
	}
	ll Q(int l,int r) { int L=log[r-l+1]; return h(dp[L][l],dp[L][r+1-(1<<L)]); }
}; 

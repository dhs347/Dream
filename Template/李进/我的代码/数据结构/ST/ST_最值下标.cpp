struct ST{
	int n,log[N],dp[25][N]; ll *a;
	int h(int x,int y) { return a[x]>=a[y] ? x:y; }
	void Init(int _n,ll *_a){
		n=_n,a=_a,log[0]=-1; rep(i,1,n) log[i]=log[i>>1]+1,dp[0][i]=i;
		rep(i,1,log[n]) rep(j,1,n+1-(1<<i)) dp[i][j]=h(dp[i-1][j],dp[i-1][j+(1<<(i-1))]);
	}
	int Q(int l,int r) { int L=log[r-l+1]; return h(dp[L][l],dp[L][r+1-(1<<L)]); }
}; 

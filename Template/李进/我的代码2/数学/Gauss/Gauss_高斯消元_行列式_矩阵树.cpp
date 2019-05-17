const int _N=105;
struct Gauss{
	ll mod,a[_N][_N],mp[_N][_N],ans[_N],inv,n; int t;
	inline void Init(int _n,ll _p) { mod=_p,n=_n; }
	inline ll Pow(ll x,ll k){
		ll ans=1; for (;k;k>>=1,(x*=x)%=mod) if (k&1) (ans*=x)%=mod; return ans;
	}
	inline int Solve(int n,int op=1) {
		ll res=ans[0]=1;
		rep(i,1,n) {
			for (t=i;t<=n;++t) if (a[t][i]) break;
			if (t>n) break;
			if (t!=i) {
				res=-res;
				rep(j,1,n+op) swap(a[i][j],a[t][j]);
			}
			inv=Pow(a[i][i],mod-2);
			rep(j,(1-op)*i+1,n) {
				if (j==i) continue;
				int t=a[j][i]*inv%mod;
				rep(k,1,n+op) a[j][k]=(a[j][k]-t*a[i][k]%mod+mod)%mod;
			}
		}
		rep(i,1,n) if (op==1) ans[i]=a[i][n+1]*Pow(a[i][i],mod-2)%mod; else (ans[0]*=a[i][i])%=mod;
		return res;
	}
	inline ll Matrix_Tree(ll x=1,int op=0){
		mem(a,0);
		rep(i,1,n) rep(j,1,n) {
			if (i==j) continue;
			a[i][j]=mod-mp[i][j]*x-op,a[i][i]+=mod-a[i][j];
		}
		ll ans0=Solve(n-1,0)*ans[0]; return (ans0+mod)%mod;
	}
}; 

//说明：Solve(n,op),op=1是解方程组ans[1..n],op=0是求行列式值ans[0],返回值表示行列式的符号res; Solve(n-1,0)*ans[0]表示n-1阶主子式绝对值
//Matrix_Tree(x,op),原图覆盖x次,op=1意思是覆盖一层完全图

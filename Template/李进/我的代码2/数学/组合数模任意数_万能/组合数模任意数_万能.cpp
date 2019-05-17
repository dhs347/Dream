const int _N=100105;

struct Euler{
	int c[_N][62],a[62],tot; ll phi,y,p,fac[_N],inv[_N];
	inline ll quick_mod(ll x,ll k) {
		ll ans=1; for (; k; k>>=1,(x*=x)%=p) if (k&1) (ans*=x)%=p;
		return ans;
	}
	inline void init(ll _p){
		p=phi=y=_p,tot=0; mem(c,0); fac[0]=inv[0]=1;
		for (ll i=2; i*i<=y; i++) {
			if (y%i) continue;
			a[++tot]=i;
			while (y%i==0) y/=i;
		}
		if (y>1) a[++tot]=y;
		rep(i,1,tot) phi=phi/a[i]*(a[i]-1);
		for (int i=1; (y=i)<_N ; i++) {
			rep(j,1,tot) {
				c[i][j]=c[i-1][j];
				while (y%a[j]==0) c[i][j]++,y/=a[j];
			}
			fac[i]=fac[i-1]*y%p;
			inv[i]=quick_mod(fac[i],phi-1);
		}
	}
	inline ll C(int n,int m) {
		if (n<m) return 0; if (!m || n==m) return 1;
		ll ans=fac[n]*inv[m]%p*inv[n-m]%p;
		rep(i,1,tot) (ans*=quick_mod(a[i],c[n][i]-c[m][i]-c[n-m][i]))%=p;
		return ans;
	}
	inline ll solve(){
		//...
	}
};

//说明：求C(n,m)%p, n,m<=10^6, p<=10^9且为任意数    fac[i]为i!与p互质的成分,c[i][j]为i!中a[j]的指数

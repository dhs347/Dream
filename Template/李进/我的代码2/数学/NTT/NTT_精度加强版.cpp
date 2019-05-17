ll p,g; //p为大费马质数,q为原根
inline ll mul(ll a,ll b){ return a*b-(ll)((long double)a*b/p)*p; }
inline ll Pow(ll a,ll b){
	ll res=1;
	for (;b;b>>=1,a=mul(a,a)) if (b&1) res=mul(res,a);
	return res;
}

struct FT{
	int rev[N],len; ll w[2][N],W[2][N],F[N],G[N]; 
	inline void Init(int n){
		for (len=1;len<2*n;len<<=1);len<<=1;
		ll lcm=1ll*n*len/gcd(n,len);
		p=lcm+1;
		while (p<100000) p+=lcm;
		for (;;p+=lcm){
			int chk=1;
			for (int j=2;(ll)j*j<=p&&chk;j++) if (p%j==0) chk=0;
			if (chk) break;
		}
		for (g=2;;g++){
			int chk=1;
			for (int j=2;1ll*j*j<=p-1&&chk;j++)
				if ((p-1)%j==0){
					if (Pow(g,j)==1) chk=0; else
					if (Pow(g,(p-1)/j)==1) chk=0;
				}
			if (chk) break;
		}
	}
	void preFFT(int n){
		ll w0=Pow(g,(p-1)/n); int m;
		w[0][0]=w[1][0]=1;
		rep(i,1,n-1) w[0][i]=mul(w[0][i-1],w0);
		rep(i,1,n-1) w[1][i]=w[0][n-i];
		for (m=0;(1<<m)!=n;m++);
		rev[0]=0;
		rep(i,1,n-1) rev[i]=(rev[i>>1]>>1)|(i&1)<<m-1;
	}
	void FFT(ll *A,int n,int op){
		rep(i,0,n-1) if (i<rev[i]) swap(A[i],A[rev[i]]);
		for (int i=1;i<n;i<<=1)
			for (int j=0,t=n/(i<<1);j<n;j+=i<<1)
				for (int k=j,l=0;k<j+i;k++,l+=t){
					ll x=A[k],y=mul(w[op][l],A[k+i]);
					A[k]=(x+y>=p?x+y-p:x+y);
					A[k+i]=(x-y+p>=p?x-y:x-y+p);
				}
		if (op){
			ll tmp=Pow(n,p-2);
			rep(i,0,n-1) A[i]=mul(A[i],tmp);
		}
	}
	void preDFT(int n,int op){
		ll w0=Pow(g,(p-1)/n);
		W[0][0]=W[1][0]=1;
		rep(i,1,n-1) W[0][i]=mul(W[0][i-1],w0);
		rep(i,1,n-1) W[1][i]=W[0][n-i];
		rep(i,0,2*n-1) G[2*n-1-i]=W[op][1ll*i*(i-1)/2%n];
		rep(i,2*n,len-1) G[i]=0;
		for (len=1;len<2*n;len<<=1);len<<=1;
		preFFT(len);
		FFT(G,len,0);
	}
	void DFT(ll *A,int n,int op){
		rep(i,0,n-1) F[i]=mul(A[i],W[op][(n-1ll*i*(i-1)/2%n)%n]);
		rep(i,n,len-1) F[i]=0;
		FFT(F,len,0);
		rep(i,0,len-1) F[i]=mul(F[i],G[i]);
		FFT(F,len,1);
		rep(i,0,n-1) A[i]=mul(F[2*n-1-i],W[op][(n-1ll*i*(i-1)/2%n)%n]);
		if (op){
			ll tmp=Pow(n,p-2);
			rep(i,0,n-1) A[i]=mul(A[i],tmp);
		}
	}
	inline void solve(ll a[],ll b[],ll c[],int n,int op) { //op=0,mul; op=1,div
		preDFT(n,0),DFT(a,n,0),DFT(b,n,0);
		rep(i,0,n-1) c[i]=op?mul(a[i],Pow(b[i],p-2)):mul(a[i],b[i]);
		preDFT(n,1),DFT(c,n,1);
	}
}; 

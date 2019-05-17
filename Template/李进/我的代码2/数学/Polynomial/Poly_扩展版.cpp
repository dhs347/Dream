const int _N=200005; ll inv[_N<<2],fac[_N<<2],fac_inv[_N<<2];
inline ll add(ll x,ll y) { x+=y; return x%_p; }
inline ll mul(ll x,ll y) { return (ll)x*y%_p; }
inline ll Pow(ll x,ll k) { ll ans=1; for (;k;k>>=1,x=x*x%_p) if (k&1) (ans*=x)%=_p; return ans; } 
inline void init_inv(int n) { inv[1]=1; rep(i,2,n) inv[i]=mul(_p-_p/i,inv[_p%i]); }
inline void init_fac(int n) { 
	fac[0]=fac_inv[0]=1; 
	rep(i,1,n) fac[i]=mul(fac[i-1],i),fac_inv[i]=mul(fac_inv[i-1],inv[i]); 
}

template <class V>
struct FT{
	int n,nn; V w[2][_N<<2],rev[_N<<2],tmp;
	inline int init_len(int _n) { for (n=1; n<=_n; n<<=1); return n; }
	inline int Init(int _n) {
		init_len(_n); if (n==nn) return n; nn=n;
		V w0=Pow(3,(_p-1)/n); w[0][0]=w[1][0]=1;
		rep(i,1,n-1) w[0][i]=w[1][n-i]=mul(w[0][i-1],w0);
		rep(i,0,n-1) rev[i]=(rev[i>>1]>>1)|((i&1)*(n>>1)); return n;
	}
	void FFT(V A[],int op){
		rep(i,0,n-1) if (i<rev[i]) swap(A[i],A[rev[i]]);
		for (int i=1; i<n; i<<=1)
			for (int j=0,t=n/(i<<1); j<n; j+=i<<1)
				for (int k=j,l=0; k<j+i; k++,l+=t) {
					V x=A[k],y=mul(w[op][l],A[k+i]);
					A[k]=add(x,y),A[k+i]=add(x-y,_p);
				}
		if (op) { tmp=inv[n]; rep(i,0,n-1) A[i]=mul(A[i],tmp); }
	}
};

template <class V>
struct Calculator{
	FT<V> T; V X[_N<<2],Y[_N<<2],A[_N<<2],B[_N<<2],C[_N<<2];
	inline void Fill(V a[],V b[],int n,int len) {
		if (a!=b) memcpy(a,b,sizeof(V)*n); fill(a+n,a+len,0);
	}
	inline void Add(V a[],int n,V b[],int m,V c[],int t=1) {
		n=max(n,m); rep(i,0,n-1) c[i]=add(a[i],t*b[i]);
	}
	inline void Dot_Mul(V a[],V b[],int len,V c[]) {
		rep(i,0,len-1) c[i]=mul(a[i],b[i]);
	}
	inline void Dot_Mul(V a[],int len,V v,V c[]) {
		rep(i,0,len-1) c[i]=mul(a[i],v);
	}
	inline void Mul(V a[],int n,V b[],int m,V c[]) {
		int len=T.Init(n+m-1); Fill(X,a,n,len),Fill(Y,b,m,len);
		T.FFT(X,0),T.FFT(Y,0),Dot_Mul(X,Y,len,c),T.FFT(c,1);
	}
	inline void Int(V a[],int n,V b[]) {
		per(i,n-1,0) b[i+1]=mul(a[i],inv[i+1]); b[0]=0;
	}
	inline void Der(V a[],int n,V b[]) {
		rep(i,1,n-1) b[i-1]=mul(a[i],i); b[n-1]=0;
	}
	inline void Inv(V a[],int n,V b[]) {
		if (n==1) { b[0]=Pow(a[0],_p-2),b[1]=0; return; }
		Inv(a,(n+1)>>1,b); int len=T.Init(2*n-1);
		Fill(X,a,n,len),Fill(b,b,n,len),T.FFT(X,0),T.FFT(b,0);
		rep(i,0,len-1) b[i]=mul(b[i],2-mul(b[i],X[i]));
		T.FFT(b,1),Fill(b,b,n,len);
	}
	inline void Log(V a[],int n,V b[]) {
		static V A[_N<<2],B[_N<<2]; 
		Der(a,n,A),Inv(a,n,B),Mul(A,n,B,n,b);
		Int(b,n,b),Fill(b,b,n,T.n);
	}
	inline void Exp(V a[],int n,V b[]) {
		if (n==1) { b[0]=exp(a[0]),b[1]=0; return; }
		Exp(a,(n+1)>>1,A),Log(A,n,B),Add(a,n,B,n,B,-1);
		(B[0]+=1)%=_p,Mul(A,n,B,n,b),Fill(b,b,n,T.n);
	}
	inline void Sqrt(V a[],int n,V b[]) {
		if (n==1) { b[0]=sqrt(a[0]),b[1]=0; return; }
		Sqrt(a,(n+1)>>1,b),Inv(b,n,B),Mul(a,n,B,n,B);
		Add(b,n,B,n,b),Dot_Mul(b,n,inv[2],b),Fill(b,b,n,T.n);
	}
	inline void Power(V a[],int n,ll k,V b[]) {
		Log(a,n,C),Dot_Mul(C,n,k,C),Exp(C,n,b),Fill(b,b,n,T.n);
	}
	inline V Lagrange(V a[],int n,int k) {
		Inv(a,n,A),Power(A,n,k,B); return mul(B[k-1],inv[k]);
	}
	inline void Div(V a[],int n,V b[],int m,V d[],V r[]) {
		int len=T.init_len(2*n-1); Fill(A,a,n,len),Fill(B,b,m,len);
		reverse(A,A+n),reverse(B,B+m),Inv(B,n-m+1,Y);
		Mul(A,n,Y,n,d),Fill(d,d,n-m+1,len),reverse(d,d+n-m+1);
		reverse(B,B+m),Fill(A,d,n-m+1,len);
		Mul(A,n,B,n,r),Add(a,n,r,n,r,-1),Fill(r,r,n,len);
	}
	inline void Sinh(V a[],int n,V b[]) {
		Exp(a,n,b); for (int i=0; i<n; i+=2) b[i]=0;
	}
	inline void Cosh(V a[],int n,V b[]) {
		Exp(a,n,b); for (int i=1; i<n; i+=2) b[i]=0;
	}
	inline void Dirichlet_Mul(V a[],int n,V b[],int m,V c[],int L) {
		int len=min((ll)n*m,L); Fill(c,c,0,L+1);
		rep(i,1,n) for (int j=1; j<=m && (ll)i*j<=len; j++) 
			c[i*j]=add(c[i*i],mul(a[i],b[j]));
	}
	inline void Der_k(V a[],int n,int k,V b[]) {
		Der(a,n,b); rep(i,1,k-1) Der(b,n,b);
	}
	inline void Int_k(V a[],int n,int k,V b[]) {
		Int(a,n,b); rep(i,1,k-1) Int(b,n,b);
	}
	inline void Grow(V a[],int n,V b[]) {
		rep(i,0,n-1) b[i]=mul(a[i],i);
	}
	inline void Grow_k(V a[],int n,int k,V b[]) {
		rep(i,0,n-1) b[i]=mul(a[i],Pow(i,k));
	}
	inline void Shl(V a[],int n,int k,V b[]) {
		rep(i,k,n-1) b[i-k]=a[i]; Fill(b,b,n-k,n);
	}
	inline void Shr(V a[],int n,int k,V b[]) {
		per(i,n-1,k) b[i]=a[i-k]; Fill(b,b,0,k);
	}
	inline void To_egf(V a[],int n,V b[]) { Dot_Mul(a,fac,n,b); }
	inline void To_ogf(V a[],int n,V b[]) { Dot_Mul(a,fac_inv,n,b); }
	inline void Bin_Mul(V a[],int n,V b[],int m,V c[]) {
		static V A[_N<<2],B[_N<<2];
		To_ogf(a,n,A),To_ogf(b,m,B),Mul(A,n,B,m,c),To_egf(c,T.n,c);
	}
	inline void POW(V a[],int n,ll k,V b[],int t=0) {
		if (k*t>=n || !k) { Fill(b,b,0,n),b[0]=!k; return; }
		if (t) Shl(a,n,t,a); Power(a,n-t,k,b),Shr(b,n,k*t,b);
	}
	inline void Reverse(V a[],int n,V b[]) { reverse_copy(a,a+n,b); }
	inline void Init_Com_Num_H_B(V a[],int n,ll k) {
		a[0]=1; rep(i,1,n-1) a[i]=mul(a[i-1],inv[i]*(k-i+1)%_p);
	}
	inline void Init_Com_Num_L_B(V a[],int n,ll k) {
		a[0]=1; rep(i,1,n-1) a[i]=mul(a[i-1],inv[i]*(k+i)%_p);
	}
	inline void Pre_Sum(V a[],int n,V b[]) {
		b[0]=a[0]; rep(i,1,n-1) b[i]=add(b[i-1],a[i]);
	}
	inline void Pre_Sum_k(V a[],int n,ll k,V b[]) {
		Init_Com_Num_L_B(b,n,k-1),Mul(a,n,b,n,b);
	}
	inline void Fly(V a[],int n,ll k,V b[]) {
		k%=_p; for (int i=0,t=1; i<n; ++i,t=mul(t,k)) b[i]=mul(a[i],t);
	}
	inline void Crossify(V a[],int n) { Fly(a,n,-1,a); }
	inline void Diff(V a[],int n,V b[]) {
		rep(i,0,n-2) b[i]=a[i+1]-a[i]; b[n-1]=-a[n-1];
	}
	inline void Diff_k(V a[],int n,int k,V b[]) {
		Init_Com_Num_H_B(b,k+1,k),Crossify(b,k+1),Mul(a,n,b,k+1,b),Shl(b,n+k,k,b);
	}
	inline void Get_all_one(V a[],int n) { rep(i,0,n-1) a[i]=1; }
	inline void Get_exp_x(V a[],int n) { Fill(a,fac_inv,n,n); }
	inline void Get_log_1_add_x(V a[],int n) {
		a[0]=0; int t=1; rep(i,1,n-1) a[i]=t*inv[i],t=-t;
	}
	inline void Init_Bell_Num(V a[],int n) {
		Get_exp_x(C,n),C[0]=0,Exp(C,n,a),To_egf(a,n,a);
	}
	inline void Init_Bernoulli_Num(V a[],int n) {
		Get_exp_x(C,n+1),Shl(C,n+1,1,C),Inv(C,n,a),To_egf(a,n,a);
	}
	inline V Get_Num_Power_Sum(ll n,int k) {
		n%=_p; V ans=0; static V C[_N<<2];
		Init_Com_Num_H_B(C,k+2,k+1),Init_Bernoulli_Num(B,k+1);
		for (int i=1,t=n*(k&1?-1:1); i<=k+1; ++i,t=mul(t,-n)) 
			ans=add(ans,mul(C[i],B[k+1-i])*t%_p);
		ans=mul(ans,inv[k+1]); return ans;
	}
	inline void Init_Stiriling_Num_2_H_B(V a[],int n,ll k) {
		k%=_p-1; static V A[_N<<2],B[_N<<2];
		rep(i,0,n-1) A[i]=(i&1)?-1:1,B[i]=Pow(i,k);
		Bin_Mul(A,n,B,n,a),To_ogf(a,n,a);
	}
	inline void Init_Stiriling_Num_2_L(V a[],int n,int k) {
		static V A[_N<<2]; Get_exp_x(A,n+k),A[0]=0,POW(A,n+k,k,a,1);
		Dot_Mul(a,n+k,fac_inv[k],a),To_egf(a,n+k,a),Shl(a,n+k,k,a);
	}
	inline void Init_Stiriling_Num_1_L(V a[],int n,int k) {
		static V A[_N<<2]; Get_log_1_add_x(A,n+k),POW(A,n+k,k,a,1);
		Dot_Mul(a,n+k,((k&1)?-1:1)*fac_inv[k],a);
		To_egf(a,n+k,a),Crossify(a,n+k),Shl(a,n+k,k,a);
	}
	inline void Mod_p(V a[],int n) {
		rep(i,0,n-1) a[i]=(a[i]%_p+_p)%_p;
	}
};


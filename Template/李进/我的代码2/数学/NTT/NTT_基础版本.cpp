ll Pow(ll x,ll k) { ll ans=1; for (;k;k>>=1,x=x*x%_p) if (k&1) (ans*=x)%=_p; return ans; } 

template <class V>
struct FT{
	static const int N=1<<18; V w[2][N*2+5],rev[N*2+5],tmp;
	void Init() {
		V w0=Pow(3,(_p-1)/N),m; w[0][0]=w[1][0]=1;
		rep(i,1,N-1) w[0][i]=w[1][N-i]=(ll)w[0][i-1]*w0%_p;
		for (m=0; (1<<m)!=N; m++);
		rep(i,1,N-1) rev[i]=(rev[i>>1]>>1)|(i&1)<<m-1;
	}
	void FFT(V A[],int op){
		rep(i,0,N-1) if (i<rev[i]) swap(A[i],A[rev[i]]);
		for (int i=1; i<N; i<<=1)
			for (int j=0,t=N/(i<<1); j<N; j+=i<<1)
				for (int k=j,l=0; k<j+i; k++,l+=t) {
					V x=A[k],y=(ll)w[op][l]*A[k+i]%_p;
					A[k]=(x+y)%_p,A[k+i]=(x-y+_p)%_p;
				}
		if (op) { tmp=Pow(N,_p-2); rep(i,0,N-1) A[i]=1ll*A[i]*tmp%_p; }
	}
	void Solve(V A[],V B[],V C[],int op=0) {
		if (op) reverse(B,B+N); FFT(A,0),FFT(B,0); 
		rep(i,0,N-1) C[i]=(ll)A[i]*B[i]%_p; FFT(C,1); if (op) reverse(C,C+N);
	}
};

/*

注: 

1.N为大于长度2倍的2的幂,FT内部有效区域:[0,T.N-1];

2.Solve里op=0为普通卷积x+y=i,op=1为差卷积y-x=i,注意大的是B； 

3.多次使用，注意答案数组的有效区域[0,n-1]外的地方要清空,n是有效长度；

*/
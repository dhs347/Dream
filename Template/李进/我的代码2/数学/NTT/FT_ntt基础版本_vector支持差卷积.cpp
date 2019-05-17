ll Pow(ll x,ll k,ll _p) { ll ans=1; for (;k;k>>=1,x=x*x%_p) if (k&1) (ans*=x)%=_p; return ans; } 

const int _M=N,_N=N;
template <class V>
struct FT{
	vector <V> aa,bb; int _p,K; V w[2][_M*2+5],rev[_M*2+5],tmp;
	void Init(int _K,int p) { K=_K,_p=p; }
	void FFT(vector<V>& A,int m,int op){
		int N=1<<m; V w0=Pow(3,(_p-1)/N,_p); w[0][0]=w[1][0]=1;
		rep(i,1,N-1) w[0][i]=w[1][N-i]=(ll)w[0][i-1]*w0%_p;
		rep(i,1,N-1) rev[i]=(rev[i>>1]>>1)|(i&1)<<m-1;
		rep(i,0,N-1) if (i<rev[i]) swap(A[i],A[rev[i]]);
		for (int i=1; i<N; i<<=1)
			for (int j=0,t=N/(i<<1); j<N; j+=i<<1)
				for (int k=j,l=0; k<j+i; k++,l+=t) {
					V x=A[k],y=(ll)w[op][l]*A[k+i]%_p;
					A[k]=(x+y)%_p,A[k+i]=(x-y+_p)%_p;
				}
		if (op) { tmp=Pow(N,_p-2,_p); rep(i,0,N-1) A[i]=1ll*A[i]*tmp%_p; }
	}
	vector<V>& multiply(vector<V>& A,vector<V>& B,vector<V> *C=NULL,int op=0){
		int lena=A.size(),lenb=B.size(),len=1,L=0; aa=A,bb=B;
		while (len<2*max(lena,lenb)) len<<=1,++L;
		aa.resize(len),bb.resize(len);
        if (op) reverse(all(bb));
        FFT(aa,L,0),FFT(bb,L,0);
		if (!C) C=&A; (*C).resize(len);
		rep(i,0,len-1) (*C)[i]=(ll)aa[i]*bb[i]%_p;
		FFT(*C,L,1); 
		if (op) reverse(all(*C));
        if (K<len-1) (*C).resize(K+1); 
        return *C;
	}
}; 

ll Pow(ll x,ll k,ll _p) { ll ans=1; for (;k;k>>=1,x=x*x%_p) if (k&1) (ans*=x)%=_p; return ans; } 

const int _M=N,_N=N;
template <class V>
struct FT{
	vector <V> aa,bb,a[_N]; int m,_p,K; V w[2][_M*2+5],rev[_M*2+5],tmp;
	void Init(int _m,int _K,int p) { m=_m,K=_K,_p=p; rep(i,1,m) a[i].clear(); }
	void Insert(vector<V> C) { a[++m].swap(C); }
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
	vector<V>& multiply(vector<V>& A,vector<V>& B,vector<V> *C=NULL){
		int lena=A.size(),lenb=B.size(),len=1,L=0; aa=A,bb=B;
		while (len<2*max(lena,lenb)) len<<=1,++L;
		aa.resize(len),bb.resize(len),FFT(aa,L,0),FFT(bb,L,0);
		if (!C) C=&A; (*C).resize(len);
		rep(i,0,len-1) (*C)[i]=(ll)aa[i]*bb[i]%_p;
		FFT(*C,L,1); if (K<len-1) (*C).resize(K+1); return *C;
	}
	vector<V>& solve(int l,int r){
		if(l==r) return a[l];
		int mid=(l+r)>>1;
		return multiply(solve(l,mid),solve(mid+1,r));
	}
	int Q(int k,int l=1,int r=0) { r=r?r:m; return solve(l,r)[k]; }
	priority_queue <pii> H;
	vector<V>& H_Merge() {
	    while (!H.empty()) H.pop();
	    rep(i,1,m) H.emplace(-a[i].size(),i);
	    while (H.size()>=2) {
	        int x=H.top().sec; H.pop();
	        int y=H.top().sec; H.pop();
	        multiply(a[x],a[y]),H.emplace(-a[x].size(),x);
	        a[y].clear();
        }
        return a[H.top().sec];
    }
}; 

/*

注：

1.模板类int比ll快很多，大约1s

2.H_Merge()中最后一句可以节约空间，加了空间是O(n),否则O(nlogn)

3.当模数较大时，最好用此模板，不要用fft

4.常见ntt质数：

P = 1004535809  ====>  pr = 3
P = 998244353   ====>  pr = 3

*/

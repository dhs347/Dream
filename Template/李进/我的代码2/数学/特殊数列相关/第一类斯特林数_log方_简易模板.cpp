ll Pow(ll x,ll k,ll _p) { ll ans=1; for (;k;k>>=1,x=x*x%_p) if (k&1) (ans*=x)%=_p; return ans; } 

const int _M=N,_N=N;
template <class V>
struct FT{
	vector <V> aa,bb,a[_N]; int m,_p,K; V w[2][N*2+5],rev[N*2+5],tmp;
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

FT<int> T;

ll S(int n,int k) {
    if (!(0<=k && k<=n)) return 0;
	if (!n) return 1;
	T.Init(n,min(n,k),_p);
	rep(i,1,n) T.a[i].pb(i-1),T.a[i].pb(1);
	return T.H_Merge()[k];
} 


/*

注：时间复杂度O(nlogn)或O(nlogn)

*/
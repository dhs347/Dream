const int _N=256,_M=256;
template <class V>
struct Matrix{
	int n,m; V x[_N][_M];
	Matrix& operator = (const V &t) { rep(i,0,n-1) rep(j,0,m-1) x[i][j]=t; return *this; }
	void set(int _n,int _m,V x=0) { n=_n,m=_m,*this=x; }
	Matrix(int _n=0,int _m=0,V x=0) { n=_n,m=_m,*this=x; }
	V* operator [] (const int &t) { return x[t]; }
	Matrix& operator += (const Matrix &t) { rep(i,0,n-1) rep(j,0,m-1) x[i][j]+=t.x[i][j]; return *this; }
	Matrix& operator *= (const Matrix &t) {
		Matrix C(n,t.m,0);
		rep(i,0,n-1) rep(k,0,m-1) if (x[i][k]!=0) rep(j,0,t.m-1) if (t.x[k][j]!=0) (C[i][j]+=x[i][k]*t.x[k][j]%_p)%=_p; return *this=C;
	}
	Matrix& operator *= (const V &t) { rep(i,0,n-1) rep(j,0,m-1) x[i][j]*=t; return *this; }
	friend Matrix operator + (const Matrix &A,const Matrix &B) { Matrix C=A; C+=B; return C; }
	friend Matrix operator * (const Matrix &A,const Matrix &B) { Matrix C=A; C*=B; return C; }
	friend Matrix operator * (const Matrix &A,const V &B) { Matrix C=A; C*=B; return C; }
	friend Matrix operator * (const V &A,const Matrix &B) { Matrix C=B; C*=A; return C; }
	static Matrix E(int n) { Matrix C(n,n,0); rep(i,0,n-1) C.x[i][i]=1; return C; }
	void print() { printf("Matrix: n=%d m=%d\n\n",n,m); debug_arr2(x,n,m); }
}; 
typedef Matrix<ll> Mat;
void pre_calc(Mat* F,ll k){ for (int i=1; (1ll<<i)<=k; i++) F[i]=F[i-1]*F[i-1]; }
Mat Pow(Mat* F,ll k) {
	int t=F[0].n; Mat ans(t,t); ans=Mat::E(t);
	for (int i=0;k;k>>=1,i++) if (k&1) ans*=F[i]; return ans;
}

struct Trie_Tu{
	static const int M=26; int go[N][M],pre[N],toop[N],dep[N],temp[N],id[N],cnt,str_cnt,S,t,l,r,f,T,tot; ll sum[N],ans; Mat* A;
	inline int h(int c) { return c-'a'; }
	inline int new_node(int d=0) { ++cnt,pre[cnt]=0,mem(go[cnt],0); dep[cnt]=d; sum[cnt]=0; return cnt; }
	inline void Init() { str_cnt=cnt=0; S=new_node(); rep(i,0,M-1) go[0][i]=S; } 
    inline void Go(int &p,int c,int f=1) { int &t=go[p][c]; p=t?t:t=new_node(dep[p]+1); if (f) ans+=sum[p]; else /**/; }
    inline int Run(const char s[],int _n=0,int op=0,int f=1) {
        if (!_n) _n=strlen(s); int pos=S,p=op*(_n-1),q=(op?-1:_n); op=1-2*op,T+=f; ans=0;
        for (int i=p; i!=q; i+=op) Go(pos,h(s[i]),f); return pos;
    }
    inline void Insert(const char s[],int _n=0,int op=0) { str_cnt++,sum[t=Run(s,_n,op,0)]++; /*...*/ }
    inline void Build() {
    	for (toop[l=r=1]=S; l<=r && (f=toop[l++]); )
    		rep(i,0,M-1) if (!go[f][i]) go[f][i]=go[pre[f]][i]; else
    		pre[t=go[f][i]]=go[pre[f]][i], t!=S ? toop[++r]=t : 0; Toop(),Count(); 
	}
	inline void Toop() {
        rep(i,0,cnt) temp[i]=0; rep(i,1,cnt) temp[dep[i]]++;
        rep(i,1,cnt) temp[i]+=temp[i-1]; per(i,cnt,1) toop[temp[dep[i]]--]=i;
    }
    inline void Merge(int x,int y) { sum[x]+=sum[y]; }
    inline void Count() { rep(i,1,cnt) Merge(toop[i],pre[toop[i]]); }
    inline Mat* Get_Security_Tu() {
    	tot=0; rep(i,1,cnt) if (!sum[i]) id[i]=tot++; if (A!=NULL) delete A; A=new Mat(tot,tot,0);
    	rep(i,1,cnt) if (!sum[i]) rep(j,0,M-1) if (!sum[go[i][j]]) (*A)[id[i]][id[go[i][j]]]++; return A;
	}
	inline void Q() {  }
};

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
		rep(i,0,n-1) rep(k,0,m-1) if (x[i][k]!=0) rep(j,0,t.m-1) if (t.x[k][j]!=0) C[i][j]+=x[i][k]*t.x[k][j]; return *this=C;
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

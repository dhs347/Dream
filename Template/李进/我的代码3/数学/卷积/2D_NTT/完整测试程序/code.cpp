# include <iostream>
# include <sstream>
# include <cstdio>
# include <cstdlib>
# include <algorithm>
# include <string>
# include <cstring>
# include <cmath>
# include <stack>
# include <queue>
# include <vector>
# include <list>
# include <map>
# include <set>
# include <deque>
# include <iterator>
# include <functional>
# include <bitset>
# include <climits>
# include <ctime>
using namespace std;
#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))
#define odd(x) ((x)&1)
#define sqr(x) ((x)*(x))
#define mp make_pair
#define pb push_back
#define fir first
#define sec second
#define all(x) (x).begin(),(x).end()
#define mem(a,x) memset(a,x,sizeof(a))
#define rep(i,a,b) for (int i=(a); i<=(b); ++i)
#define per(i,a,b) for (int i=(a); i>=(b); --i)
#define rep_it(it,x) for (__typeof((x).begin()) it=(x).begin(); it!=(x).end(); it++)
#define ____ puts("\n_______________\n\n") 
#define debug(x) ____; cout<< #x << " => " << (x) << endl
#define debug_pair(x) cout<<"\n{ "<<(x).fir<<" , "<<(x).sec<<" }\n"
#define debug_arr(x,n) ____; cout<<#x<<":\n"; rep(i,0,n) cout<<#x<<"["<<(i)<<"] => "<<x[i]<<endl
#define debug_arr2(x,n,m) ____; cout<<#x<<":\n"; rep(i,0,n) rep(j,0,m) cout<<#x<<"["<<(i)<<"]["<<(j)<<"]= "<<x[i][j]<<((j==m)?"\n\n":"    ")
#define debug_set(x) ____; cout<<#x<<": \n"; rep_it(it,x) cout<<(*it)<<" "; cout<<endl
#define debug_map(x) ____; cout<<#x<<": \n"; rep_it(it,x) debug_pair(*it)
typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef vector<int> vi;
const int oo = /*2 * 1000 * 1000 * 1000*/0x3f3f3f3f;
const ll ooo=9223372036854775807ll; 
const int _cnt = 1000 * 1000 + 7;
const int _p = 998244353;
const int N=100005; 
const double PI=acos(-1.0);
const double eps=1e-9;
int o(int x) { return x%_p; }
int gcd(int a, int b) { return b ? gcd(b, a%b) : a; }
int lcm(int a, int b) { return a / gcd(a, b)*b; }

void file_put() {
    freopen("filename.in", "r", stdin);
    freopen("filename.out", "w", stdout);
}

typedef vector<vector<int>> vii;

const int _M=N,_N=N;
template <class V>
struct FT{
	vector <V> aa,bb; int _p,K,_m,N; V w[2][_M*2+5],rev[_M*2+5],tmp,w0;
	inline void Init(int _K,int p) { K=_K,_p=p; }
	ll Pow(ll x,ll k,ll _p) { ll ans=1; for (;k;k>>=1,x=x*x%_p) if (k&1) (ans*=x)%=_p; return ans; } 
	inline void get_len(int a,int b,int &len,int &L) { len=1,L=0; while (len<a+b) len<<=1,++L; }
	inline void init_w(int m) {
	    N=1<<m,w0=Pow(3,(_p-1)/N,_p); w[0][0]=w[1][0]=1;
		rep(i,1,N-1) w[0][i]=w[1][N-i]=(ll)w[0][i-1]*w0%_p;
		rep(i,1,N-1) rev[i]=(rev[i>>1]>>1)|(i&1)<<m-1;
    }
	inline void FFT(vector<V>& A,int m,int op){
	    if (m!=_m) init_w(_m=m);
	    rep(i,0,N-1) if (i<rev[i]) swap(A[i],A[rev[i]]);
		for (int i=1; i<N; i<<=1)
			for (int j=0,t=N/(i<<1); j<N; j+=i<<1)
				for (int k=j,l=0; k<j+i; k++,l+=t) {
					V x=A[k],y=(ll)w[op][l]*A[k+i]%_p;
					A[k]=(x+y)%_p,A[k+i]=(x-y+_p)%_p;
				}
		if (op) { tmp=Pow(N,_p-2,_p); rep(i,0,N-1) A[i]=1ll*A[i]*tmp%_p; }
	}
	inline void multiply(const vector<V>& A,const vector<V>& B,vector<V> *C){
		int lena=A.size(),lenb=B.size(),len=1,L=0; aa=A,bb=B;
		get_len(lena,lenb,len,L),aa.resize(len),bb.resize(len);
        FFT(aa,L,0),FFT(bb,L,0),(*C).resize(len);
		rep(i,0,len-1) (*C)[i]=(ll)aa[i]*bb[i]%_p;
		FFT(*C,L,1); if (K<len-1) (*C).resize(K+1); 
	}
};

struct Matrix{
    int n,m; vii a;
    inline void Set_m(int _m,int x=0) { m=_m; rep(i,0,n-1) a[i].resize(m,x); }
    inline void Set_n(int _n) { n=_n,a.resize(n); }
    inline void Set(int _n,int _m,int x=0) { Set_n(_n),Set_m(_m,x); }
    Matrix(int n=0,int m=0,int x=0):n(n),m(m) {
        a.clear(),a.resize(n); Set_m(m,x);
    }
    inline void Transpose() {
        Matrix t=Matrix(m,n,0);
        rep(i,0,n-1) rep(j,0,m-1) t.a[j][i]=a[i][j];
        *this=t;
    }
    inline void Reverse() {
        Matrix t=Matrix(n,m,0);
        rep(i,0,n-1) rep(j,0,m-1) t.a[n-1-i][m-1-j]=a[i][j];
        *this=t;
    }
    inline void Shift(int x,int y) {
        rep(i,x,n-1+x) rep(j,y,m-1+y) a[i-x][j-y]=(i<n&&j<m)?a[i][j]:0;   
    }
    inline void FFT(FT<int> &T,int len,int op) {
        if (!op) Set_m(1<<len,0);
        rep(i,0,n-1) T.FFT(a[i],len,op);
    }
    inline void print() const;
    inline void Normalize(int _p);
    inline void Random();
};

inline void Matrix::print() const {
    printf("\n\n\n\n\nn => %d     m => %d\n",n,m);
    debug_arr2(a,n-1,m-1);
}

inline void Matrix::Normalize(int _p) {
    rep(i,0,n-1) rep(j,0,m-1) if (a[i][j]<0) a[i][j]+=_p;
}

inline void Matrix::Random() {
    rep(i,0,n-1) rep(j,0,m-1) a[i][j]=(rand()<<15)+rand();
}

inline bool operator==(const Matrix &A,const Matrix &B) {
    if (A.n!=B.n || A.m!=B.m) return 0;
    rep(i,0,A.n-1) rep(j,0,A.m-1) if (A.a[i][j]!=B.a[i][j]) return 0;
    return 1;
}

struct Calculator{
    Matrix aa,bb,cc; FT<int> T; int len,L,_p;
    inline void Init(int p) { _p=p; }
    inline void Multiply(const Matrix &A,const Matrix &B,Matrix &C,int op=0) {
        aa=A,bb=B; if (op) aa.Reverse(); T.get_len(A.m,B.m,len,L),T.Init(cc.m=A.n+B.n-1,_p);
        aa.FFT(T,L,0),bb.FFT(T,L,0),aa.Transpose(),bb.Transpose(),cc.Set_n(aa.n);
        rep(i,0,aa.n-1) T.multiply(aa.a[i],bb.a[i],&cc.a[i]);
        cc.Transpose(),cc.FFT(T,L,1),cc.Set_m(A.m+B.m-1),C=cc;
        if (op) C.Shift(A.n-1,A.m-1);
    }
    inline void add(int &x,int y) { x+=y,x%=_p; }
    inline int mul(int x,int y) { return (ll)x*y%_p; }
    inline void Multiply_B(const Matrix &A,const Matrix &B,Matrix &C) {
        C.Set(A.n+B.n-1,A.m+B.m-1);
        rep(xa,0,A.n-1) rep(ya,0,A.m-1) rep(xb,0,B.n-1) rep(yb,0,B.m-1)
            add(C.a[xa+xb][ya+yb],mul(A.a[xa][ya],B.a[xb][yb]));
    }
    inline void Multiply_B_sub(const Matrix &A,const Matrix &B,Matrix &C) {
        C.Set(A.n+B.n-1,A.m+B.m-1);
        rep(xa,0,A.n-1) rep(ya,0,A.m-1) rep(xb,xa,B.n-1) rep(yb,ya,B.m-1)
            add(C.a[xb-xa][yb-ya],mul(A.a[xa][ya],B.a[xb][yb]));
    }
};

Matrix A,B,C,D,E,F;
int n1,n2,m1,m2;
Calculator T;

int main() {
    file_put();
    
    srand(time(0));
    scanf("%d%d%d%d",&n1,&m1,&n2,&m2);
    A.Set(n1,m1),B.Set(n2,m2);
    
    //rep(i,0,A.n-1) rep(j,0,A.m-1) scanf("%d",&A.a[i][j]);
    //rep(i,0,B.n-1) rep(j,0,B.m-1) scanf("%d",&B.a[i][j]); 
    
    A.Random(),B.Random();
    //A.print(),B.print();
    T.Init(_p);
    
    //T.Multiply_B(A,B,C);
    T.Multiply(A,B,D,0);
    C.Normalize(_p),D.Normalize(_p);
    //C.print(),D.print();
    
    //T.Multiply_B_sub(A,B,E);
    T.Multiply(A,B,F,1);
    E.Normalize(_p),F.Normalize(_p);
    //E.print(),F.print();
    
    debug(C==D);
    debug(E==F);
	
    return 0;
}


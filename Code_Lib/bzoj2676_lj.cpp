#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define rep(i, a, b) for(int i=(a); i<(b); i++)
#define per(i, a, b) for(int i=(b)-1; i>=(a); i--)
#define sz(a) (int)a.size()
#define de(a) cout << #a << " = " << a << endl
#define dd(a) cout << #a << " = " << a << " "
#define all(a) a.begin(), a.end()
#define pw(x) (1ll<<(x))
#define endl "\n"
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef double db;
const double eps=1e-15;

#define mem(a,x) memset(a,x,sizeof(a))

void file_put() {
    freopen("filename.in", "r", stdin);
    freopen("filename.out", "w", stdout);
}

int M;
struct mat{
	double a[105][105]; 
	inline double* operator[](int x) { return a[x]; }
	inline const double* operator[](int x) const { return a[x]; }
	mat(double x=0) { mem(a,0); rep(i,0,M) a[i][i]=x; }
	inline void clear(double x=0) { mem(a,0); rep(i,0,M) a[i][i]=x; }
	inline friend mat operator+(const mat &A,const mat &B) {
		mat C;
		rep(i,0,M) rep(j,0,M) C[i][j]=A[i][j]+B[i][j];
		return C;
	}
	inline friend mat operator-(const mat &A,const mat &B) {
		mat C;
		rep(i,0,M) rep(j,0,M) C[i][j]=A[i][j]-B[i][j];
		return C;
	}
	inline friend mat operator*(const mat &A,const mat &B) {
		mat C;
		rep(i,0,M) rep(k,0,M) if (A[i][k]>eps)
			rep(j,0,M) if (B[k][j]>eps)
				C[i][j]+=A[i][k]*B[k][j];
		return C;
	}
	inline friend mat operator^(mat &A,ll k) {
		mat ret(1);
		for (; k; k>>=1,A=A*A) if (k&1) ret=ret*A;
		return ret;
	}
};

int n,r,q,sz,ss; double L=0,R=1,mid,ans; mat A; mat ret(1);

int id(int x,int y) {
	return (x-1)*r+y-1;
}

inline void link(int x,int y,int s,int t,double p) {
	if (s>q || t>r || s<1 || t<1) return;
	A[id(s,t)][id(x,y)]+=p;
}

bool check(double p) {
	A.clear();
	rep(i,1,q+1) rep(j,1,r+1) link(i,j,min(i+1,q),min(j+1,r),p);
	rep(i,1,q+1) rep(j,1,r+1) link(i,j,i-1,1,1-p),A[sz-1][id(i,j)]+=p*j;
	A[sz-1][sz-1]+=1;
	A=(A^n);
	return A[sz-1][id(q,1)]-ss>eps;
}

int main() {
	//file_put();
	
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	
	cin>>n>>r>>q>>ss;M=sz=r*q+1;
	if (!check(1)) {
		cout<<"Impossible."<<endl;
		return 0;
	}
	while (R-L>eps) {
		mid=(L+R)/2;
		if (check(mid)) R=mid; else L=mid;
	}
	
	cout << setiosflags(ios::fixed);
	cout << setprecision(6);
	cout<<mid<<endl; 
	
	return 0;
}


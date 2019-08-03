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
#define all(a) (a).begin(), (a).end()
#define pw(x) (1ll<<(x))
#define lb(x) ((x) & -(x))
#define endl "\n"
#define FI(x) freopen(#x".in","r",stdin)
#define FO(x) freopen(#x".out","w",stdout)
typedef double db;
typedef int ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;
//typedef uniform_int_distribution<ll> RR;
const int _p = 1e9 + 9, N = 6600, w0=115381398ll;

int p, pw3[10], w[3];
long long n;
int add(int x, int y) { return (x + y) % _p;}
ll mul(ll x,ll y) { return 1ll * x * y%_p; }

ll Pow(ll x,ll k) {
	ll ret=1;
	for (;k;k>>=1,x=mul(x,x)) if (k&1) ret=mul(ret,x);
	return ret;
}

/*template <int K>
struct Num{
	ll a[K];
	Num(int x=0) { memset(a,0, sizeof(a)),a[0]=x; }
	inline Num& operator = (const Num &t) {
		rep(i,0,K) a[i]=t.a[i];
		return *this;
	}
	inline Num& operator = (int x) { memset(a,0, sizeof(a)),a[0]=x; return *this; }
	inline friend Num operator + (const Num &a,const Num &b) {
		Num c;
		rep(i,0,K) c.a[i]=add(a.a[i],b.a[i]);
		return c;
	}
	inline friend Num operator - (const Num &a,const Num &b) {
		Num c;
		rep(i,0,K) c.a[i]=add(a.a[i],-b.a[i]);
		return c;
	}
	inline friend Num operator * (const Num &a,const Num &b) {
		Num c;
		rep(i,0,K) rep(j,0,K) (c.a[(i+j)%K]+=mul(a.a[i],b.a[j]))%=_p;
		return c;
	}
	inline friend Num operator >> (const Num &a,int k) {
		Num c;
		rep(i,0,K) c.a[(i+k)%K]=a.a[i];
		return c;
	}
	inline friend Num operator ^ (Num x,ll k) {
        Num ret=1;
        for (;k;k>>=1,x=x*x) if (k&1) ret=ret*x;
        return ret;
	}
	inline ll Value() {
	    int cnt=K&-K,L=K/cnt; ll ret=add(a[0],-(L>1)*a[cnt]);
	    if (K&1^1) ret-=add(a[K>>1],-(L>1)*a[(K>>1)+cnt]),ret%=_p;
	    return ret;
    }
	inline void print(string s="") {
		printf("\n\n\n%s\n",s.c_str());
		rep(i,0,K) printf("a[%d] => %d\n",i,a[i]);
	}
};*/

template <int M,int N,int K>
struct FT{
	int tmp[M<<1], a[N], b[N], t;
	void FWT(int a[],int S,int n,int op) {
		if (n==1) return; int L=n/M;
		rep(i,0,M) FWT(a,S+L*i,n/M,op);
		rep(i,0,L) {
			rep(j,0,M) tmp[j]=0;
			rep(j,0,M) rep(k,0,M) {
				t=op*j*k%M,t<0?t+=M:0;
				tmp[j]=add(tmp[j], mul(a[S+L*k+i], w[t])); 
			}
			rep(j,0,M) a[S+L*j+i]=tmp[j];
		}
	}
	void tran(ll A[], int n, int C[]) {
		rep(i, 0, n) a[i] = A[i];
		FWT(a, 0, n, 1);
		rep(i, 0, n) C[i] = a[i];
	}
	void tran2(int A[], int n, ll C[]) {
		rep(i, 0, n) a[i] = A[i];
		FWT(a, 0, n, -1);
		ll inv=Pow(n,_p-2);
	    rep(i,0,n) C[i]=mul(a[i], inv),C[i]<0?C[i]+=_p:0;
	}
/*	void Multiply(ll A[],ll B[],int n,ll C[]) {
	    rep(i,0,n) a[i]=A[i],b[i]=B[i];
	    FWT(a,0,n,1),FWT(b,0,n,1);
	    rep(i,0,n) a[i]=a[i]*b[i];
	    FWT(a,0,n,-1); ll inv=Pow(n,_p-2);
	    rep(i,0,n) C[i]=mul(a[i].Value(),inv),C[i]<0?C[i]+=_p:0;
    }
    int get(int x,int y) {
        int ret=0,B=1;
        for (; x||y; x/=M,y/=M,B*=M) ret+=(x%M+y%M)%M*B;
        return ret;
    }
    void Multiply_B(ll A[],ll B[],int n,ll C[]) {
        rep(i,0,n) rep(j,0,n) (C[get(i,j)]+=mul(A[i],B[j]))%=_p;
        rep(i,0,n) C[i]<0?C[i]+=_p:0;
    }*/
};

FT<3, N, 3> T;

ll tmp[N], an1[8][N], an2[8][N];
int t1[8][N], t2[8][N], t3[N], tmp3[8][N], ans[8][N], a0[8][N], pre1[8][8][N], pre2[8][8][N];

const int m = 6561;
clock_t st, ed;
void solve(long long n) {
	n--;
	rep(i, 0, p) rep(j, 0, m) {
		ans[i][j] = pre1[p][i][j];
		a0[i][j] = pre2[p][i][j];
	}
	int len = 8 % p;
	while (n) {
		if (n & 1) {
			rep(i, 0, p) memset(tmp3[i], 0, sizeof(tmp3[i]));
			rep(i, 0, p) {
				rep(j, 0, p) {
					int t = (i * len + j) % p;
					rep(k, 0, m) tmp3[t][k] = add(tmp3[t][k], mul(ans[i][k], a0[j][k]));
				}
			}
			rep(j, 0, p) memcpy(ans[j], tmp3[j], sizeof(tmp3[j]));
		}
		rep(i, 0, p) memset(tmp3[i], 0, sizeof(tmp3[i]));
		rep(i, 0, p) {
			rep(j, 0, p) {
				int t = (i * len + j) % p;
				rep(k, 0, m) tmp3[t][k] = add(tmp3[t][k], mul(a0[i][k], a0[j][k]));
			}
		}
		rep(j, 0, p) memcpy(a0[j], tmp3[j], sizeof(tmp3[j]));	
		n >>= 1; len = len * len % p;
	}
	T.tran2(ans[0], m, tmp);
} 

int main() {
	FI(a);
	FO(a);
	//ios::sync_with_stdio(0);
	//cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	w[0] = 1; w[1] = w0; w[2] = mul(w0, w0); 
	pw3[0] = 1; rep(i, 1, 10) pw3[i] = pw3[i-1] * 3;
	rep(p, 1, 8) {
		rep(i, 0, p) rep(j, 0, m) an1[i][j] = an2[i][j] = 0;
		rep(i, 1, 8) an1[i % p][pw3[i]] = 1;
		rep(i, 0, 8) an2[i % p][pw3[i]] = 1;
		rep(i, 0, p) {
			T.tran(an1[i], m, pre1[p][i]);
			T.tran(an2[i], m, pre2[p][i]);
		}
	}
	while (cin >> n >> p) {
		solve(n);
		cout << tmp[0] << endl;
	} 
	return 0;
}


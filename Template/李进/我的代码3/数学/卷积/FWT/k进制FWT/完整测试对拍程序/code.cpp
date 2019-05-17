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
#define mem(a,x) memset(a,x,sizeof(a))

const int _p=998244353;
ll add(ll x,ll y) { x+=y; return x%_p; }
ll mul(ll x,ll y) { return x*y%_p; }
ll Pow(ll x,ll k) {
	ll ret=1;
	for (;k;k>>=1,x=mul(x,x)) if (k&1) ret=mul(ret,x);
	return ret;
}

template <int K>
struct Num{
	ll a[K];
	Num(int x=0) { mem(a,0),a[0]=x; }
	inline Num& operator = (const Num &t) {
		rep(i,0,K) a[i]=t.a[i];
		return *this;
	}
	inline Num& operator = (int x) { mem(a,0),a[0]=x; return *this; }
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
};

template <int M,int N,int K>
struct FT{
	Num<K> tmp[M<<1],a[N],b[N]; int t;
	void FWT(Num<K> a[],int S,int n,int op) {
		if (n==1) return; int L=n/M;
		rep(i,0,M) FWT(a,S+L*i,n/M,op);
		rep(i,0,L) {
			rep(j,0,M) tmp[j]=0;
			rep(j,0,M) rep(k,0,M) {
				t=op*j*k%M,t<0?t+=M:0;
				tmp[j]=tmp[j]+(a[S+L*k+i]>>t); 
			}
			rep(j,0,M) a[S+L*j+i]=tmp[j];
		}
	}
	void Multiply(ll A[],ll B[],int n,ll C[]) {
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
    }
};

void file_put() {
    freopen("filename.in", "r", stdin);
    freopen("filename.out", "w", stdout);
}

const int N=100000;
FT<10,N,10> T;
ll inv,a[N],b[N],c[N],d[N];

int main() {
	file_put();
	
	srand(time(0));
	
	//rep(i,0,N) scanf("%lld",&a[i]);
	//rep(i,0,N) scanf("%lld",&b[i]);
	
	rep(i,0,N) a[i]=(rand()<<15)|rand();
	rep(i,0,N) b[i]=(rand()<<15)|rand();
	
	T.Multiply(a,b,N,c);
	//T.Multiply_B(a,b,N,d);
	
	//rep(i,0,3) printf("%lld\n",c[i]); printf("\n");
	//rep(i,0,3) printf("%lld\n",d[i]); printf("\n");
	
    //if (equal(c,c+N,d)) printf("Yes\n"); else printf("No\n");

	return 0;
}


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
const int _p=998244353; int n;
const int N=50005,M=40;

template <class V,int M>
struct Poly{
	V a[M];
	Poly() { mem(a,0); }
	Poly(const vi &t) {
		mem(a,0);
		for (int i=0; i+1<sz(t); i+=2) a[t[i]]=t[i+1];
	}
	inline V& operator [] (int x) { return a[x]; }
	inline V operator [] (int x) const { return a[x]; }
	inline friend Poly operator + (const Poly &a,const Poly &b) {
		Poly c;
		rep(i,0,M) c[i]=(a[i]+b[i])%_p;
		return c;
	}
	inline friend Poly operator - (const Poly &a,const Poly &b) {
		Poly c;
		rep(i,0,M) c[i]=(a[i]-b[i])%_p;
		return c;
	}
	inline friend Poly operator * (const Poly &a,const Poly &b) {
		Poly c;
		rep(i,0,M) for (int j=0; i+j<M; j++) c[i+j]+=a[i]*b[j]%_p,c[i+j]%=_p;
		return c;
	}
	inline friend Poly<int,N> operator / (Poly a,const Poly &b) {
        Poly<int,N> c;  
        rep(i,0,40) c[i]=a[i];
		rep(i,0,n+1) rep(j,1,min(i,39)+1) c[i]+=(ll)c[i-j]*(-b[j]+(!j))%_p,c[i]%=_p;
		return c;
	}
	inline friend Poly operator << (const Poly &a,int k) {
		Poly c;
		rep(i,0,M-k) c[i]=a[i+k];
		return c;
	}
	inline friend Poly operator >> (const Poly &a,int k) {
		Poly c;
		per(i,k,M) c[i]=a[i-k];
		return c;
	}
	inline friend Poly operator ^ (Poly a,ll k) {
		Poly c; c[0]=1;
		for (; k; k>>=1,a=a*a) if (k&1) c=c*a;
		return c;
	}
	inline friend Poly sqr(const Poly &a) { return a*a; }
	inline void print() const {
		printf("\n\n\n");
		rep(i,0,M) printf("a[%d]=%d\n",i,a[i]);
		printf("\n\n\n");
	}
};

ll h(ll x) { return x*(x-1)%_p*(x-1)%_p; }

Poly<int,40> FM,FZ,
	Q({0,1,2,-3,6,5,10,-3,12,-1}),
	P0({2,4,4,20,6,12,8,16}),
	P1({0,1,2,6,4,23,6,2,8,9}),
	P2({0,4,2,4,4,24,6,-4,8,4});
	
Poly<int,N> F0,F1,F2;
int m,x,g[N]; ll ans=0,ret;

void file_put() {
    freopen("filename.in", "r", stdin);
    freopen("filename.out", "w", stdout);
}

int main() {
	//file_put();
	
	scanf("%d",&n);
	g[0]=g[2]=1;
	rep(i,4,N) g[i]=((ll)g[i-2]+g[i-4])%_p;
	FM=((P0>>1)-Q)*((P2>>3)-Q)-(sqr(P1)>>4);
	FZ=P1*Q;
	F0=((sqr(P1)>>3)-P0*((P2>>3)-Q))/FM;
	F1=FZ/FM;
	F2=(FM*P2+(P1*FZ>>1))/(FM*(Q-(P2>>3)));
	ans=(g[n-1]+g[n-3])*h(n)%_p;
	rep(i,2,n-1) {
		ret=(ll)g[i-1]*F0[n-i-1]%_p;
		ret+=2ll*g[i-2]*F1[n-i-2]%_p;
		if (i>=3 && i<=n-3) ret+=(ll)g[i-3]*F2[n-i-3]%_p;
		ret%=_p;
		ans+=ret*h(i)%_p;
	}
	ans%=_p,ans=(ans+_p)%_p;
	printf("%lld\n",ans);
	
	return 0;
}

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
#define mem(a,x) memset(a,x,sizof(a))


#define rep_it(it,x) for (__typeof((x).begin()) it=(x).begin(); it!=(x).end(); it++)
#define ____ puts("\n_______________\n\n") 
#define debug(x) ____; cout<< #x << " => " << (x) << endl
#define debug_pair(x) cout<<"\n{ "<<(x).fir<<" , "<<(x).sec<<" }\n"
#define debug_arr(x,n) ____; cout<<#x<<":\n"; rep(i,0,n+1) cout<<#x<<"["<<(i)<<"] => "<<x[i]<<endl
#define debug_arr2(x,n,m) ____; cout<<#x<<":\n"; rep(i,0,n+1) rep(j,0,m+1) cout<<#x<<"["<<(i)<<"]["<<(j)<<"]= "<<x[i][j]<<((j==m)?"\n\n":"    ")
#define debug_set(x) ____; cout<<#x<<": \n"; rep_it(it,x) cout<<(*it)<<" "; cout<<endl
#define debug_map(x) ____; cout<<#x<<": \n"; rep_it(it,x) debug_pair(*it)


void file_put() {
    freopen("filename.in", "r", stdin);
    freopen("filename.out", "w", stdout);
}

int P=1e9+7,cas=0;
const int MAXN= 1 << 18 << 1;
const db PI = acos(-1);

namespace FFT{
    

    int N,L,MASK,na,nb;
    int a[MAXN], b[MAXN];
    
    struct vir{
    	db r, i;
    	vir(db r = 0.0, db i = 0.0) : r(r), i(i){}
    	void print() {printf("%lf %lf\n", r, i);}
    };
    
    vir operator +(const vir &a, const vir &b) {return vir(a.r + b.r, a.i + b.i);}
    vir operator -(const vir &a, const vir &b) {return vir(a.r - b.r, a.i - b.i);}
    vir operator *(const vir &a, const vir &b) {return vir(a.r * b.r - a.i * b.i, a.r * b.i + a.i * b.r);}
    vir conj(vir a) {return vir(a.r, -a.i);}
    
    vir w[MAXN];
    
    void FFT(vir p[], int n) {
    	for (int i = 1, j = 0; i < n - 1; ++i) {
    		for (int s = n; j ^= s >>= 1, ~j & s;);
    		if (i < j) swap(p[i], p[j]);
    	}
    	for (int d = 0; (1 << d) < n; ++d) {
    		int m = 1 << d, m2 = m * 2, rm = n >> (d + 1);
    		for (int i = 0; i < n; i += m2) {
    			for (int j = 0; j < m; ++j) {
    				vir &p1 = p[i + j + m], &p2 = p[i + j];
    				vir t = w[rm * j] * p1;
    				p1 = p2 - t, p2 = p2 + t;
    			}
    		}
    	}
    }
    vir A[MAXN], B[MAXN], C[MAXN], D[MAXN];
    
    
    void doit(int *a, int *b, int na, int nb){
    	for (N = 1; N < na + nb - 1; N <<= 1);
    	rep(i,na,N) a[i]=0;
    	rep(i,nb,N) b[i]=0;
    	L = 15;	
    	MASK = (1<<L) - 1;
    	rep(i, 0, N) w[i] = vir(cos(2 * i * PI / N), sin(2 * i * PI / N));
    	rep(i, 0, N) {
    		A[i] = vir(a[i] >> L, a[i] & MASK);
    		B[i] = vir(b[i] >> L, b[i] & MASK);
    	}
    }
    
    void mul() {
    	FFT(A, N), FFT(B, N);
    	rep(i, 0, N) {
    		int j = (N - i) % N;
    		vir da = (A[i] - conj(A[j])) * vir(0, -0.5),
    			db = (A[i] + conj(A[j])) * vir(0.5, 0),
    			dc = (B[i] - conj(B[j])) * vir(0, -0.5),
    			dd = (B[i] + conj(B[j])) * vir(0.5, 0);
    		C[j] = da * dd + da * dc * vir(0, 1);
    		D[j] = db * dd + db * dc * vir(0, 1);
    	}
    	FFT(C, N), FFT(D, N);
    	for (int i = 0; i < N; ++i) {
    		ll  da = (ll)(C[i].i / N + 0.5) % P,
    			db = (ll)(C[i].r / N + 0.5) % P,
    			dc = (ll)(D[i].i / N + 0.5) % P,
    			dd = (ll)(D[i].r / N + 0.5) % P;
    		a[i] = ((dd << (L * 2)) + ((db + dc) << L) + da) % P;
    	}
    }

}

int a[MAXN],b[MAXN],S[MAXN],T,n,m,p; ll fac[MAXN],inv[MAXN],ret[MAXN];

ll Pow(ll x,ll k,ll P) {
    ll ret=1;
    for (; k; k>>=1,x=x*x%P) if (k&1) ret=ret*x%P;
    return ret;
}

struct polysum {
    static const int D = 1<<19;
    ll a[D], fac[D], ifac[D], p1[D], p2[D], h[D][2], C[D];
    ll add(ll a, ll b) {a = (a + b) % P; return a < 0 ? a + P : a;}
	ll mul(ll a, ll b) {a = 1ll * a * b % P; return a < 0 ? a + P : a;}
	ll kpow(ll a, ll b) {ll r=1;for(;b;b>>=1,a=mul(a,a)) {if(b&1)r=mul(r,a);}return r;}
    void init(int M) {
        fac[0] = 1; rep(i, 1, M+5) fac[i] = mul(fac[i-1], i);
        ifac[M+4] = kpow(fac[M+4], P - 2);
        per(i, 0, M+4) ifac[i] = mul(ifac[i+1], i+1);
    }
    ll calcn(int d, ll *a, ll n) { // a[0].. a[d]  a[n]
        if (n <= d && n>=0) return a[n];
        p1[0] = p2[0] = 1;
        rep(i, 0, d+1) p1[i+1] = mul(p1[i], (n - i) % P);
        rep(i, 0, d+1) p2[i+1] = mul(p2[i], (n - d + i) % P);
        ll ans=0;
        rep(i, 0, d+1) {
        	ll s1 = mul(p1[i], p2[d - i]);
        	ll s2 = mul(ifac[i], ifac[d - i]);
        	ll t = mul(mul(s1, s2), a[i]);
            ans = (d-i)&1 ? add(ans, -t) : add(ans, t);
        }
        return ans;
    }
} PP;



int main() {
//    file_put();
    
    scanf("%d",&T),fac[0]=inv[0]=inv[1]=1;
    while (T--) {
        scanf("%d%d%d",&n,&m,&P),p=n+m; PP.init(p+10);
        rep(i,1,p+1) fac[i]=fac[i-1]*i%P;
        rep(i,2,p+1) inv[i]=(P-P/i)*inv[P%i]%P;
        rep(i,1,p+1) inv[i]=inv[i-1]*inv[i]%P;
        rep(i,0,p+1) a[i]=(((i&1)?-1:1)*inv[i]+P)%P,b[i]=Pow(i,n,P)*inv[i]%P; 
//        debug_arr(a,p);
//        debug_arr(b,p);
        FFT::doit(a,b,p+1,p+1);
        FFT::mul();
        rep(i,0,p+1) S[i]=FFT::a[i];
//        debug_arr(S,p);
        rep(i,0,p+1) b[i]=Pow(i,m,P)*inv[i]%P;
        FFT::doit(S,b,p+1,p+1);
        FFT::mul(); 
        rep(i,0,p+1) ret[i]=FFT::a[i]*fac[i]%P;
//        debug_arr(ret,p);
        ll ans=PP.calcn(p,ret,-1);
        if (p&1) ans=-ans;
        printf("Case #%d: %lld\n",++cas,(ans+P)%P);
    }
        
	return 0;
}


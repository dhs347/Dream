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
const ll ooo=1ll<<60;

void file_put() {
    freopen("filename.in", "r", stdin);
    freopen("filename.out", "w", stdout);
}

const int P=1e9+7,_p=1e9+7;  ll sumcnt=0;

int add(int x,int y) {
    if ((x += y) >= P) x -= P;
    return x < 0 ? x + P : x;
}

int mul(int x,int y) {
    return (ll)x*y%P;
}

ll qpow(ll x,ll k) {
    x%=P;
    ll ret=1;
    for (;k; k>>=1,x=mul(x,x)) if (k&1) ret=mul(ret,x);
    return ret;
}

// desc : 0^k + 1^k + 2^k + .. + (n-1)^k
// time-ini : O(n^2)
// time-cal : k + log
namespace Bernoulli {
	const int N = 200;
	int C[N][N], B[N];
	void init() {
		rep(i, 0, N) C[i][0] = 1;
		rep(i, 0, N) rep(j, 1, i + 1) C[i][j] = add(C[i - 1][j - 1], C[i - 1][j]);
		B[0] = 1;
		rep(i, 1, N) {
			B[i] = 0;
			rep(j, 0, i) B[i] = add(B[i], P - mul(C[i + 1][j], B[j]));
			B[i] = mul(B[i], qpow(C[i + 1][i], P - 2)) % P;
		}
	}
	int cal(ll n, int k) { 
		int sum = 0; int invn=qpow(n,P-2);
		for (int i=0,p=qpow(n,k+1); i<=k; i++,p=mul(p,invn)) sum = add(sum, mul(C[k + 1][i], mul(B[i], p)));
		return mul(sum, qpow(k + 1, P - 2));
	}
};

struct Min_25{ 
	// F(i) 要拆成多个完全积性函数的和 
	static const int N = 5e5+ 7;
	int Sqr, m, p[N], id1[N], id2[N], tot, cntp, K, f[N];
	ll g[N], sp[N], h[N], n, w[N];
	bool isp[N];
	// f(p) = p ^ k 
	//ll f(int p) { return qpow(p,K); }
 
	// 假设都是质数的完全积性函数前缀和 去掉 f(1) 
	ll calc(ll n) { return Bernoulli::cal(n+1,K) - 1;}

	void prime(int n){
    	cntp = 0;isp[1] = 1;
    	rep(i, 2, n+1) {
        	if(!isp[i]) p[++cntp] = i;
        	for(int j = 1; j <= cntp && i * p[j] <= n; j++){
            	isp[i * p[j]] = 1;
            	if(i % p[j] == 0)break;
        	}
    	}
    	p[++cntp] = INT_MAX;
	}
	
	void solve(ll _n, int _K) {
	    n = _n, K=_K;
	    rep(i, 1, cntp) f[i] = qpow(p[i], K), sp[i] = add(sp[i - 1], f[i]);
	    if (n == 0) return;
		m = 0;Sqr = sqrt(n);
		tot = upper_bound(p + 1, p + cntp + 1, Sqr) - (p + 1);
		for(ll i = 1, j; i <= n; i = j + 1){
        	j = n / (n / i);
			w[++m] = n / i;
        	g[m] = calc(w[m]);
        	w[m] <= Sqr ? id1[w[m]] = m : id2[j] = m;
    	}
    	rep(j, 1, tot + 1)
        	for(int i = 1; i <= m && 1ll * p[j] * p[j] <= w[i]; i++){
				ll t = w[i] / p[j];
				int k = t <= Sqr ? id1[t] : id2[n / t]; 
        		g[i] = add(g[i], -mul(f[j], (g[k] - sp[j - 1])));
			}
	}
	
	ll get(ll _n) {
	    int t = _n <= Sqr ? id1[_n] : id2[n / _n];
	    return g[t];
    }
} _U;

namespace Du{
    
    const int _N=2000005,_M=2000000,P=4333333,N=3000005;

    struct HT{
    	int head[P],nxt[N],tot; ll v[N],e[N];
    	void init(){ mem(head,0); tot=0; }
        void I(int x,ll y,ll c){ assert(tot+1<N); e[++tot]=y,v[tot]=c; nxt[tot]=head[x]; head[x]=tot; }
        ll F(int x,ll y) { for (int i=head[x]; i; i=nxt[i]) if (e[i]==y) return v[i]; return -ooo; }
    };
    
    struct Euler{
    	int prime[_N],tot; bool check[_N]; ll f[_N],tmp, inv_6; HT T;
    	void init(){
            mem(check,0); tot=0; f[1]=1;
            rep(i,2,_M+1) {
                if(!check[i]) prime[tot++]=i,f[i]=i-1;
                rep(j,0,tot) {
                    if ((ll)i*prime[j]>_M) break;
                    check[i*prime[j]]=1;
                    if (i%prime[j]==0) { f[i*prime[j]]=f[i]*prime[j]; break; }
                    f[i*prime[j]]=f[i]*(prime[j]-1);
                }
            }
    		rep(i,1,_M+1) (f[i]*=((ll)i*i%_p))%=_p;
            T.init(); f[0]=0; rep(i,1,_M+1) (f[i]+=f[i-1])%=_p; inv_6=qpow(6,_p-2);
    	}
    	inline ll H(ll x){ x%=_p; int t=mul(mul(x,x+1),(_p+1>>1)); t=mul(t,t); return t; }
    	inline ll G(ll x) { x%=_p; return x*(x+1)%_p*(2*x+1)%_p*inv_6%_p; }
        ll F(ll x){
            if (x<=_M) return f[x]; tmp=T.F(x%P,x); ll g1_inv=1;
            if (tmp!=-ooo) return tmp; ll ans=H(x);
            for (ll l=2,r; l<=x; l=r+1) r=x/(x/l), (ans-=F(x/l)*((G(r)-G(l-1))%_p)%_p)%=_p;
    		//(ans*=g1_inv)%=_p;    //注意g(1)的逆元
            T.I(x%P,x,ans); return ans; 
        }
        ll ff(ll n) {
            ll ans=0,t;
            for (ll l=1,r; l<=n; l=r+1) {
                sumcnt++;
                r=n/(n/l), t=n/l%_p;
                ll tt=t*(t+1)%_p*(_p+1>>1)%_p;
                tt=tt*tt%_p;
                (ans+= tt*((F(r)-F(l-1))%_p)%_p)%=_p;
            }
    		return (ans+_p)%_p; 
        }
        ll query(ll n){
            T.init();
    		ll ans=0,t;
    		for (ll l=1,r; l<=n; l=r+1) r=n/(n/l), t=n/l%_p,(ans+= F(n/l)*((_U.get(r)-_U.get(l-1))%_p)%_p)%=_p;
    		return (ans+_p)%_p; 
    	}
    } E;
} 



int k,T; ll n;

int main() {
//    file_put();
    
//    de((sizeof(Du::E) + sizeof(_U) >> 20));
    
    scanf("%d",&T);
    
    Bernoulli::init();
    _U.prime(111111);
    
    Du::E.init();
    
    while (T--) {
        scanf("%lld%d",&n,&k);
        sumcnt=0;
        _U.solve(n, k+1);
        printf("%lld\n",Du::E.query(n));
    }
    
    
//    Bernoulli::init();

//    _U.prime(111111);
//    _U.solve(n, k);

//    scanf("%d",&n);
//    Du::E.init();
//    de(Du::E.F(n));
    
	return 0;
}


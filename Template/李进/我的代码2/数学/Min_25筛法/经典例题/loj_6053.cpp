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
const int _p = 1000 * 1000 * 1000 + 7;
const int N=200005; 
const double PI=acos(-1.0);
const double eps=1e-9;
int o(int x) { return x%_p; }
int gcd(int a, int b) { return b ? gcd(b, a%b) : a; }
int lcm(int a, int b) { return a / gcd(a, b)*b; }

void file_put() {
    freopen("filename.in", "r", stdin);
    freopen("filename.out", "w", stdout);
}

template <class V>
struct Euler{
	ll n,w[N]; bool pp[N]; int B,cnt,tot,id1[N],id2[N]; V p[N],g[N],h[N],s[N],f_1;
	inline void Init(ll _n){ 
		n=_n,B=sqrt(n)+1; mem(pp,0); 
		tot=cnt=0; g[0]=h[0]=s[0]=0; f_1=1; /* */ 
		init_prime(B),init_sum(); 
	}
	inline V f(int i,int e){ return p[i]^e; /* */ }
	inline int get_id(ll x){ return x<=B?id1[x]:id2[n/x]; }
	inline void init_prime(int _n){
		rep(i,2,_n){
			if (!pp[i]) p[++tot]=i,s[tot]=(s[tot-1]+i)%_p; /* */
			for (int j=1; j<=tot && i*p[j]<=_n; ++j) {
				pp[i*p[j]]=1;
				if (i%p[j]==0) break;
			}
		}
	}
	inline void init_sum(){
		for (ll i=1,j,x,k; i<=n; i=j+1){
            j=n/(n/i),w[++cnt]=x=n/i,x%=_p,k=cnt;
            (n/i<=B) ? id1[n/i]=k : id2[j]=k;
            h[k]=x-1; /* ... */
            g[k]=x*(x+1)%(2*_p)/2-1;
        }
        rep(j,1,tot) for (int i=1; i<=cnt && (ll)p[j]*p[j]<=w[i]; ++i){
            int k=get_id(w[i]/p[j]);
            (h[i]-=(ll)1*(h[k]-(j-1)))%=_p; /* ... */
            (g[i]-=(ll)p[j]*(g[k]-s[j-1])%_p)%=_p;
        }
	}
	inline V F(int k){ return g[k]-h[k]; /**/ }
	inline V G(int no){ return s[no]-no; /**/ }
	V S(ll x,int j){
	    if (x<=1 || p[j]>x) return 0;
	    int k=get_id(x); V ans=(F(k)-G(j-1))%_p;
	    if (j==1) ans+=2;
	    for (int i=j; i<=tot && (ll)p[i]*p[i]<=x; ++i){
	        ll t1=p[i],t2=(ll)p[i]*p[i];
	        for (int e=1; t2<=x; ++e,t1=t2,t2=t2*p[i])
	            (ans+=((ll)S(x/t1,i+1)*f(i,e)%_p+f(i,e+1)%_p))%=_p;
	    }
	    return ans;
	}
	inline V Solve(){ return ((S(n,1)+f_1)%_p+_p)%_p; } 
};

ll n; Euler<ll> E;

int main() {
    //file_put();
	
	scanf("%lld",&n),E.Init(n);
	printf("%lld\n",E.Solve());
	
    return 0;
}


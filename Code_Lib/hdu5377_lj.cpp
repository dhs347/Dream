#include<bits/stdc++.h>
//#pragma GCC optimize("Ofast") 
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

void file_put() {
    freopen("filename.in", "r", stdin);
    freopen("filename.out", "w", stdout);
}

#define rep_it(it,x) for (__typeof((x).begin()) it=(x).begin(); it!=(x).end(); it++)
#define ____ puts("\n_______________\n\n") 
#define debug(x) ____; cout<< #x << " => " << (x) << endl
#define debug_pair(x) cout<<"\n{ "<<(x).fir<<" , "<<(x).sec<<" }\n"
#define debug_arr(x,n) ____; cout<<#x<<":\n"; rep(i,0,n+1) cout<<#x<<"["<<(i)<<"] => "<<x[i]<<endl
#define debug_arr2(x,n,m) ____; cout<<#x<<":\n"; rep(i,0,n+1) rep(j,0,m+1) cout<<#x<<"["<<(i)<<"]["<<(j)<<"]= "<<x[i][j]<<((j==m)?"\n\n":"    ")
#define debug_set(x) ____; cout<<#x<<": \n"; rep_it(it,x) cout<<(*it)<<" "; cout<<endl
#define debug_map(x) ____; cout<<#x<<": \n"; rep_it(it,x) debug_pair(*it)

int TT,n,q,x,y,z,cas=0;
vi P,R;

ll kpow(ll a, ll b, ll P) {
    ll r = 1;
    for (; b; b>>=1, a = a * a % P) if (b & 1) r = r * a % P;
    return r; 
}

void ex_gcd(ll a, ll b, ll &x, ll &y){
    b ? (ex_gcd(b, a % b, y, x), y -= a / b * x) : (x = 1, y = 0);
}

inline ll Inv(ll a, ll P) {
    ll x, y; ex_gcd(a, P, x, y);
    return x < 0 ? x + P : x;
}

ll Pow(ll x,ll k,ll p) {
    ll ret=1;
    for (; k; k>>=1,x=x*x%p) if (k&1) ret=ret*x%p;
    return ret; 
}

struct Euler{
    vector<ll> c;
    inline bool check_g(ll g, ll p) {
        rep(i,0,sz(c))
            if (Pow(g, c[i], p) == 1)
                return 0;
        return 1;
    }
    inline ll getRoot(ll p) {
        c.clear();
        ll tmp=p-1,g;
        for (ll k=2; k*k<=tmp; ++k)
            if (tmp % k == 0) {
                c.pb(k);
                while (tmp % k == 0) tmp /= k;
            }
        if (tmp != 1) c.pb(tmp);
        rep(i,0,sz(c)) c[i] = (p-1) / c[i];
        for (g=1; !check_g(g,p); ++g);
        return g;
    }
} E;

const int N=1e6+4;
ll a[N],b[N],ret[N],X[N],Y[N];

typedef pair<ll,ll> pll;
struct BSGS{
    ll X[N],Y[N];
    unordered_map<ll, ll> M;
    ll solve(ll a,ll b,ll p) {
        a%=p,b%=p; ll g=__gcd(a,p);
        if (b%g) return -1;
        a/=g,b/=g,p/=g; ll x,y;
        ex_gcd(a,p,x,y);
        return (x*b%p+p)%p;
    }
//    void gcd(ll a,ll b,ll &d,ll &x,ll &y){
//        if(!b) {  d=a;  x=1;  y=0;} else{
//            gcd(b,a%b,d,y,x);
//            y-=x*(a/b);
//        }
//    }
//
//    ll solve(ll a,ll c,ll b){
//        ll d,x,y;
//        gcd(a,b,d,x,y);
//        if(c%d!=0)
//            return -1;
//        x=x*c/d;
//        b=b/d;
//        x=x-(x/b*b);
//        if(x<0)
//            x+=b;
//        return x;
//    }
    void bsgs(ll x,ll P,ll XX[],ll YY[],int tot,ll a[],ll b[]) {
        rep(i,1,tot+1) a[i]=b[i]=-1;
//        if(x % P == 0) return;
        rep(i,1,tot+1) X[i] = XX[i] % P, Y[i] = YY[i] % P;
        ll sa, t = 1, sq = 700000; M.clear();
        rep(i, 0, sq) { if (M.count(t)) break; M[t] = i, t = t * x % P; }
        t = P / sq, sa = Inv(kpow(x, sq, P), P);
        rep(j,1,tot+1) {
            rep(i, 0, t+1) if (M.count(X[j])) {
                a[j]= i * sq + M[X[j]]; break;
            } else X[j] = X[j] * sa % P;
            rep(i, 0, t+1) if (M.count(Y[j])) {
                b[j]= i * sq + M[Y[j]]; break;
            } else Y[j] = Y[j] * sa % P;
        }
    }
} T;

void bat(ll n) {
    P.clear(); R.clear();
    for (int i=2; (ll)i*i<=n; i++) {
        if (n%i) continue;
        while (n%i==0) n/=i;
        P.pb(i),R.pb(E.getRoot(i));
    }
    if (n>1) P.pb(n),R.pb(E.getRoot(n));
}

void upd(ll &x,ll y) {
    if (y==-1) return;
    if (x==-1) {
        x=y;
        return;
    }
    x=min(x,y);
}

int s[2];

int Assert(bool it) {
    if (it) return 0;
    int sum=0;
    rep(i,1,10000000) rep(j,1,100000000) sum+=i*j;
    return sum;
}

int main() {
//    file_put();
    
    scanf("%d",&TT);
    //Assert(0);
    while (TT--) {
        printf("Case #%d:\n",++cas);
        scanf("%d%d",&n,&q);
        bat(n); 
        rep(i,1,q+1) scanf("%lld%lld",&X[i],&Y[i]),ret[i]=-1;
        rep(u,0,sz(P)) {
            int p=P[u],r=R[u];
            
            T.bsgs(r,p,X,Y,q,a,b);
            rep(i,1,q+1) {
                if (a[i]==-1 || b[i]==-1) continue;
                int t=T.solve(a[i],b[i],p-1);
                upd(ret[i],t);
            }             
        }
        for (auto p:P) rep(i,1,q+1) {
            if (X[i]%p==0 && Y[i]%p==0) upd(ret[i],1);
            if (Y[i]%p==1) upd(ret[i],0);
        }
        rep(i,1,q+1) printf("%lld\n",ret[i]);
    }
    
    
    return 0;
}

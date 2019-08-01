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

void file_put() {
    freopen("filename.in", "r", stdin);
    freopen("filename.out", "w", stdout);
}

int T,n; const int N=1e6+10; ll k;
int p[N],prime[N],mu[N],top;

void init(int N){
    top = 0; mu[1] = 1;
    for (int i = 2; i <= N; ++i) {
        if (!p[i]) prime[++top] = i, mu[i] = -1;
        for (int j = 1; j <= top; ++j) {
            if (i * prime[j] > N) break;
            p[i * prime[j]] = 1;
            if (i % prime[j] == 0) break;
            mu[i * prime[j]] = -mu[i];
        }
    }
    rep(i,1,N+1) mu[i]=mu[i]+mu[i-1];
}

struct F{ __int128 p,q; };
inline F operator + (const F &a,const F &b) {
    __int128 p=a.p*b.q+b.p*a.q;
    __int128 q=a.q*b.q;
    __int128 g=__gcd(p,q);
    p/=g,q/=g;
    return F{p,q};
}
inline F operator / (const F &a,const int k) {
    __int128 p=a.p;
    __int128 q=a.q*k;
    __int128 g=__gcd(p,q);
    p/=g,q/=g;
    return F{p,q};
}
inline void print(const F &ret) {
    printf("%lld/%lld\n",(ll)ret.p,(ll)ret.q);
}

F _0{(__int128)0,(__int128)1},_1{(__int128)1,(__int128)1};

namespace SBT {
    typedef long double db;
    typedef int U;
    typedef pair<U, U> pii; 
    const U INF = 1e9 + 7;
    typedef __int128 T;
    typedef pair<T, T> V; // V = [double|long double|fraction]
    inline int cmp(const V &a, const V &b) {
        T x = a.fi * b.se - a.se * b.fi;
        return (x > 0) - (x < 0);
    }
    inline bool in(const V &a, const V &b, const V &c) {
        return 0 <= cmp(c, a) && cmp(c, b) < 0;
    }
    pii operator+(const pii &a, const pii &b) {
        return mp(a.fi + b.fi, a.se + b.se);
    }
    pii operator*(const pii &a, U x) {
        return mp(a.fi * x, a.se * x);
    }
    bool search(V v, U MAXB, pii &lo, pii &hi, int f) {
        V x;
        U l = 0, r = f > 0 ? (hi.se ? (MAXB - lo.se) / hi.se : INF) : 
            (lo.se ? (MAXB - hi.se) / lo.se : INF);
        while (l + 1 < r) {
            U z = (l + r) >> 1;
            x = f > 0 ? lo + hi * z : lo * z + hi;
            f * cmp(x, v) <= 0 ? l = z : r = z;
        }
        x = f > 0 ? lo + hi * r : lo * r + hi;
        r = f * cmp(x, v) <= 0 ? r : l;
        f > 0 ? lo = lo + hi * r : hi = lo * r + hi;
        return r > 0;
    }
    pii solve(V v, U MAXB) { // find ROUND_HALF_UP(a / b) = v, b <= MAXB
        V L = mp(v.fi * 10 - 5, v.se * 10);    
        V R = mp(v.fi * 10 + 5, v.se * 10);
        pii lo(0, 1), hi(1, 0);
        while (true) {
            bool ok = 0;
            //V m = mp(lo.fi + hi.fi, lo.se + hi.se);    
            //if (in(L, R, m)) return mp(m.fi, m.se);
            ok |= search(v, MAXB, lo, hi, 1);
            ok |= search(v, MAXB, lo, hi, -1);
            if (!ok) break;
        }
        db t1 = (db) lo.fi / lo.se; 
        db t2 = (db) hi.fi / hi.se;
        db t3 = (db) v.fi / v.se;
        return hi; 
//        if (t2 - t3 <= t3 - t1) return hi; else return lo;
        //if (in(L, R, lo)) return lo;
        //if (in(L, R, hi)) return hi;
        return mp(-1, -1);
    }
};

ll cal(ll a,ll b,ll c,ll n) { // sum_{i=0...n-1}cell((a*i+b)/c)
  if(n == 0) return 0;
  return (b/c)*n+(a/c)*n*(n-1)/2+(a%c?cal(c,(a*n+b)%c,a%c,(a%c*n+b%c)/c):0);
}

ll Count(const F &X) {
    __int128 p=X.p, q=X.q; ll ret=0;
    for (int l=1,r; l<=n; l=r+1) r=n/(n/l),ret+=cal(p,0,q,n/l+1)*(mu[r]-mu[l-1]);
    return ret;
}



int main() {
//    file_put();
    
    scanf("%d",&T),init(1000002);
    while (T--) {
        scanf("%d%lld",&n,&k);
        F L=_0,R=_1,Mid,ans=_0;
        rep(i,1,42) {
            Mid=(L+R)/2;
            if (Count(Mid)<k) ans=Mid,L=Mid; else R=Mid;
        }        
//        print(ans); de("mid");
        pair<__int128,__int128> P;
        P.fi=ans.p,P.se=ans.q;
        pair<int,int> ret=SBT::solve(P,n);
        printf("%lld/%lld\n",(ll)ret.fi,(ll)ret.se);
    }
    
    return 0;
}

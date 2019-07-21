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

ll Pow(ll x,ll k,ll p) {
    assert(k>=0);
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
} T;

const int N=1e6+5;
ll c,k1,b1,k2,a,b,g; int cas=0,tot=0; pair<ll,ll> P[N];

int main() { 
//    file_put();
    
    while (scanf("%lld%lld%lld%lld",&c,&k1,&b1,&k2)!=EOF) {
//        assert(c>=2);
        ll p=k1*k2%(c-1)+b*k2%(c-1)-k1%(c-1)+c-1; p%=c-1;
        
        ll t=__gcd(p,c-1),d=(c-1)/t; //de(t); de(d); de(c-1);
        if (d%2==0) d/=2,t*=2;
        ll g=T.getRoot(c);
//        de(g); de(k1+b);
        ll D=Pow(g,d,c); //de(D);
        tot=0;
        for (ll a=1,i=1; a<=c-1; i++,a++) {
            ll b=Pow(a,k1+b1,c)%c;
            assert(a>0); assert(b>0);
            b=c-b;assert(b>0);
//            de(a); de(b);
            if ((Pow(a,k1+b1,c)+b)%c) continue; 
            if ((Pow(a,2*k1+b1,c)+Pow(b,k2+1,c))%c) continue;
            P[++tot]=mp(a,b);
        }
//        sort(P+1,P+tot+1); //,tot=unique(P+1,P+tot+1)-P-1;
        printf("Case #%d:\n",++cas);
        rep(i,1,tot+1) printf("%lld %lld\n",P[i].fi,P[i].se);
        if (!tot) printf("-1\n");
    }

	return 0;
}


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
};

ll p; Euler E;

int main() {
    //file_put();
    
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
    
    cin>>p,cout<<E.getRoot(p)<<endl; 
	
	return 0;
}


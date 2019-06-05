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
typedef unsigned long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef double db;

void file_put() {
    freopen("filename.in", "r", stdin);
    freopen("filename.out", "w", stdout);
}

const int N=1e5+5;
int n,k,M,a[5]; vector<ll> V,E; ll ans=0,ret,x;

inline ll I(ll x,vector<ll> &V,bool op=1) {
    ll y;
    rep(i,0,sz(V)) y=V[i],x=min(x,x^y);
    if (x && op) V.pb(x); return x;
}

void dfs(int t) {
    if (t>=k) {
        E.clear();
        ll y;
        rep(j,0,sz(V)) {
            y=V[j];
            x=0;
            rep(i,0,k) x|=(y>>a[i]&1)<<i;
            I(x,E);
        }
        x=(1<<k)-1,ret=0;
        rep(i,0,k) ret+=a[i];
        if (!I(x,E,0)) ans+=1ull<<(ret-sz(E)+1);
        return;
    }
    rep(i,0,M) a[t]=i,dfs(t+1);
}

int main() {
    //file_put();
    
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	
	cin>>n>>k;
	rep(i,1,n+1) cin>>x,I(x,V);
    for (ll i=0,y; i<sz(V); ++i) y=V[i],M=max(M,64-__builtin_clzll(y));
	dfs(0);
    cout<<ans/2<<((ans&1)?".5":"")<<endl; 
	
//	cout << setiosflags(ios::fixed);
//	cout << setprecision(3);
	return 0;
}


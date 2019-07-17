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

ll get_phi(ll n) {
    ll ret=n;
    for (ll i=2; i*i<=n; i++) {
        if (n%i) continue;
        while (n%i==0) n/=i;
        ret=ret/i*(i-1);
    }
    if (n>1) ret=ret/n*(n-1); 
    return ret;
}

ll n;

int main() {
//    file_put(); 
    
    while (scanf("%lld",&n)!=EOF) printf("%lld\n",get_phi(n-1)); 
    
	return 0;
}


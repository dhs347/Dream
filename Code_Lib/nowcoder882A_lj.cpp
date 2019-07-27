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

ll ans=1; ll m,n; int T; 
const int P=1e9+7;

ll Pow(ll x,ll k) {
    ll ret=1;
    for (; k; k>>=1,x=x*x%P) if (k&1) ret=ret*x%P;
    return ret;
}

int main() {
//    file_put();
    
    scanf("%d",&T);
    while (T--) {
        scanf("%d%d",&n,&m);
        if (n==1 &&m==0) {
            printf("%lld\n",ans);
            continue;
        } 
        if (!m) {
            ans=0;
            printf("%lld\n",ans); 
            continue;
        }
        ans*=Pow(n-1,P-2),ans%=P;
        printf("%lld\n",ans);
    }
    
	return 0;
}


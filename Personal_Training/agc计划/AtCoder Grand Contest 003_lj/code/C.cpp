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

const int N=1e5+5;
int n; pii a[N]; ll ans=0;

int main() {
//    file_put();
    
    scanf("%d",&n);
    rep(i,1,n+1) scanf("%d",&a[i].fi),a[i].se=i&1;
    sort(a+1,a+n+1);
    rep(i,1,n+1) ans+=((i&1)^a[i].se);
    printf("%lld\n",ans>>1); 
    
	return 0;
}


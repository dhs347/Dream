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

const int N=2005;
const ll oo=1ll<<62;
ll a[N],x,ans=oo,ret,b[N]; int n;

int main() {
//	file_put();
	
	scanf("%d%lld",&n,&x);
	rep(i,0,n) scanf("%lld",&a[i]),b[i]=a[i];
	rep(i,0,n) {
		ret=i*x;
		rep(j,0,n) ret+=b[j];
		ans=min(ans,ret);
		rep(j,0,n) b[j]=min(b[j],a[(j+i+1)%n]);
	}
	printf("%lld\n",ans);
	
	return 0;
}


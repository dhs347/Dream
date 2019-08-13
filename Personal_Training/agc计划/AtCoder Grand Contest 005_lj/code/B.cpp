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

const int N=2e5+5;
int n,l[N],r[N],a[N],id[N]; ll ans=0;

ll count(int l,int m,int r) {
	return (ll)(r-m)*(m-l);
}

int main() {
//	file_put();
	
	scanf("%d",&n);
	rep(i,1,n+1) scanf("%d",&a[i]),id[a[i]]=i,l[i]=i-1,r[i]=i+1;
	per(i,1,n+1) ans+=(ll)i*count(l[id[i]],id[i],r[id[i]]),r[l[id[i]]]=r[id[i]],l[r[id[i]]]=l[id[i]];
	printf("%lld\n",ans);
	
	return 0;
}


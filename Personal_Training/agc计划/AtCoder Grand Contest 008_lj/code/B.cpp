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
const ll oo=1ll<<62;
int n,a[N],k; ll s[N],pre[N],suf[N],ret=-oo;;

int main() {
//	file_put();
	
	scanf("%d%d",&n,&k);
	rep(i,1,n+1) scanf("%d",&a[i]),s[i]=s[i-1]+a[i];
	rep(i,1,n+1) pre[i]=pre[i-1]+a[i]*(a[i]>0);
	per(i,1,n+1) suf[i]=suf[i+1]+a[i]*(a[i]>0);
	rep(i,1,n-k+2) ret=max(ret,pre[i-1]+suf[i+k]+max(s[i+k-1]-s[i-1],0ll));
	printf("%lld\n",ret); 
	
	return 0;
}


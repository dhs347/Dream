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

const int N=2e5+5,P=998244353;
int n,x,y; vi V[N]; ll f[N],fac[N];

void dfs(int x,int p) {
	f[x]=1;
	for (auto y:V[x]) if (y!=p) dfs(y,x),(f[x]*=f[y])%=P;
	(f[x]*=fac[sz(V[x])])%=P;
} 

int main() {
	//file_put();
	
	scanf("%d",&n),fac[0]=1;
	rep(i,1,n+3) fac[i]=fac[i-1]*i%P;
	rep(i,1,n) scanf("%d%d",&x,&y),V[x].pb(y),V[y].pb(x);
	dfs(1,0);
	printf("%lld\n",f[1]*n%P);
	
	return 0;
}


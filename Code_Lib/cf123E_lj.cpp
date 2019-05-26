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

const int N=1e6+5;
int n,sx,sy,xx[N],yy[N],siz[N],p[N],u,v; ll dp[N]; vi V[N];
double ans=0;

void dfs(int x,int f) {
	siz[x]=1,p[x]=xx[x];
	for (auto y:V[x]) if (y!=f) dfs(y,x),siz[x]+=siz[y],p[x]+=p[y];
	dp[f]+=(ll)p[x]*siz[x];
}

int main() {
	//file_put();
	
	scanf("%d",&n);
	rep(i,1,n) scanf("%d%d",&u,&v),V[u].pb(v),V[v].pb(u);
	rep(i,1,n+1) scanf("%d%d",&xx[i],&yy[i]),sx+=xx[i],sy+=yy[i];
	dfs(1,0);
	rep(i,1,n+1) dp[i]+=(ll)(n-siz[i])*(sx-p[i]);
	rep(i,1,n+1) ans+=(double)dp[i]/sx*((double)yy[i]/sy);
	printf("%.12lf\n",ans);
	
	return 0;
}

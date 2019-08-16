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
int n,X,Y,d[N],f[N],ret=0,x,y; vi R[N],B[N];

bool check(int x,int y) {
	if (!y) return 1;
	if (f[x]==y || f[y]==x) return 1;
	if (f[f[x]]==y || f[f[y]]==x) return 1;
	return f[x]==f[y];
}

void dfs(int x,int p) {
	d[x]=d[p]+1,f[x]=p;
	for (auto y: B[x]) if (y!=p) dfs(y,x);
}

void dfs(int x,int p,int k) {
	ret=max(ret,d[x]);
	for (auto y: R[x]) if (y!=p) {
		if (!check(x,y)) {
			printf("-1\n");
			exit(0);
		}
		if (d[y]>k+1) dfs(y,x,k+1);
	}
}

int main() {
//	file_put();
	
	scanf("%d%d%d",&n,&X,&Y),d[0]=-1;
	rep(i,1,n) scanf("%d%d",&x,&y),R[x].pb(y),R[y].pb(x);
	rep(i,1,n) scanf("%d%d",&x,&y),B[x].pb(y),B[y].pb(x);
	dfs(Y,0),dfs(X,0,0);
	printf("%d\n",ret<<1);
	
	return 0;
}


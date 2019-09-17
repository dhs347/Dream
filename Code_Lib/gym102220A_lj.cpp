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
int T,n,m,a[N],u,v,c,w,siz[N],len[N],tmp[N]; vector<ll> f[N],g[N]; ll ans=0;
struct node{ int u,v,c,w; } P[N];
inline bool operator < (const node &a, const node &b) { return a.w>b.w; }
inline int G(int x,int y) {
	int k=1<<(len[y]-len[x]);
	return k|(y&(k-1));
}

void dfs(int u,int x,int y) {
	if (x>n) return;
	tmp[y]=a[x],siz[u]++;
	dfs(u,x<<1,y<<1),dfs(u,x<<1|1,y<<1|1);
}

void add(int u,int v,int c,int w) {
	for (int x=u; x; x>>=1) {
		int m=siz[x],no=G(x,v); ll ret=f[x][no];
		for (int y=no>>1; y; y>>=1,no>>=1) {
			ret+=g[x][y];
			if ((y<<1)<=m && (y<<1)!=no) ret+=min(f[x][y<<1],0ll);
			if ((y<<1|1)<=m && (y<<1|1)!=no) ret+=min(f[x][y<<1|1],0ll);
		}
		c=min(1ll*c,ret);
	}
	if (!c) return;
	ans+=(ll)c*w;
	for (int x=u; x; x>>=1) {
		int m=siz[x],no=G(x,v);
		f[x][no]-=c,g[x][no]-=c;
		for (int y=no>>1; y; y>>=1) {
			f[x][y]=g[x][y];
			if ((y<<1)<=m) f[x][y]+=min(f[x][y<<1],0ll);
			if ((y<<1|1)<=m) f[x][y]+=min(f[x][y<<1|1],0ll);
		}
	}
}

int main() {
	//file_put();
	
	scanf("%d",&T);
	rep(i,1,N) len[i]=len[i>>1]+1;
	while (T--) {
		scanf("%d%d",&n,&m);
		rep(i,1,n+1) scanf("%d",&a[i]);
		rep(i,1,m+1) scanf("%d%d%d%d",&u,&v,&c,&w),P[i]=node{u,v,c,w};
		sort(P+1,P+m+1);
		rep(i,1,n+1) {
			siz[i]=0;
			dfs(i,i,1);
			f[i].resize(siz[i]+1),g[i].resize(siz[i]+1);
			rep(j,1,siz[i]+1) f[i][j]=g[i][j]=tmp[j]; 
		}
		ans=0;
		rep(i,1,m+1) add(P[i].u,P[i].v,P[i].c,P[i].w);
		printf("%lld\n",ans);
	}
	
	return 0;
}


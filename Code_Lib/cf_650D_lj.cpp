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

const int N=1e6+5,oo=2e9;
int n,m,a[N],x,y,p[N],f[N],g[N],ff[N],gg[N],L=0,M,ret[N]; vector<pii> V[N]; bool ok[N],yes[N],yes2[N];

int main() {
	//file_put();
	
	scanf("%d%d",&n,&m);
	rep(i,1,n+1) scanf("%d",&a[i]);
	rep(i,1,m+1) scanf("%d%d",&x,&y),V[x].pb(mp(y,i));
	p[0]=0;
	rep(i,1,n+5) p[i]=oo;
	rep(i,1,n+1) {
		for (auto t:V[i]) {
			int x=t.fi,id=t.se;
			f[id]=lower_bound(p,p+n+3,x)-p;
		}
		ff[i]=lower_bound(p,p+n+3,a[i])-p;
		p[ff[i]]=a[i],L=max(L,ff[i]);
	}
	p[0]=-oo;
	rep(i,1,n+5) p[i]=0;
	per(i,1,n+1) {
		for (auto t:V[i]) {
			int x=t.fi,id=t.se;
			g[id]=lower_bound(p,p+n+3,-x)-p;
		}
		gg[i]=lower_bound(p,p+n+3,-a[i])-p;
		p[gg[i]]=-a[i];
	}
	rep(i,1,n+1) ok[i]=(ff[i]+gg[i]-1==L);
	M=0;
	rep(i,1,n+1) {
		if (!ok[i]) continue;
		yes[i]=(M<a[i]);
		M=max(M,a[i]);
	}
	M=oo;
	per(i,1,n+1) {
		if (!ok[i]) continue;
		yes2[i]=(M>a[i]);
		M=min(M,a[i]);
	}
	rep(i,1,n+1) yes[i]&=yes2[i];
	rep(i,1,n+1) for (auto t:V[i]) {
		int x=t.fi,id=t.se;
		ret[id]=max(f[id]+g[id]-1,L-yes[i]);
	}
	rep(i,1,m+1) printf("%d\n",ret[i]);
	
	return 0;
}


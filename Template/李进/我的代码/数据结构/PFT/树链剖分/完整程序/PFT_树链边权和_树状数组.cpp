# include <iostream>
# include <sstream>
# include <cstdio>
# include <cstdlib>
# include <algorithm>
# include <string>
# include <cstring>
# include <cmath>
# include <stack>
# include <queue>
# include <vector>
# include <list>
# include <map>
# include <set>
# include <deque>
# include <iterator>
# include <functional>
# include <bitset>
# include <climits>
# include <ctime>
using namespace std;
#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))
#define odd(x) ((x)&1)
#define sqr(x) ((x)*(x))
#define mp make_pair
#define pb push_back
#define fir first
#define sec second
#define all(x) (x).begin(),(x).end()
#define mem(a,x) memset(a,x,sizeof(a))
#define rep(i,a,b) for (int i=(a); i<=(b); ++i)
#define per(i,a,b) for (int i=(a); i>=(b); --i)
#define rep_it(it,x) for (__typeof((x).begin()) it=(x).begin(); it!=(x).end(); it++)
#define ____ puts("\n_______________\n\n")
#define debug(x) ____; cout<< #x << " => " << (x) << endl
#define debug_pair(x) cout<<"\n{ "<<(x).fir<<" , "<<(x).sec<<" }\n"
#define debug_arr(x,n) ____; cout<<#x<<":\n"; rep(i,0,n) cout<<#x<<"["<<(i)<<"] => "<<x[i]<<endl
#define debug_arr2(x,n,m) ____; cout<<#x<<":\n"; rep(i,0,n) rep(j,0,m) cout<<#x<<"["<<(i)<<"]["<<(j)<<"]= "<<x[i][j]<<((j==m)?"\n\n":"    ")
#define debug_set(x) ____; cout<<#x<<": \n"; rep_it(it,x) cout<<(*it)<<" "; cout<<endl
#define debug_map(x) ____; cout<<#x<<": \n"; rep_it(it,x) debug_pair(*it)
typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef vector<int> vi;
const int oo = /*2 * 1000 * 1000 * 1000*/0x3f3f3f3f;
const ll ooo=9223372036854775807ll;
const int _cnt = 1000 * 1000 + 7;
const int _p = 1000 * 1000 * 1000 + 7;
const int N=100005;
const double PI=acos(-1.0);
const double eps=1e-9;
int o(int x) { return x%_p; }
int gcd(int a, int b) { return b ? gcd(b, a%b) : a; }
int lcm(int a, int b) { return a / gcd(a, b)*b; }

void file_put() {
    freopen("filename.in", "r", stdin);
    freopen("filename.out", "w", stdout);
}

struct BIT{
	ll c[N],cc[N],s[N]; int n;
	void Init(int _n,ll a[]=NULL) { mem(s,0); mem(c,0); mem(cc,0); n=_n; if (a!=NULL) rep(i,1,n) s[i]=s[i-1]+a[i]; }
	ll Q(ll a[],int k) { ll ans=0; for ( ; k; k-=(k&(-k))) ans+=a[k]; return ans; }
	void U(ll a[],int k,ll x) {  for ( ; k<=n; k+=(k&(-k))) a[k]+=x;  }
	ll Query(int l,int r) { return s[r]-s[l-1]+(r+1)*Q(c,r)-Q(cc,r)-l*Q(c,l-1)+Q(cc,l-1); }
	void Update(int l,int r,ll x) { U(c,l,x); U(c,r+1,-x); U(cc,l,l*x); U(cc,r+1,-(r+1)*x); }
}; 

struct PFT{
	int s[N],top[N],son[N],dep[N],id[N],no[N],f[N];
	int head[N],to[2*N],next[2*N],n,m,cnt;
	ll num[N],a[N],w[2*N]; BIT T;
	void Init(){
		mem(head,-1); mem(son,-1); mem(next,-1);
		mem(num,0); m=cnt=n=0;
	}
	void addedge(int u,int v,ll c) { to[m]=v,w[m]=c,next[m]=head[u],head[u]=m++; }
	void dfs1(int u,int fa,int d){
		dep[u]=d; f[u]=fa; s[u]=1;
		for (int i=head[u]; ~i; i=next[i]) {
			int v=to[i];
			if (v==fa) continue;
			dfs1(v,u,d+1);
			s[u]+=s[v];
			if (son[u]==-1 || s[v]>s[son[u]]) son[u]=v;
		}
	}
	void dfs2(int u,int _top) {
		top[u]=_top; id[u]=++cnt; no[id[u]]=u;
		if (son[u]==-1) return;
		dfs2(son[u],_top);
		for (int i=head[u]; ~i; i=next[i]) {
			int v=to[i];
			if (v!=son[u] && v!=f[u]) dfs2(v,v);
		}
	}
    void edge_init(){
        rep(u,1,n) {
            for (int i=head[u]; ~i; i=next[i]) {
                int v=to[i],t=(dep[u]>dep[v])?u:v;
                if (!num[t]) num[t]=w[i];
            }
        }
    }
	void Build(int _n) {
		n=_n; dfs1(1,0,0); dfs2(1,1); edge_init();
		rep(i,1,n) a[id[i]]=num[i]; T.Init(n,a);
	}
	void Update(int x,int y,ll v){
		while (top[x]!=top[y]){
			if (dep[top[x]]<dep[top[y]]) swap(x,y);
			T.Update(id[top[x]],id[x],v);
			x=f[top[x]];
		}
		if (x==y) return;
		if (dep[x]>dep[y]) swap(x,y);
		T.Update(id[son[x]],id[y],v);
	}
	ll Query(int x,int y) {
		ll ret=0;
		while (top[x]!=top[y]) {
			if (dep[top[x]]<dep[top[y]]) swap(x,y);
			ret+=T.Query(id[top[x]],id[x]);
			x=f[top[x]];
		}
		if (x==y) return ret;
		if (dep[x]>dep[y]) swap(x,y);
		return ret+T.Query(id[son[x]],id[y]);
	}
};

PFT T;
string st;
int a,b,n,m,Q;
ll c;

int main() {
    //file_put();

    while (scanf("%d%d",&n,&Q)!=EOF) {
    	T.Init();
    	rep(i,1,n-1) {
    		scanf("%d%d%I64d",&a,&b,&c);
			T.addedge(a,b,c); T.addedge(b,a,c);
		}
		T.Build(n);
		while (Q--) {
			cin>>st;
			if (st[0]=='1') {
				scanf("%d%d",&a,&b);
				printf("%I64d\n",T.Query(a,b));
			} else {
				scanf("%d%I64d",&a,&c);
                int x=T.to[2*a-2],y=T.to[2*a-1];
                ll t=T.Query(x,y);
				T.Update(x,y,-t+c);
			}
		}
	}

    return 0;
}

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
//#define max(a,b) ((a)>(b)?(a):(b))
//#define min(a,b) ((a)<(b)?(a):(b))
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
    ll c[N],a[N],t; int n;
    void Init(int _n,ll x[]=NULL) { 
		mem(c,0); mem(a,0); n=_n; 
		if (x!=NULL) rep(i,1,n) Update(i,x[i]);
	}
    void Update(int k,ll x){
        a[k]=x;
        for ( ; k<=n; k+=(k&(-k))) {
            c[k]=a[k],t=(k&(-k));
            for (int i=1; i<t; i<<=1) c[k]=max(c[k],c[k-i]);
        }
    }
    ll Query(int l,int r) {
        ll ans=0;
        while (r>=l) {
            ans=max(a[r],ans); r--;
            for (; r-(r&(-r))>=l; r-=(r&(-r))) ans=max(ans,c[r]);
        }
        return ans;
    }
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
			T.Update(id[x],v);
			x=f[top[x]];
		}
		if (x==y) return;
		if (dep[x]>dep[y]) swap(x,y);
		T.Update(id[y],v);
	}
	ll Query(int x,int y) {
		ll ret=0;
		while (top[x]!=top[y]) {
			if (dep[top[x]]<dep[top[y]]) swap(x,y);
			ret=max(ret,T.Query(id[top[x]],id[x]));
			x=f[top[x]];
		}
		if (x==y) return ret;
		if (dep[x]>dep[y]) swap(x,y);
		return max(ret,T.Query(id[son[x]],id[y]));
	}
};

PFT T;
string st;
int a,b,n,m,Q;
ll c;
int _T;

int main() {
    //file_put();

	scanf("%d",&_T);
    while (_T--) {
    	scanf("%d",&n);
    	T.Init();
    	rep(i,1,n-1) {
    		scanf("%d%d%I64d",&a,&b,&c);
			T.addedge(a,b,c); T.addedge(b,a,c);
		}
		T.Build(n);
		while (1) {
			cin>>st;
			if (st[0]=='Q') {
				scanf("%d%d",&a,&b);
				printf("%I64d\n",T.Query(a,b));
			} else 
			if (st[0]=='C'){
				scanf("%d%I64d",&a,&c);
                int x=T.to[2*a-2],y=T.to[2*a-1];
				T.Update(x,y,c);
			} else 
				break;
		}
	}

    return 0;
}


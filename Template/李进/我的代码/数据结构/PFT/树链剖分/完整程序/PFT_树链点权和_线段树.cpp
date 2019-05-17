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

struct Seg_T{
    #define lson l,mid,rt<<1
    #define rson mid+1,r,rt<<1|1
	int n,L,R; ll s[4*N],lazy[4*N],*a,v;
	void push_up(int rt){ s[rt]=s[rt<<1]+s[rt<<1|1]; }
	void push_down(int rt,int m) {
		if (!lazy[rt]) return;
		lazy[rt<<1]+=lazy[rt];
        lazy[rt<<1|1]+=lazy[rt];
        s[rt<<1]+=(m-(m>>1))*lazy[rt];
        s[rt<<1|1]+=(m>>1)*lazy[rt];
        lazy[rt]=0;
	}
	void B(int l,int r,int rt) {
		lazy[rt]=0;
		if (l==r) { s[rt]=a[l]; return; }
		int mid=(l+r)>>1;
    	B(lson); B(rson); push_up(rt);
	}
	void Init(int _n,ll _a[]=NULL){
        n=_n; if (_a==NULL) { mem(s,0); mem(lazy,0); return ; }
        a=_a; B(1,n,1);
	}
    void U(int l,int r,int rt){
        if (L<=l && r<=R) { lazy[rt]+=v; s[rt]+=v*(r-l+1); return; }
        push_down(rt,r-l+1);
        int mid=(l+r)>>1;
        if (L<=mid) U(lson);
        if (R>mid) U(rson);
        push_up(rt);
    }
    ll Q(int l,int r,int rt) {
        if (L<=l && r<=R) return s[rt];
        push_down(rt,r-l+1);
        int mid=(l+r)>>1; ll ret=0;
        if (L<=mid) ret+=Q(lson);
		if (R>mid) ret+=Q(rson);
        push_up(rt);
        return ret;
    }
    void Update(int _L,int _R,ll _v){ L=_L,R=_R,v=_v; U(1,n,1); }
    ll Query(int _L,int _R) { L=_L,R=_R; return Q(1,n,1); }
};

struct PFT{
	int s[N],top[N],son[N],dep[N],id[N],no[N],f[N];
	int head[N],to[2*N],next[2*N],n,m,cnt;
	ll num[N],a[N]; Seg_T T;
	void Init(){
		mem(head,-1); mem(son,-1); mem(next,-1); 
		mem(num,0); m=cnt=n=0;
	}
	void addedge(int u,int v) { to[m]=v,next[m]=head[u],head[u]=m++; }
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
	void Build(int _n) {
		n=_n; dfs1(1,0,0); dfs2(1,1);
		rep(i,1,n) a[id[i]]=num[i]; T.Init(n,a);
	}
	void Update(int x,int y,ll v){
		while (top[x]!=top[y]){
			if (dep[top[x]]<dep[top[y]]) swap(x,y);
			T.Update(id[top[x]],id[x],v);
			x=f[top[x]];
		}
		if (dep[x]>dep[y]) swap(x,y);
		T.Update(id[x],id[y],v);
	}
	ll Query(int x,int y) {
		ll ret=0;
		while (top[x]!=top[y]) {
			if (dep[top[x]]<dep[top[y]]) swap(x,y);
			ret+=T.Query(id[top[x]],id[x]);
			x=f[top[x]];
		}
		if (dep[x]>dep[y]) swap(x,y);
		return ret+T.Query(id[x],id[y]);
	}
};

PFT T;
string st;
int a,b,n,m,Q;
ll c;

int main() {
    file_put();
    
    while (scanf("%d%d%d",&n,&m,&Q)!=EOF) {
    	T.Init();
    	rep(i,1,n) scanf("%I64d",&T.num[i]);
    	rep(i,1,m) {
    		scanf("%d%d",&a,&b);
			T.addedge(a,b); T.addedge(b,a); 
		}
		T.Build(n);
		while (Q--) {
			cin>>st;
			if (st[0]=='Q') {
				scanf("%d",&a);
				printf("%I64d\n",T.Query(a,a));
			} else {
				scanf("%d%d%I64d",&a,&b,&c);
				if (st[0]=='D') c=-c;
				T.Update(a,b,c);
			}
		}
	}

    return 0;
}

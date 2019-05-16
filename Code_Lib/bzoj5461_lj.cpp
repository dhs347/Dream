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

const int N=3e5+5,M=N*25+5,_p=998244353,_10=796898467;
struct node{ int ls,rs,v,tag; } t[M]; 
struct ttype{ int x,id; } tmp[N];
inline bool operator < (const ttype &a,const ttype &b) { return a.x<b.x; }
int n,p[N],x,cnt=0,tot=0,rt[N],sa,sb; vi V[N]; ll no=0,ans=0;

inline int mul(int x,int y) { return (ll)x*y%_p; }
inline int add(int x,int y) { return ((ll)x+y)%_p; } 
inline int mul(vi V) {
    int ret=1;
    for (int i=0; i<sz(V); ++i) ret=mul(ret,V[i]);
    return ret;
}

void Insert(int &x,int l,int r,int v) {
	x=++tot,t[x].v=t[x].tag=1;
    if (l==r) return;
    int mid=l+r>>1;
    if (v<=mid) Insert(t[x].ls,l,mid,v); else Insert(t[x].rs,mid+1,r,v);
}

inline void push_up(int x) {
    t[x].v=add(t[t[x].ls].v,t[t[x].rs].v);
}

inline void pd(int x,int c) {
    if (!x) return;
    t[x].tag=mul(t[x].tag,c);
    t[x].v=mul(t[x].v,c);
}

inline void push_down(int x) {
    if (!x) return;
    if (t[x].tag<0) t[x].tag+=_p;
    if (t[x].tag==1) return;
    pd(t[x].ls,t[x].tag);
    pd(t[x].rs,t[x].tag);
    t[x].tag=1;
}

int Merge(int x,int y,int p) {
    if (!x && !y) return 0;
    if (!x) {
        sb=add(sb,t[y].v);
        pd(y,(add(sa,p)-2ll*mul(sa,p))%_p);
        return y;
    }
    if (!y) {
        sa=add(sa,t[x].v);
        pd(x,(add(sb,p)-2ll*mul(sb,p))%_p);
        return x;
    }
    push_down(x),push_down(y);
    t[x].rs=Merge(t[x].rs,t[y].rs,p);
    t[x].ls=Merge(t[x].ls,t[y].ls,p);
    push_up(x);
    return x;
}

void dfs(int x) {
    if (V[x].empty()) return;
    if (sz(V[x])==1) { dfs(V[x][0]),rt[x]=rt[V[x][0]]; return; }
    dfs(V[x][0]),dfs(V[x][1]);
    sa=sb=0;
    rt[x]=Merge(rt[V[x][0]],rt[V[x][1]],p[x]);
}

void Query(int x,int l,int r) {
    if (!x || !t[x].v) return;
    if (l==r) {
        ++no;
        ans+=mul(mul(no,tmp[l].x),mul(t[x].v,t[x].v)),ans%=_p;
        return;
    }
    push_down(x);
    int mid=l+r>>1;
    Query(t[x].ls,l,mid);
    Query(t[x].rs,mid+1,r);
}

int main() {
    //file_put();
    
	scanf("%d",&n);
	rep(i,1,n+1) scanf("%d",&x),V[x].pb(i);
	rep(i,1,n+1) {
		scanf("%d",&x);
		if (V[i].empty()) tmp[++cnt]=ttype{x,i}; else p[i]=mul(x,_10);
	}
	sort(tmp+1,tmp+cnt+1);
	rep(i,1,cnt+1) Insert(rt[tmp[i].id],1,cnt,i);
	dfs(1),Query(rt[1],1,cnt);
	printf("%lld\n",ans);
	
	return 0;
}


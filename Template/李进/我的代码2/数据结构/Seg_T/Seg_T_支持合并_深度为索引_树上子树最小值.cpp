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

struct Seg_T{
	int rt[N],ls[N<<6],rs[N<<6],v[N<<6],cnt,L,R,pos,x,m;
	void Init(int _m) { v[cnt=0]=oo; m=_m; }
	void push_up(int t) { v[t]=min(v[ls[t]],v[rs[t]]); }
	int new_node(int p=0,int q=0,int x=oo) { ls[++cnt]=p,rs[cnt]=q,v[cnt]=x; return cnt; }
	void U(int &t,int l,int r) {
		if (!t) t=new_node();
		if (l==r) { v[t]=x; return; }
		int mid=(l+r)>>1;
		if (pos<=mid) U(ls[t],l,mid); else U(rs[t],mid+1,r);
		push_up(t); 
	}
	int M(int a,int b){
		if (!a || !b) return a+b;
		int c=new_node(M(ls[a],ls[b]),M(rs[a],rs[b]),min(v[a],v[b]));
		if (ls[c] || rs[c]) push_up(c); return c;
	} 
	int Q(int t,int l,int r) {
		if (L<=l && r<=R) return v[t];
		int mid=(l+r)>>1; int ans=oo;
		if (L<=mid) ans=min(ans,Q(ls[t],l,mid));
		if (R>mid) ans=min(ans,Q(rs[t],mid+1,r));
		return ans;
	}
	void Update(int &t,int _pos,int _x) { pos=_pos,x=_x,U(t,1,m); }
	int Query(int &t,int l,int r) { L=l,R=r; return Q(t,1,m); }
}; 

vector<int> V[N];
int dep[N],a[N],x,y,tt,n,r,last=0;
Seg_T T;

void dfs(int x,int p){
	dep[x]=dep[p]+1;
	T.Update(T.rt[x],dep[x],a[x]);
	for (int i=0; i<V[x].size(); i++) {
		if (V[x][i]==p) continue;
		dfs(V[x][i],x);
		T.rt[x]=T.M(T.rt[x],T.rt[V[x][i]]);
	}
}

int main() {
    //file_put();
    
    scanf("%d%d",&n,&r);
    T.Init(n);
    rep(i,1,n) scanf("%d",&a[i]);
    rep(i,1,n-1) {
    	scanf("%d%d",&x,&y);
    	V[x].push_back(y); V[y].push_back(x);
	}
	dfs(r,0);
	scanf("%d",&tt);
	while (tt--) {
		scanf("%d%d",&x,&y);
		x=(x+last)%n+1;
		y=(y+last)%n;
		printf("%d\n",last=T.Query(T.rt[x],dep[x],dep[x]+y)); 
	}
    
    return 0;
}

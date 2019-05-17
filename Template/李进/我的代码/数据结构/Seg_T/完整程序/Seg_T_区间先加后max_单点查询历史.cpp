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
const int oo = (1e9);
const ll ooo = (1e18); 
const int _cnt = 1000 * 1000 + 7;
const int _p = 1000 * 1000 * 1000 + 7;
const int N=600005; 
const double PI=acos(-1.0);
const double eps=1e-9;
int o(int x) { return x%_p; }
int gcd(int a, int b) { return b ? gcd(b, a%b) : a; }
int lcm(int a, int b) { return a / gcd(a, b)*b; }

void file_put() {
    freopen("filename.in", "r", stdin);
    freopen("filename.out", "w", stdout);
}

typedef pair<ll,ll> pll;
#define x first
#define y second
#define mid ((l+r)>>1)
inline pll operator+(const pll &A,const pll &B){ return pll(max(A.x+B.x,-ooo),max(A.y+B.x,B.y)); }
inline pll max(const pll &A,const pll &B) { return pll(max(A.x,B.x),max(A.y,B.y)); }
struct Seg_T{
	pll now[N<<2],ever[N<<2],v; int L,R,opt,n; ll *a;
	inline void pd(int t,int f) { ever[t]=max(ever[t],now[t]+ever[f]); now[t]=now[t]+now[f]; }
	inline void push_down(int t) { pd(t<<1,t),pd(t<<1|1,t),now[t]=ever[t]=pll(0,0); }
	void B(int t,int l,int r) {
		if (l==r) { ever[t]=now[t]=pll(a[l],-oo); return; }
		now[t]=ever[t]=pll(0,0); B(t<<1,l,mid); B(t<<1|1,mid+1,r);
	}
	void update(int t,int l,int r){
		if (L<=l && r<=R) { now[t]=now[t]+v; ever[t]=max(ever[t],now[t]); return; }
		push_down(t);  if (L<=mid) update(t<<1,l,mid); if (R>mid) update(t<<1|1,mid+1,r);
	}
	ll query(int t,int l,int r) {
		if (l==r) return (opt==1)?max(now[t].x,now[t].y):max(ever[t].x,ever[t].y);
		push_down(t); if (L<=mid) return query(t<<1,l,mid); else query(t<<1|1,mid+1,r);
	}
	inline void Init(int _n,ll *_a) { n=_n,a=_a,B(1,1,n); }
	inline void Update(int l,int r,const pll &_v) { L=l,R=r,v=_v; update(1,1,n); }//v表示元素先+x,再对y取max 
	inline ll Query(int pos,int _opt) { L=pos,opt=_opt; return query(1,1,n); }//单点查询，opt==1为现在的值 
}; 
#undef x 
#undef y

int n,m,l,r,pos,opt;
Seg_T T;
ll a[N],x;

int main() {
    //file_put();
    
    scanf("%d%d",&n,&m);
    rep(i,1,n) scanf("%I64d\n",&a[i]);
	T.Init(n,a); 
	while (m--) {
		scanf("%d",&opt);
		if (opt>3) {
			scanf("%d",&pos);
			printf("%lld\n",T.Query(pos,opt==4));
			continue;
		}
		scanf("%d%d%lld",&l,&r,&x);
		if (opt==1) T.Update(l,r,pll(x,-ooo));
		if (opt==2) T.Update(l,r,pll(-x,0)); 
		if (opt==3) T.Update(l,r,pll(-ooo,x));
	}
	
    return 0;
}

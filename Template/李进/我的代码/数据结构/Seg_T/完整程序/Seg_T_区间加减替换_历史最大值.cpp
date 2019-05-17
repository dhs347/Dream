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

struct Seg_T{
	int n,L,R,opt; ll *a,mx[N<<2],add[N<<2],cover[N<<2],_mx[N<<2],_add[N<<2],_cover[N<<2],x;
	inline void push_up(int t) {
		mx[t]=max(mx[t<<1],mx[t<<1|1]);
		_mx[t]=max(_mx[t<<1],_mx[t<<1|1]);
	}
	inline void pd(int t,int f){
		_mx[t]=max(_mx[t],max(_cover[f],mx[t]+_add[f]));
		if (cover[t]==-oo) _add[t]=max(_add[t],add[t]+_add[f]);
		else _cover[t]=max(_cover[t],cover[t]+_add[f]);
		if (add[f]) {
			if (cover[t]!=-oo) cover[t]+=add[f]; else add[t]+=add[f];
			mx[t]+=add[f];
		}
		if (cover[f]!=-oo) mx[t]=cover[t]=cover[f],add[t]=0;
		_cover[t]=max(_cover[t],max(cover[t],_cover[f]));
		_add[t]=max(_add[t],add[t]);
	}
	inline void push_down(int t) {
		pd(t<<1,t),pd(t<<1|1,t);
		add[t]=_add[t]=0; cover[t]=_cover[t]=-oo;
	}
	void B(int t,int l,int r) {
		add[t]=_add[t]=0,cover[t]=_cover[t]=-oo;
		if (l==r) { mx[t]=_mx[t]=a[l]; return; }
		int mid=(l+r)>>1; B(t<<1,l,mid); B(t<<1|1,mid+1,r); push_up(t);
	}
	void update(int t,int l,int r){
		if (l!=r) push_down(t); int mid=(l+r)>>1;
		if (L<=l && r<=R) {
			if (opt==0) mx[t]+=x,add[t]+=x,_add[t]+=x;
			if (opt==1) cover[t]=_cover[t]=mx[t]=x;
			_mx[t]=max(_mx[t],mx[t]); return ;
		}
		if (L<=mid) update(t<<1,l,mid);
		if (R>mid) update(t<<1|1,mid+1,r); push_up(t);
	}
	ll query(int t,int l,int r) {
		if (l!=r) push_down(t);
		int mid=(l+r)>>1; ll ans=-oo;
		if (L<=l && r<=R) return (opt?_mx[t]:mx[t]);
		if (L<=mid) ans=max(ans,query(t<<1,l,mid));
		if (R>mid) ans=max(ans,query(t<<1|1,mid+1,r)); return ans;
	}
	inline void Update(int l,int r,ll _x,int _opt) { L=l,R=r,x=_x,opt=_opt; update(1,1,n); }
	inline ll Query(int l,int r,int _opt) { L=l,R=r,opt=_opt; return query(1,1,n); }
	inline void Init(int _n,ll *_a) { n=_n,a=_a; B(1,1,n); }
}; 

Seg_T T;
ll a[N],x;
int n,m,l,r;
char p;

int main() {
    //file_put();
    
    scanf("%d",&n);
    rep(i,1,n) scanf("%lld",&a[i]);
    T.Init(n,a);
    scanf("%d",&m);
	rep(i,1,m) {
		p=' ';
		while (p!='Q' && p!='A' && p!='C' && p!='P') scanf("%c",&p);
		scanf("%d%d",&l,&r);
		//debug(p);
		if (p=='Q') printf("%lld\n",T.Query(l,r,0)); else
		if (p=='A') printf("%lld\n",T.Query(l,r,1)); else
		if (p=='P') {
			scanf("%lld",&x);
			T.Update(l,r,x,0); 
		} else
		if (p=='C') {
			scanf("%lld",&x);
			T.Update(l,r,x,1);
		}
	} 
	
    return 0;
}

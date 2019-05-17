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
const int N=1000005; 
const double PI=acos(-1.0);
const double eps=1e-9;
int o(int x) { return x%_p; }
int gcd(int a, int b) { return b ? gcd(b, a%b) : a; }
int lcm(int a, int b) { return a / gcd(a, b)*b; }

void file_put() {
    freopen("filename.in", "r", stdin);
    freopen("filename.out", "w", stdout);
}

int k;

struct ST{
	int n,log[N],dp[25][N]; int *a;
	int h(int x,int y) { return a[x]<=a[y] ? x:y; }
	void Init(int _n,int *_a){
		n=_n,a=_a,log[0]=-1; rep(i,1,n) log[i]=log[i>>1]+1,dp[0][i]=i;
		rep(i,1,log[n]) rep(j,1,n+1-(1<<i)) dp[i][j]=h(dp[i-1][j],dp[i-1][j+(1<<(i-1))]);
	}
	int Q(int l,int r) { int L=log[r-l+1]; return h(dp[L][l],dp[L][r+1-(1<<L)]); }
}; 

struct SA{
	int t1[N],t2[N],cc[N],x[N],sa[N],R[N],H[N],h[N],n,m,cnt,str_cnt; int *s; ST T;
	inline bool cmp(int *y,int a,int b,int k){
		return y[a]==y[b] && (a+k>=n ? -1:y[a+k])==(b+k>=n ? -1:y[b+k]);
	}
	inline void init_sa() {
		int *x=t1,*y=t2;
		rep(i,0,m-1) cc[i]=0;
		rep(i,0,n-1) ++cc[x[i]=s[i]];
		rep(i,1,m-1) cc[i]+=cc[i-1];
		per(i,n-1,0) sa[--cc[x[i]]]=i;
		for(int k=1,p=0; k<=n; k<<=1,p=0){
			rep(i,n-k,n-1) y[p++]=i;
			rep(i,0,n-1) if(sa[i]>=k) y[p++]=sa[i]-k;
			rep(i,0,m-1) cc[i]=0;
			rep(i,0,n-1) ++cc[x[y[i]]];
			rep(i,1,m-1) cc[i]+=cc[i-1];
			per(i,n-1,0) sa[--cc[x[y[i]]]]=y[i];
			swap(x,y),m=1,x[sa[0]]=0;
			rep(i,1,n-1) x[sa[i]]=cmp(y,sa[i],sa[i-1],k) ? m-1:m++;
			if(m>=n) break;
		}
	}
	inline void init_H(){
		rep(i,0,n-1) R[sa[i]]=i;
		int k=H[0]=0;
		rep(i,0,n-1) {
			if (!R[i]) continue;
			int j=sa[R[i]-1];
			if (k) k--;
			while (s[i+k]==s[j+k]) k++;
			h[i]=H[R[i]]=k;
		}
	}
	inline int Q_lcp(int x,int y) {
		if (R[x]>R[y]) swap(x,y);
		return x==y ? n-x : H[T.Q(R[x]+1,R[y])];
	}
	inline void divide_group(int k,int x[]) {
		x[0]=cnt=0; rep(i,1,n-1) if (H[i]<k) x[++cnt]=i; x[++cnt]=n;
	}
	inline bool check_group(int l,int r,int ans) {
		//...
		if (r-l+1>=k) return true; return false;
	}
	inline bool check(int ans){
		divide_group(ans,x);
		rep(i,1,cnt) if (check_group(x[i-1],x[i]-1,ans)) return true; return false;
	}
	inline int binary(int l,int r) {
		int ans,mid;
		while (l<=r) {
			mid=(l+r)>>1;
			if (check(mid)) {
				ans=mid;
				l=mid+1;
			} else r=mid-1;
		}
		return ans;
	}
	inline ll Q(){
		//...
		ll ans=(ll)n*(n+1)/2;
		rep(i,1,n-1) ans-=H[i];
		return ans;
	}
	inline void Insert(int _s[],int op=0,int _n=0){
		if (n) s[n++]=300+str_cnt+1; ++str_cnt;
		if (!op) rep(i,0,_n-1) s[n++]=_s[i]; else
				 per(i,_n-1,0) s[n++]=_s[i];
	}
	//SA(){ s=new int[N]; n=str_cnt=0; }
	inline void Init(int _s[]=NULL,int _n=0,int _m=1000){
		if (_s!=NULL) s=_s,n=_n;  m=_m;
		init_sa(); init_H(); //T.Init(n-1,H);
	}
};

SA T;
char s[N];
int a[N],_T;
int len,q,x,y,n;

int main() {
    //file_put();
    
    scanf("%d",&_T);
    while (_T--) {
    	scanf("%s",s);
    	n=strlen(s);
    	rep(i,0,n-1) a[i]=s[i];
    	T.Init(a,n,300);
    	printf("%I64d\n",T.Q()); 
	}
    
    return 0;
}

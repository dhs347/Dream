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
const int N=200103; 
const double PI=acos(-1.0);
const double eps=1e-9;
int o(int x) { return x%_p; }
int gcd(int a, int b) { return b ? gcd(b, a%b) : a; }
int lcm(int a, int b) { return a / gcd(a, b)*b; }

void file_put() {
    freopen("filename.in", "r", stdin);
    freopen("filename.out", "w", stdout);
}

ll ans=0,s1,s2;
int p[N],q[N],n1[N],n2[N],c1,c2;
//p,q分别为1，2的两个帮派（阵营）的单调栈，n1[],n2[]为对应下标的元素个数,n1[i]表示p[i]的重复个数
//c0表示单调栈的栈顶指针（闭区间） ，s0和s1表示两个阵营单调栈中的当前和（不含无穷大） 
//具体算法是：对于一个组[l,r]，逐个元素扫描 ，对其阵营分类，0则直接更新两个单调栈，
//1或者2除此之外，需要在自己的阵营的单调栈中添加新元素无穷大， 在对方的阵营中查询（答案加上对方的和） 
//注意：先更新，后查询；也就是说在对方的阵营中查询时，对方必不含正无穷元素
//更新操作是指：维护单调栈的递增性（严格），从栈顶开始删元素，统计删的总个数，且维护和，最后再吐出来用于更新的元素x，个数就是删的个数
//注意细节：空栈不可以进行更新，直接跳过即可 

inline void I(int p[],int n1[],int &c1) {
	p[++c1]=oo; n1[c1]=1;
}

inline void U(int p[],int n1[],int &c1,int x,ll &s) {
	if (c1==0) return ;
	int n0=0;
	while (c1 && p[c1]>=x) {
		if (p[c1]!=oo) s-=p[c1]*n1[c1];
		n0+=n1[c1];
		--c1;
	}
	p[++c1]=x;
	n1[c1]=n0;
	s+=x*n0;
} 

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
	int t1[N],t2[N],cc[N],x[N],sa[N],R[N],H[N],h[N],n,m,cnt,str_cnt,num0; char *s; int num[1005],home[N]; //ST T;
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
		int k=H[0]=s[n]=0;
		rep(i,0,n-1) {
			if (!R[i]) continue;
			int j=sa[R[i]-1];
			if (k) k--;
			while (s[i+k]==s[j+k]) k++;
			h[i]=H[R[i]]=k;
		}
	}
	/*inline int Q_lcp(int x,int y) {
		if (R[x]>R[y]) swap(x,y);
		return x==y ? n-x : H[T.Q(R[x]+1,R[y])];
	}*/
	/*inline int Q_lcs(int x,int y) {
		int ans=0,px=-1,py=-1;
		rep(i,0,n-1) {
			if (home[sa[i]]==x) {
				px=i; if (py!=-1) ans=max(ans,H[T.Q(py+1,i)]);
			}
			if (home[sa[i]]==y) {
				py=i; if (px!=-1) ans=max(ans,H[T.Q(px+1,i)]);
			}
		}
		return ans;
	} */
	inline void divide_group(int k,int x[]) {
		x[0]=cnt=0; rep(i,1,n-1) if (H[i]<k) x[++cnt]=i; x[++cnt]=n;
	}
	inline void count(int l,int r) {
		mem(num,0); num0=0; rep(i,l,r) num0+=!(num[home[sa[i]]]++); num0-=(num[0]>0);
	} 
	inline bool check_group(int l,int r,int k) {
		//...
		c1=c2=s1=s2=0;
		int cnt1=0,cnt2=0;
		rep(i,l,r) {
			if (i!=l) U(p,n1,c1,H[i],s1),U(q,n2,c2,H[i],s2);
			if (home[sa[i]]==1) { I(p,n1,c1); ans+=s2; cnt1++; }
			if (home[sa[i]]==2) { I(q,n2,c2); ans+=s1; cnt2++; }
		}
		ans-=(ll)cnt1*cnt2*(k-1); return 0;
	}
	inline bool check(int ans){
		divide_group(ans,x);
		rep(i,1,cnt) if (check_group(x[i-1],x[i]-1,ans)) return true; return false;
	}
	inline int binary(int l,int r) {
		int ans=-1,mid;
		while (l<=r) {
			mid=(l+r)>>1;
			if (check(mid)) {
				ans=mid;
				l=mid+1;
			} else r=mid-1;
		}
		return ans;
	}
	inline void Q(int k){
		//...
		divide_group(k,x);
		ans=0;
		rep(i,1,cnt) check_group(x[i-1],x[i]-1,k);
	}
	inline void Insert(char _s[],int op=0,int _n=0){
		if (n) home[n]=0,s[n++]=str_cnt+' '; if (!_n) _n=strlen(_s); ++str_cnt;
		if (!op) rep(i,0,_n-1) home[n]=str_cnt,s[n++]=_s[i]; else
				 per(i,_n-1,0) home[n]=str_cnt,s[n++]=_s[i];
	}
	SA(){ s=new char[N]; }
	inline void Clear() { n=str_cnt=0; }
	inline void Init(char _s[]=NULL,int _n=0,int _m='z'+1005){
		if (_s!=NULL) s=_s,n=_n ? _n : strlen(s);  m=_m;
		init_sa(); init_H(); //T.Init(n-1,H);
	}
};

SA T;
char s[N],t[N]; 
int k;

int main() {
    //file_put();
    
    while (scanf("%d",&k)!=EOF && k) {
    	scanf("%s%s",s,t);
    	T.Clear();
    	T.Insert(s);
    	T.Insert(t);
		T.Init();
		T.Q(k);
		printf("%I64d\n",ans);
	}

    return 0;
}

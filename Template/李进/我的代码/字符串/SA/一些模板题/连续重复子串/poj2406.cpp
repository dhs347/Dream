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
const int N=1001005; 
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
	int n,log[N],dp[21][N]; int *a;
	int h(int x,int y) { return a[x]<=a[y] ? x:y; }
	void Init(int _n,int *_a){
		n=_n,a=_a,log[0]=-1; rep(i,1,n) log[i]=log[i>>1]+1,dp[0][i]=i;
		rep(i,1,log[n]) rep(j,1,n+1-(1<<i)) dp[i][j]=h(dp[i-1][j],dp[i-1][j+(1<<(i-1))]);
	}
	int Q(int l,int r) { int L=log[r-l+1]; return h(dp[L][l],dp[L][r+1-(1<<L)]); }
}; 

struct SA{
	int x[3*N+5],sa[4*N+5],R[3*N+5],H[3*N+5],h[3*N+5],n,m,cnt,str_cnt; int *s;  int aa[3*N+5],bb[3*N+5]; //ST T;
	int fac[3*N+5];
	#define F(x) ((x)/3+((x)%3==1?0:tb))
	#define G(x) ((x)<tb?(x)*3+1:((x)-tb)*3+2)
	int wa[3*N+5],wb[3*N+5],wv[3*N+5],ws[3*N+5];
	int c0(int *r,int a,int b) {
		return r[a]==r[b]&&r[a+1]==r[b+1]&&r[a+2]==r[b+2];
	}
	int c12(int k,int *r,int a,int b) {
		if(k==2) return r[a]<r[b]||r[a]==r[b]&&c12(1,r,a+1,b+1);
		else return r[a]<r[b]||r[a]==r[b]&&wv[a+1]<wv[b+1];
	}
	void sort(int *r,int *a,int *b,int n,int m) {
		int i;
		for(i=0; i<n; i++) wv[i]=r[a[i]];
		for(i=0; i<m; i++) ws[i]=0;
		for(i=0; i<n; i++) ws[wv[i]]++;
		for(i=1; i<m; i++) ws[i]+=ws[i-1];
		for(i=n-1; i>=0; i--) b[--ws[wv[i]]]=a[i];
		return;
	}
	void dc3(int *r,int *sa,int n,int m) {
		int i,j,*san=sa+n,ta=0,tb=(n+1)/3,tbc=0,p; int *rn=r+n;
		r[n]=r[n+1]=0;
		for(i=0; i<n; i++) if(i%3!=0) wa[tbc++]=i;
		sort(r+2,wa,wb,tbc,m);
		sort(r+1,wb,wa,tbc,m);
		sort(r,wa,wb,tbc,m);
		for(p=1,rn[F(wb[0])]=0,i=1; i<tbc; i++)
			rn[F(wb[i])]=c0(r,wb[i-1],wb[i])?p-1:p++;
		if(p<tbc) dc3(rn,san,tbc,p);
		else for(i=0; i<tbc; i++) san[rn[i]]=i;
		for(i=0; i<tbc; i++) if(san[i]<tb) wb[ta++]=san[i]*3;
		if(n%3==1) wb[ta++]=n-1;
		sort(r,wb,wa,ta,m);
		for(i=0; i<tbc; i++) wv[wb[i]=G(san[i])]=i;
		for(i=0,j=0,p=0; i<ta && j<tbc; p++)
			sa[p]=c12(wb[j]%3,r,wa[i],wb[j])?wa[i++]:wb[j++];
		for(; i<ta; p++) sa[p]=wa[i++];
		for(; j<tbc; p++) sa[p]=wb[j++];
	}
	inline void init_sa(){
		dc3(s,sa,n+1,m);
	}
	/*inline void init_sa() {
		int *x=t1,*y=t2;
		rep(i,0,m-1) cc[i]=0;
		rep(i,0,n-1) ++cc[x[i]=s[i]-'a'];
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
	}*/
	/*inline void get_height(int *r,int n){
	    int i,j,k=0;
	    for(i=0;i<n;i++) R[sa[i]]=i;
	    for(i=0;i<n;H[R[i++]]=k)
	        if (R[i]) for(k?k--:0,j=sa[R[i]-1];r[i+k]==r[j+k];k++);
	}*/
	inline void get_height(int *r,int n){
	    int i,j,k=0;
	    for(i=0;i<=n;i++) R[sa[i]]=i;
	    for(i=0;i<n;H[R[i++]]=k)
	        if (R[i]) for(k?k--:0,j=sa[R[i]-1];r[i+k]==r[j+k];k++);
	}
	inline void init_H(){
		/*rep(i,0,n-1) R[sa[i]]=i;
		int k=H[0]=0;
		rep(i,0,n-1) {
			if (!R[i]) continue;
			int j=sa[R[i]-1];
			if (k) k--;
			while (s[i+k]==s[j+k]) k++;
			h[i]=H[R[i]]=k;
		}*/
		get_height(s,n);
	}
	/*inline int Q_lcp(int x,int y) {
		if (R[x]>R[y]) swap(x,y);
		return x==y ? n-x : H[T.Q(R[x]+1,R[y])];
	}*/
	inline int QQ_lcp(int k) {
		if (R[k]<R[0]) return aa[R[k]]; else return bb[R[k]];
	}
	inline void divide_group(int k,int x[]) {
		x[0]=cnt=0; rep(i,1,n-1) if (H[i]<k) x[++cnt]=i; x[++cnt]=n;
	}
	inline bool check_group(int l,int r,int ans) {
		//...
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
	inline int Q(){
		//...
		int tt=0;
		rep(i,1,(int)sqrt((double)n)+1) {
			if (n%i!=0) continue;
			fac[++tt]=i;
			fac[++tt]=n/i;
		}
		std::sort(fac+1,fac+tt+1);
		rep(i,1,tt){
			if (QQ_lcp(fac[i])!=n-fac[i]) continue;
			return fac[i];
		}
		return n;
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
		if (R[0]) {
			aa[R[0]-1]=H[R[0]];
			per(i,R[0]-2,0) aa[i]=min(aa[i+1],H[i+1]);
		}
		if (R[0]<n-1) {
			bb[R[0]+1]=H[R[0]+1];
			rep(i,R[0]+2,n-1) bb[i]=min(bb[i-1],H[i]);
		}
	}
};

SA T;
char s[3*N+5];
int a[3*N+5];
int len,q,x,y,n;

int main() {
    //file_put();
    
    while (scanf("%s",s)!=EOF && s[0]!='.') {
    	n=strlen(s);
    	rep(i,0,n-1) a[i]=s[i];
    	a[n]=0;
    	T.Init(a,n,300);
    	printf("%d\n",n/T.Q()); 
	}
    
    return 0;
}

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

struct TP{
	int l[N],r[N],ans[N][3],len[N],n,cnt,k; int *home,*sa; ll ans0;
	inline void Init(int _n,int _k,int _sa[],int _home[]) {
		cnt=n=_n; k=_k; sa=_sa; home=_home; ans0=0;
		rep(i,0,n) l[i]=i-1,r[i]=i+1,len[i]=1; l[0]=n,r[n]=0;
		rep(i,0,n-1) { mem(ans[i],0); ans[i][home[sa[i]]]=1; }
	}
	inline void M(int x,int y) {
		len[x]+=len[y]; //...
		rep(i,0,2) ans[x][i]+=ans[y][i];
	}
	inline void C(int x,int op) { ans0+=op*(ll)ans[x][1]*ans[x][2]; }
	inline void D(int x) {
		C(l[x],-1); C(x,-1); M(l[x],x); C(l[x],1);
		r[l[x]]=r[x]; l[r[x]]=l[x]; --cnt;
	}
}; 

struct SA{
	int sa[4*N+5],R[N],H[N],h[N],n,m,cnt,str_cnt,num0; int *s; int num[1005],home[N]; TP T; int cpos,inx[N],temp[N],flow[N]; 
	#define F(x) ((x)/3+((x)%3==1?0:tb))
	#define G(x) ((x)<tb?(x)*3+1:((x)-tb)*3+2)
	int wa[4*N+5],wb[4*N+5],wv[4*N+5],ws[4*N+5];
	int c0(int *r,int a,int b) { return r[a]==r[b]&&r[a+1]==r[b+1]&&r[a+2]==r[b+2]; }
	int c12(int k,int *r,int a,int b) {
		if(k==2) return r[a]<r[b]||r[a]==r[b]&&c12(1,r,a+1,b+1);
		else return r[a]<r[b]||r[a]==r[b]&&wv[a+1]<wv[b+1];
	}
	void sort(int *r,int *a,int *b,int n,int m) {
		int i; for(i=0; i<n; i++) wv[i]=r[a[i]];
		for(i=0; i<m; i++) ws[i]=0;
		for(i=0; i<n; i++) ws[wv[i]]++;
		for(i=1; i<m; i++) ws[i]+=ws[i-1];
		for(i=n-1; i>=0; i--) b[--ws[wv[i]]]=a[i];
	}
	void dc3(int *r,int *sa,int n,int m) {
		int i,j,*san=sa+n,ta=0,tb=(n+1)/3,tbc=0,p; int *rn=r+n; r[n]=r[n+1]=0;
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
	inline void init_sa(){ s[n]=0; dc3(s,sa,n+1,m); rep(i,0,n-1) sa[i]=sa[i+1]; }
	inline void init_H(){
		rep(i,0,n-1) R[sa[i]]=i;
		int k=H[0]=0; s[n]=m-1;
		rep(i,0,n-1) {
			if (!R[i]) continue;
			int j=sa[R[i]-1];
			if (k) k--;
			while (s[i+k]==s[j+k]) k++;
			h[i]=H[R[i]]=k;
		}
	}
	inline void Cut(int len){
		while (cpos && H[inx[cpos]]>=len) T.D(inx[cpos--]);
	}
	inline bool check_len(int len) { return true; }
	inline ll Core(int k) {
		cpos=n-1; ll ans=0; T.Init(n,k,sa,home);
		mem(temp,0); mem(flow,0); rep(i,1,n-1) temp[H[i]]++;
		rep(i,1,n) temp[i]+=temp[i-1];
		rep(i,1,n-1) {
			int t=H[i] ? temp[H[i]-1]+1 : 1;
			inx[t+(flow[t]++)]=i;
		}
		per(i,n,k) { Cut(i); if (check_len(i)) ans+=T.ans0; } return ans;
	}
	inline ll Q(int k){
		//...
		return Core(k);
	}
	inline void Insert(int _s[],int op,int _n){
		if (n) home[n]=0,s[n++]=505+str_cnt+1; ++str_cnt;
		if (!op) rep(i,0,_n-1) home[n]=str_cnt,s[n++]=_s[i]; else
				 per(i,_n-1,0) home[n]=str_cnt,s[n++]=_s[i];
	}
	SA(){ s=new int[4*N+5]; }
	inline void Clear() { n=str_cnt=0; }
	inline void Init(int _s[]=NULL,int _n=0,int _m=505+1005){
		if (_s!=NULL) s=_s,n=_n;  m=_m;
		init_sa(); init_H();
	}
};

SA T;
char s[N],t[N];
int k,a[N],n;

int main() {
    //file_put();
    
    while (scanf("%d",&k)!=EOF && k) {
    	scanf("%s%s",s,t);
    	T.Clear();
    	n=strlen(s);
    	rep(i,0,n-1) a[i]=s[i];
    	T.Insert(a,0,n);
    	n=strlen(t);
    	rep(i,0,n-1) a[i]=t[i];
    	T.Insert(a,0,n);
    	T.Init();
    	printf("%I64d\n",T.Q(k));
    	//debug_arr(T.H,T.n-1);
    	//debug_arr(T.inx,T.n-1);
    	//debug_arr(T.sa,T.n);
    	//debug_arr(T.home,T.n-1);
	}

    return 0;
}

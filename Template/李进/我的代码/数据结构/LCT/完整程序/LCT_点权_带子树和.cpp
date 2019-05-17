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

struct LCT{
	#define lson c[0][x]
	#define rson c[1][x]
	int f[N],c[2][N],rev[N],s[N],n,cnt_B; int v[N],ans[N][3],sub[N][2],_sub[N][2],lazy[N][2],temp[3];//ans: sum/max/min; lazy: +/* ; sub: size/sum
	void init(int _n,int a[]=NULL){
		mem(f,0); mem(c,0); mem(rev,0); cnt_B=n=_n; rep(i,1,n) s[i]=_sub[i][0]=1;
		ans[0][0]=0,ans[0][1]=-oo,ans[0][2]=oo; _sub[0][0]=_sub[0][1]=0;
		rep(i,0,n) lazy[i][0]=0,lazy[i][1]=1;
		if (a==NULL) { mem(ans+1,0); mem(_sub+1,0); mem(sub+1,0); mem(v,0); return; }
		rep(i,1,n) v[i]=ans[i][0]=ans[i][1]=ans[i][2]=_sub[i][1]=a[i]; mem(sub,0);
	}
	void push_up(int x) {
		s[x]=s[lson]+s[rson]+1;
		ans[x][0]=ans[lson][0]+ans[rson][0]+v[x];
		ans[x][1]=max(ans[lson][1],ans[rson][1]),ans[x][1]=max(ans[x][1],v[x]);
		ans[x][2]=min(ans[lson][2],ans[rson][2]),ans[x][2]=min(ans[x][2],v[x]);
		_sub[x][0]=_sub[lson][0]+_sub[rson][0]+sub[x][0]+1;
		_sub[x][1]=_sub[lson][1]+_sub[rson][1]+sub[x][1]+v[x];
	}
	void U(int x,int data[],int r){
		if (!x) return;
		v[x]=v[x]*data[1]+data[0];
		ans[x][0]=ans[x][0]*data[1]+s[x]*data[0];
		ans[x][1]=ans[x][1]*data[1]+data[0];
		ans[x][2]=ans[x][2]*data[1]+data[0];
		lazy[x][0]=lazy[x][0]*data[1]+data[0];
		lazy[x][1]=lazy[x][1]*data[1];
		if (r) swap(lson,rson),rev[x]^=1;
	}
	void _U(int x,int t,int y=0) { rep(i,0,1) sub[x][i]+=_sub[t][i]-_sub[y][i]; }
	void push_down(int x){
		U(lson,lazy[x],rev[x]); U(rson,lazy[x],rev[x]);
		lazy[x][0]=rev[x]=0,lazy[x][1]=1;
	}
	bool is_r(int x){ return c[0][f[x]]!=x && c[1][f[x]]!=x; }
	void U_P(int x){ if (!is_r(x)) U_P(f[x]); push_down(x); }
	void rot(int x){
		int y=f[x],z=f[y],l=(c[1][y]==x),r=l^1;
		if (!is_r(y)) c[c[1][z]==y][z]=x;
		f[x]=z,f[y]=x,f[c[r][x]]=y,c[l][y]=c[r][x],c[r][x]=y;
		push_up(y),push_up(x);
	}
	void SP(int x){
		U_P(x);
		for(;!is_r(x);rot(x)){
			int y = f[x],z = f[y];
			if(!is_r(y)) if((c[0][y]==x)^(c[0][z]==y)) rot(x); else rot(y);
		}
	}
	void AC(int x){ for (int t=0; x; x=f[x]) SP(x),_U(x,rson,t),rson=t,push_up(x),t=x; }
	void make_R(int x){ AC(x),SP(x),swap(lson,rson),rev[x]^=1; }
	void get_P(int x,int y) { make_R(x); AC(y); SP(y); }
	void link(int x,int y){ get_P(x,y),/*make_R(x),make_R(y),*/f[x] = y,_U(y,x),push_up(y); --cnt_B; }
	void cut(int x,int y) { get_P(x,y),c[0][y]=f[c[0][y]]=0,push_up(y); ++cnt_B; }
	int get_dep(int x) { AC(x); SP(x); return s[x]; }
	int get_R(int x){ AC(x),SP(x); for (;lson;x=lson) push_down(x); return x; }
	int get_r(int x){ while (!is_r(x)) x=f[x]; return x; }
	int get_F(int x){ AC(x); SP(x); for (x=lson; rson; x=rson); return x; }
	bool is_Home(int x,int y) { return get_R(x)==get_R(y); }
	bool is_home(int x,int y) { return get_r(x)==get_r(y); }
	int get_lca(int x,int y) { AC(x); AC(y); SP(x); return is_home(x,y)?x:f[x]; }
	int* query(int x,int y) { get_P(x,y); return ans[y]; }
	int* query_sub(int x,int r=0) { 
		if (r) make_R(r); AC(x); 
		temp[0]=sub[x][0]+1,temp[1]=sub[x][1]+v[x]; return temp; 
	}
	void update(int x,int y,int data[],int r) { get_P(x,y); U(y,data,r); }
	bool LC(int op,int x,int y) {
		if (is_Home(x,y)==op) return false;
		if (op==1) link(x,y); else cut(x,y); return true;
	}
	void print_p(int); void print_P(int,int*); void print();
};

void LCT::print_p(int x){
	if (!x) return;
	printf("id=%d   v[%d]=%d  sum[%d]=%d  max[%d]=%d  min[%d]=%d   s[%d]=%d   lazy[%d]=%d  lazy[%d]=%d\n",x,x,v[x],x,ans[x][0],x,ans[x][1],x,ans[x][2],x,s[x],x,lazy[x][0],x,lazy[x][1]);
}

void LCT::print_P(int x,int *y){
	if (!x) return; y[x]=1; push_down(x);
	print_P(lson,y); print_p(x); print_P(rson,y);
}

void LCT::print(){
	int check[N],cnt=0; mem(check,0);
	rep(i,1,n) if (!check[i]) {
		int x=get_r(i);
		printf("\n\n\n*****>>  root=%d   father=%d   size=%d\n",x,f[x],s[x]);
		print_P(x,check);
		cnt+=(!f[x]);
	}
	printf("\n\n\nconnected blocks number: %d \n\n\n",cnt);
}

int n,x,y,q,t,a[N],data[2];
LCT T;

int main() {
    file_put();

    while (scanf("%d%d",&n,&q)!=EOF) {
    	rep(i,1,n) scanf("%d",&a[i]);
    	T.init(n,a);
    	rep(i,1,n-1) {
    		scanf("%d%d",&x,&y);
    		T.link(x,y);
		}
		T.make_R(12);
		while (q--) {
			scanf("%d%d",&x,&y);
			printf("%d %d %d\n",x,T.query_sub(x)[0],T.query_sub(x)[1]);
		}
	}
	debug_arr(T.v,n);
	T.cut(10,4);
	cout<<T.query_sub(10,14)[0]<<endl;
	cout<<T.query_sub(4,15)[0]<<endl;
	T.link(7,6);
	cout<<T.query_sub(10,14)[0]<<endl;
	cout<<T.query_sub(13,7)[0]<<endl;

    return 0;
}



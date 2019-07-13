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
const double PI=acos(-1);

void file_put() {
    freopen("filename.in", "r", stdin);
    freopen("filename.out", "w", stdout);
}

#define rep_it(it,x) for (__typeof((x).begin()) it=(x).begin(); it!=(x).end(); it++)
#define ____ puts("\n_______________\n\n") 
#define debug(x) ____; cout<< #x << " => " << (x) << endl
#define debug_pair(x) cout<<"\n{ "<<(x).fir<<" , "<<(x).sec<<" }\n"
#define debug_arr(x,n) ____; cout<<#x<<":\n"; rep(i,0,n+1) cout<<#x<<"["<<(i)<<"] => "<<x[i]<<endl
#define debug_arr2(x,n,m) ____; cout<<#x<<":\n"; rep(i,0,n+1) rep(j,0,m+1) cout<<#x<<"["<<(i)<<"]["<<(j)<<"]= "<<x[i][j]<<((j==m)?"\n\n":"    ")
#define debug_set(x) ____; cout<<#x<<": \n"; rep_it(it,x) cout<<(*it)<<" "; cout<<endl
#define debug_map(x) ____; cout<<#x<<": \n"; rep_it(it,x) debug_pair(*it)

const int N=6e5+5,M=11;
int cnt[M][N],nn[M],p,_cnt[M][N],K;

struct BigInt{
	ll a[50]; int len; static const ll lim=(ll)1e8;
	BigInt() { memset(a, 0, sizeof a); len = 1; } 
	void operator /= (ll b)
	{
		per(i, 2, len+1) a[i-1] += a[i]%b*lim, a[i] /= b;
		for (a[1]/=b; len>1&&!a[len]; --len); 
	}
	BigInt operator / (ll b)
	{
		BigInt t = *this; t /= b; return t;
	}
	ll operator % (ll b)
	{
		ll res = 0, tl = lim%b;
		per(i, 1, len+1) res = (res*tl%b + a[i]%b) % b;
		return res;
	}
	bool zero() { return len==1&&!a[1]; }
    void readstr(const char*s)
	{
		len = strlen(s);
		for (int i = 0, j; j=(len-i-1)/8+1, i<len; ++i)
			a[j] = a[j]*10 + s[i]-'0';
		len = (len+7) / 8;
	}
} nnn; 

char s[N];

void bat(BigInt &B,int p,int a[],int &k) {
    int t=0;
    while (!B.zero()) a[t++]=B%p,B/=p;
    k=t;
}

int mul(int x,int y,int p=29) {
    return (ll)x*y%p;
}

int tot=1,k,inv[N],fac[N],g=2,gk[N],no[N],_ret[N],ret[N];

void work(int n,int cnt[]) {
    int n0=fac[n];
    rep(x,0,n+1) {
        int y=n-x;
        cnt[mul(inv[mul(fac[x],fac[y],p)],n0,p)]++;
    }    
}


const int _M=130000,_N=130000;
template <class V>
struct FT{
	struct cp{ double x,y; } tmp[_M*2+5];
	friend cp operator + (cp &a,cp &b) { return cp{a.x+b.x,a.y+b.y}; }
	friend cp operator - (cp &a,cp &b) { return cp{a.x-b.x,a.y-b.y}; }
	friend cp operator * (cp &a,cp &b) { return cp{a.x*b.x-a.y*b.y,a.x*b.y+a.y*b.x}; }
	cp get(double x) { return cp{cos(x),sin(x)}; }
	vector <cp> aa,bb;
	void FFT(vector<cp> &a,int n,int op){
		for(int i=(n>>1),j=1;j<n;j++){
			if(i<j) swap(a[i],a[j]);
			int k; for(k=(n>>1);k&i;i^=k,k>>=1); i^=k; 
		}
		for(int m=2;m<=n;m<<=1){
			cp w=get(2*PI*op/m); tmp[0]=cp{1,0};
			for(int j=1;j<(m>>1);j++) tmp[j]=tmp[j-1]*w;
			for(int i=0;i<n;i+=m)
				for(int j=i;j<i+(m>>1);j++){
					cp u=a[j],v=a[j+(m>>1)]*tmp[j-i];
					a[j]=u+v,a[j+(m>>1)]=u-v;
				}
		}
		if(op==-1) rep(i,0,n) a[i]=cp{a[i].x/n,a[i].y/n};
	}
//	void multiply(int A[][N],int _ret[]){
//		int lena=p-1,len=1;
//		while (len<lena*10) len<<=1;
//		rep(i,0,K) aa[i]=vector<cp>(len);
//		rep(i,0,K) rep(j,0,lena) aa[i][j]=cp{(double)A[i][j],0};
//		rep(i,0,K) FFT(aa[i],len,1);
//		rep(i,1,K) rep(j,0,len) aa[0][j]=aa[0][j]*aa[i][j];
//		FFT(aa[0],len,-1);
//		rep(i,0,len) _ret[i]=((ll)(aa[0][i].x+0.5)%29);
////		debug_arr(_ret,len);
//		rep(i,p-1,len) (_ret[i%(p-1)]+=_ret[i])%=29;
//	}
	vector<V> multiply(int A[],int B[]){
		int lena=p-1,lenb=p-1,len=1;
		while (len<lena+lenb) len<<=1;
		aa=vector<cp>(len),bb=vector<cp>(len);
		rep(i,0,lena) aa[i]=cp{(double)A[i],0};
		rep(i,0,lenb) bb[i]=cp{(double)B[i],0};
		FFT(aa,len,1),FFT(bb,len,1);
		rep(i,0,len) aa[i]=aa[i]*bb[i];
		FFT(aa,len,-1);
        rep(i,0,len) A[i]=((ll)(aa[i].x+0.5))%29;
        rep(i,p-1,len) A[i%(p-1)]+=A[i];
	}
};

FT<int> TT; int ans[N]; 

char get_char(int x) {
    if (x<10) return x+48;
    return x+55;
}
//
//int C[1005][1005]; int ppp[100005];
//
//void init(int n) {
//    C[0][0]=1;
//    rep(i,1,n+1) {
//        C[i][0]=1;
//        rep(j,1,n+1) C[i][j]=(C[i-1][j-1]+C[i-1][j])%p;
//    }
////    debug_arr(C[n],n);
//    rep(i,0,n+1) ppp[C[n][i]]=(ppp[C[n][i]]+1)%29;
////    debug_arr(ppp,n);
//    rep(i,0,p) if (ppp[i]) printf("%d %d\n",i,ppp[i]);
//    printf("\n");
//}

int main() {
//    file_put(); 
    
    scanf("%s%d",s,&p),fac[0]=1,inv[1]=1;
    rep(i,1,p) fac[i]=mul(fac[i-1],i,p);
    rep(i,2,p) inv[i]=mul(p-p/i,inv[p%i],p);
    nnn.readstr(s);
    int n0=nnn%29;
    bat(nnn,p,nn,K);
    rep(i,0,K) tot=mul(tot,nn[i]+1,29);
    rep(i,0,K) work(nn[i],cnt[i]);
    gk[0]=1;
    rep(i,1,p) gk[i]=(gk[i-1]<<1)%p;
    rep(i,0,p-1) no[gk[i]]=i;
    rep(i,0,K) rep(j,1,p) _cnt[i][no[j]]=cnt[i][j];
    ans[0]=1;
//    debug(233);
    rep(i,0,K) TT.multiply(ans,_cnt[i]);
    rep(i,0,p-1) ret[gk[i]]=ans[i];
    ret[0]=(n0+1-tot)%29;
    rep(i,0,p) ret[i]=(ret[i]+29)%29;
    rep(i,0,p) printf("%c",get_char(ret[i]));
    printf("\n");
//    rep(i,0,p) if (ret[i]) printf("%d %d\n",i,ret[i]);
//    printf("\n");
//    init(1);
//    debug_arr(inv,10);
//    debug(n0); debug(K);
    
	return 0;
}


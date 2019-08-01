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
#define mem(a,x) memset(a,x,sizeof(a))



void file_put() {
    freopen("filename.in", "r", stdin);
    freopen("filename.out", "w", stdout);
}

const int N=(1<<20)+15,mod=1e9+7;
int n,m,k,f[N],a[25]; ll p;

int add(int x,int y) {
	return (x+=y)>=mod? x-mod:x;
}

int sub(int x,int y) {
	return (x-=y)<0 ? x+mod:x; 
}

ll Pow(ll x,ll k) {
	ll ret=1;
	for (; k; k>>=1,x=x*x%mod) if (k&1) ret=ret*x%mod;
	return ret;
}

void FWT(int a[],int n){
    for(int d=1; d<n; d<<=1)  
        for(int m=d<<1,i=0; i<n; i+=m)  
            for(int j=0; j<d; j++){  
                int x=a[i+j],y=a[i+j+d];  
                a[i+j]=add(x,y),a[i+j+d]=sub(x,y);  
            }
}

ll pp[2020];

int main() {
//	file_put();
	
	while (scanf("%d%d%d",&n,&m,&k)!=EOF) {
		mem(f,0);
		rep(i,1,n+1) {
			rep(j,0,m) scanf("%d",&a[j]);
			pp[0]=0;
			rep(s,1,1<<m) pp[s]=pp[s^(s&-s)]^a[__builtin_ctz(s&-s)];
			rep(s,0,1<<m) f[pp[s]]+=1-__builtin_parity(s)*2;
		}
//		rep(i,0,1<<m) printf("%d\n",f[i]); 
		FWT(f,1<<k); ll y=1,ans=0,p=1<<m;
		p=Pow(p,mod-2);
//		printf("ssss\n");
//		rep(i,0,1<<k) printf("%d\n",f[i]);
//		printf("dddd\n");
		rep(x,0,1<<k) {
			ans^=add(f[x]*y%mod*p%mod,mod),y=y*3%mod;
		}
		printf("%lld\n",ans);
	}
	
	return 0;
}


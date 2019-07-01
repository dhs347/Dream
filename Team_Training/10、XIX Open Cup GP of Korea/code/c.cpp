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

ll P=(ll)1e9+7;

ll Pow(ll x,ll k) {
	if (k<=0) return 1;
	ll ret=1;
	for (; k; k>>=1,x=x*x%P) if (k&1) ret=ret*x%P;
	return ret;
}

ll inv(ll x) { return Pow(x,P-2); }

int add(int &x,int y) { x+=y,x%=P; }

const int N=5005;
int n,r,h,dpl[N],dpr[N],f[2][N],id[N],a[N],tt,L,R,A,B,cnth=0,cntr=0,ret=0,ans; char s[N],t[N];

void DP(char s[],int dp[],int k) {
	if (!k) { dp[0]=1; return; }
	mem(f,0),mem(id,0),mem(a,0); int ch=0,cr=0;
	rep(i,1,n+1) if (s[i]=='R') cr++; else id[++ch]=i,a[ch]=cr;
	rep(i,k,ch+1) {
		f[i&1][0]=(i==k);
		rep(j,1,a[i]+1) f[i&1][j]=(f[i&1^1][j]+f[i&1][j-1])%P;
		dp[id[i]]=f[i&1][a[i]];
	}
}

int main() {
//	file_put();
	
	scanf("%d%d%d%s%d%d",&n,&r,&h,s+1,&A,&B),tt=h+r,r=r*inv(tt)%P,h=h*inv(tt)%P;
    L=1,R=n,copy(s+L,s+R+1,t+1);
	DP(t,dpl,B),reverse(t+1,t+n+1);
	rep(i,1,n+1) cnth+=(t[i]=='H'),t[i]='H'+'R'-t[i];
	DP(t,dpr,A),reverse(dpr,dpr+n+2),cntr=n-cnth;
	if (A>cntr || B>cnth) return 0*printf("0\n");
	ans=Pow(h,cnth-B)*Pow(r,cntr-A)%P;
	rep(i,0,n+1) ret+=(ll)dpl[i]*dpr[i+1]%P,ret%=P;
	ret=(ll)ret*ans%P,printf("%d\n",ret); 
	
	return 0;
}




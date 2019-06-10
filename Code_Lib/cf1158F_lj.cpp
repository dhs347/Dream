#include<bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i=(a); i<(b); i++)
#define per(i, a, b) for(int i=(b)-1; i>=(a); i--)
typedef long long ll;

#define mem(a,x) memset(a,x,sizeof(a))

const int N=3005,_p=998244353,B=12;
const ll oo=1e15;

inline int add(int x,int y) { return (x+=y)>=_p?x-_p:x; }
inline int mul(int x,int y) { ll t=(ll)x*y; return t<_p?t:t%_p; }
inline void Add(int &x,int y) { x+=y; if (x>=_p) x-=_p; }
inline void Mul(int &x,int y) { ll t=(ll)x*y; x=(t<_p?t:t%_p);}
int Pow(int x,int k) {
    int ret=1;
    for (; k; k>>=1,Mul(x,x)) if (k&1) Mul(ret,x);
    return ret;
}

int n,c,f[N],dp[N][N],a[N],num[N][N],cnt[N],u[N][4100],P[N],inv[N],K,S;

inline void work_1() {
    rep(i,1,n+1) for (int j=i-1,now=0,tot=0; j<=n; j++) {
        if (j==i-1) { memset(cnt,0,sizeof(int)*(c+1)); continue; }
        tot+=!cnt[a[j]],cnt[a[j]]++;
        if (tot>=c && !now) {
            now=1;
            rep(k,1,c+1) Mul(now,P[cnt[k]]-1);
            num[i][j]=now;
            continue;
        }
        if (tot<c) continue; else cnt[a[j]]--;
        Mul(now,inv[cnt[a[j]]]),num[i][j]=now;
        Mul(now,P[++cnt[a[j]]]-1);
    }
    dp[0][0]=1;
    rep(t,1,K+1) rep(i,t*c,n+1) {
    	ll tmp=0;
    	rep(j,0,i-c+1) {
    		tmp+=1ll*dp[t-1][j]*num[j+1][i];
    		if (tmp>=oo) tmp%=_p;
		}
    	dp[t][i]=tmp%_p;
	}
}

inline void work_2() {
    u[0][0]=dp[0][0]=1,S=(1<<c)-1;
    rep(i,1,n+1) {
        rep(t,1,K+1) dp[t][i]=u[t-1][S^(1<<a[i]-1)];
        per(t,0,K+1) {
            per(mask,1,S+1) if (mask>>(a[i]-1)&1) u[t][mask]=add(u[t][mask],u[t][mask]),Add(u[t][mask],u[t][mask^(1<<(a[i]-1))]);
            Add(u[t][0],dp[t][i]);
        }
    }
} 

int main() {
    scanf("%d%d",&n,&c),P[0]=inv[0]=1,K=n/c;
    rep(i,1,n+1) scanf("%d",&a[i]),P[i]=mul(P[i-1],2),inv[i]=Pow(P[i]-1,_p-2);
    if (c<=B) work_2(); else work_1();
    f[0]=P[n]-1;
    rep(t,1,n+1) rep(i,t*c,n+1) Add(f[t],mul(dp[t][i],P[n-i]));
    rep(t,0,n+1) printf("%d ",(f[t]-f[t+1]+_p)%_p);
    printf("\n");
    
	return 0;
}

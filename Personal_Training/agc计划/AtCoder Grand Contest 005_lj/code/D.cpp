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

#define rep_it(it,x) for (__typeof((x).begin()) it=(x).begin(); it!=(x).end(); it++)
#define ____ puts("\n_______________\n\n") 
#define debug(x) ____; cout<< #x << " => " << (x) << endl
#define debug_pair(x) cout<<"\n{ "<<(x).fir<<" , "<<(x).sec<<" }\n"
#define debug_arr(x,n) ____; cout<<#x<<":\n"; rep(i,0,n+1) cout<<#x<<"["<<(i)<<"] => "<<x[i]<<endl
#define debug_arr2(x,n,m) ____; cout<<#x<<":\n"; rep(i,0,n+1) rep(j,0,m+1) cout<<#x<<"["<<(i)<<"]["<<(j)<<"]= "<<x[i][j]<<((j==m)?"\n\n":"    ")
#define debug_set(x) ____; cout<<#x<<": \n"; rep_it(it,x) cout<<(*it)<<" "; cout<<endl
#define debug_map(x) ____; cout<<#x<<": \n"; rep_it(it,x) debug_pair(*it)

void file_put() {
    freopen("filename.in", "r", stdin);
    freopen("filename.out", "w", stdout);
}

const int N=20000+5,P=924844033;
ll inv[N],fac[N],dp[N],f[N],ret=0; int n,cnt=0,len[N],k; bool v[N<<1]; vi V[N<<1];

void init() {
	fac[0]=1; rep(i,1,N) fac[i]=fac[i-1]*i%P;
	inv[0]=inv[1]=1; rep(i,2,N) inv[i]=(P-P/i)*inv[P%i]%P;
	rep(i,1,N) inv[i]=inv[i-1]*inv[i]%P;
}

ll C(int n,int k) {
	if (n<0 || k<0 || n<k) return 0;
	return fac[n]*inv[k]%P*inv[n-k]%P;
}

void dfs(int x,int k) {
	len[k]++; v[x]=1;
	if (V[x].empty()) return;
	if (!v[V[x][0]]) dfs(V[x][0],k);
}

int main() {
//	file_put();
	
	init();
	scanf("%d%d",&n,&k);
	rep(i,1,n+1) {
		if (i+k<=n) V[i].pb(i+k+n);
		if (i-k>0) V[i-k+n].pb(i);
	}
	rep(i,1,k+1) {
		if (v[i]) continue;
		dfs(i,++cnt); len[cnt]--;
	}
	rep(i,n+1,n+k+1) {
		if (v[i]) continue;
		dfs(i,++cnt); len[cnt]--;
	}
	dp[0]=1;
	rep(i,1,cnt+1) {
		memset(f,0,sizeof(f));
		rep(j,0,len[i]+1) per(k,0,n-j+1) (f[k+j]+=dp[k]*C(len[i]-j+1,j)%P)%=P;
		swap(f,dp);
	}
	for (int i=0,op=1; i<=n; i++,op=-op) ret+=dp[i]*op*fac[n-i]%P,ret%=P;
	printf("%lld\n",(ret+P)%P);
	
	return 0;
}


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

const int N=2e6+5,P=924844033;
int n,x,y,siz[N]; ll num[N],fac[N],inv[N],ret[N]; vi V[N];

ll Pow(ll x,ll k) { ll ans=1; for (;k;k>>=1,x=x*x%P) if (k&1) (ans*=x)%=P; return ans; } 

template <class V>
struct FT{
	static const int N=1<<19,_p=P; V w[2][N*2+5],rev[N*2+5],tmp;
	void Init() {
		V w0=Pow(5,(_p-1)/N),m; w[0][0]=w[1][0]=1;
		rep(i,1,N) w[0][i]=w[1][N-i]=(ll)w[0][i-1]*w0%_p;
		for (m=0; (1<<m)!=N; m++);
		rep(i,1,N) rev[i]=(rev[i>>1]>>1)|(i&1)<<m-1;
	}
	void FFT(V A[],int op){
		rep(i,0,N) if (i<rev[i]) swap(A[i],A[rev[i]]);
		for (int i=1; i<N; i<<=1)
			for (int j=0,t=N/(i<<1); j<N; j+=i<<1)
				for (int k=j,l=0; k<j+i; k++,l+=t) {
					V x=A[k],y=(ll)w[op][l]*A[k+i]%_p;
					A[k]=(x+y)%_p,A[k+i]=(x-y+_p)%_p;
				}
		if (op) { tmp=Pow(N,_p-2); rep(i,0,N) A[i]=1ll*A[i]*tmp%_p; }
	}
	void Solve(V A[],V B[],V C[],int op=0) {
		if (op) reverse(B,B+N); FFT(A,0),FFT(B,0); 
		rep(i,0,N) C[i]=(ll)A[i]*B[i]%_p; FFT(C,1); if (op) reverse(C,C+N);
	}
};

void dfs(int x,int p) {
	siz[x]=1;
	for (auto y: V[x]) if (y!=p) dfs(y,x),siz[x]+=siz[y];
	if (p) num[siz[x]]--,num[n-siz[x]]--;
}

FT<ll> T;

int main() {
//	file_put();
	
	scanf("%d",&n);
	rep(i,1,n) scanf("%d%d",&x,&y),V[x].pb(y),V[y].pb(x);
	dfs(1,0),num[n]=n;
	fac[0]=inv[0]=inv[1]=1;
	rep(i,2,n+1) inv[i]=(P-P/i)*inv[P%i]%P;
	rep(i,1,n+1) inv[i]*=inv[i-1],inv[i]%=P,fac[i]=fac[i-1]*i%P;
//	debug_arr(num,n);
	rep(i,0,n+1) (num[i]*=fac[i])%=P,fac[i]=inv[i];
	T.Init();
	T.Solve(fac,num,ret,1);
	rep(i,0,n+1) ret[i]*=inv[i],ret[i]%=P;
	rep(i,1,n+1) printf("%lld\n",ret[i]);
	
	return 0;
}


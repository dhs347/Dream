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

const int N=1e4+5,P=1e9+7;
int n; ll S[N],ans=0;

ll mul(ll x,ll y) { return x*y%P; }
void add(ll &x,ll y) { x+=y,x%=P; }

ll Pow(ll x,ll k) {
	ll ret=1;
	for (; k; k>>=1,x=mul(x,x)) if (k&1) ret=mul(ret,x);
	return ret;
}

int main() {
//	file_put();
	
	scanf("%d",&n),S[0]=1;
	rep(i,1,n+1) per(j,0,i+1) S[j]=(mul(S[j],i-1)+(j?S[j-1]:0))%P;
//	debug_arr(S,n);
	for (int t=1,op=1; t<=n-1; ++t,op=-op) add(ans,mul(op*S[n-t],Pow(1-Pow(P+1>>1,t),P-2)));
	printf("%lld\n",(ans-1+P)%P); 
	
	return 0;
}


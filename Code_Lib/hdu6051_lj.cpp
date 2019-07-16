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

void file_put() {
    freopen("filename.in", "r", stdin);
    freopen("filename.out", "w", stdout);
}

ll get_phi(int n) {
	int ret=n;
	for (int i=2; i*i<=n; i++) {
		if (n%i) continue;
		while (n%i==0) n/=i;
		ret=ret/i*(i-1);
	}
	if (n>1) ret=ret/n*(n-1);
	return ret;
}

const int P=1e9+7;
int p,m,n,_2=P+1>>1,T,cas=0;

ll f(int d) {
	int m=n/d;
	ll ret=(ll)m*get_phi(m)%P;
	ret+=(m==1);
	ret=(ll)ret*_2%P;
	ret=(ll)d*d%P*ret%P;
	return ret;
}

int main() {
//	file_put(); 
	
	scanf("%d",&T);
	while (T--) {
		ll ret=0;
		scanf("%d%d",&m,&p),n=p-1;
		for (int d=1; (ll)d*d<=n; d++) if (n%d==0) {
			ret+=f(d),ret%=P;
			if (n/d!=d) ret+=f(n/d),ret%=P;
		}
		ret-=(ll)p*(p-1)%P*_2%P,ret%=P,(ret+=P)%=P;
		printf("Case #%d: %d\n",++cas,(ll)ret*m%P);
	}
	
	return 0;
}


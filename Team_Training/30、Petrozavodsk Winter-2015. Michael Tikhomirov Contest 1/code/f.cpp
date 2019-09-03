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

const int N=1e6+5,P=1e9+7;
int n; ll E2[N],ES2[N],E2S,inv[N],ret;

int main() {
//	file_put();
	
	scanf("%d",&n),inv[0]=inv[1]=E2[0]=ES2[0]=E2S=1;
	rep(i,2,n+1) inv[i]=(P-P/i)*inv[P%i]%P;
	rep(i,1,n+1) {
		E2[i]=(2*E2S*inv[i]%P+2*ES2[i-1]*inv[i]%P*inv[i]%P)%P;
		E2S=(E2S+E2[i])%P;
		ES2[i]=((i+4)*ES2[i-1]%P*inv[i]%P+E2[i])%P;
	}
	ret=E2[n]-(ll)(n+1)*(n+1)%P;
	printf("%lld\n",(ret+P)%P);
	
	return 0;
}


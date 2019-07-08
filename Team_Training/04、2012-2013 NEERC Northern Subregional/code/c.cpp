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

ll f[5][55],g[5],ans; int n; 

ll mul(ll x,ll y,ll z) {
	ll g=__gcd(y,z);
	y/=g,z/=g;
	return x/z*y;
}

void file_put() {
    freopen("chemistry.in", "r", stdin);
    freopen("chemistry.out", "w", stdout);
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	
	file_put();
	
	cin>>n;
	rep(i,0,5) f[i][0]=1;
	rep(i,1,(n>>1)+1) {
		g[0]=1;
		rep(j,1,min((n-1)/i,4)+1) g[j]=mul(g[j-1],f[3][i-1]+j-1,j);
		per(t,0,4) per(j,0,n-i+1) rep(k,1,min((n-j)/i,4-t)+1)
			f[t+k][j+k*i]+=f[t][j]*g[k];
	}
	ans=f[4][n-1]-(n&1^1)*(f[3][(n>>1)-1]-1)*f[3][(n>>1)-1]/2;
	cout<<ans<<endl;

	return 0;
}


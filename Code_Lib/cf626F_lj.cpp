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

const int N=205,P=1e9+7;
int n,K,a[N],f[N][N][1005]; ll ret=0;

int main() {
	//file_put(); 
	
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	
	cin>>n>>K;
	rep(i,1,n+1) cin>>a[i];
	sort(a+1,a+n+1);
	f[0][0][0]=1;
	rep(i,0,n) rep(j,0,i+1) rep(k,0,K+1) {
		if (k+j*(a[i+1]-a[i])>K) continue;
	    (f[i+1][j+1][k+j*(a[i+1]-a[i])]+=f[i][j][k])%=P;
        (f[i+1][j][k+j*(a[i+1]-a[i])]+=(ll)f[i][j][k]*(j+1)%P)%=P;
        (f[i+1][j-1][k+j*(a[i+1]-a[i])]+=(ll)f[i][j][k]*j%P)%=P;
    }
    rep(k,0,K+1) (ret+=f[n][0][k])%=P;
    cout<<ret<<endl;
	
//	cout << setiosflags(ios::fixed);
//	cout << setprecision(3);
	return 0;
}


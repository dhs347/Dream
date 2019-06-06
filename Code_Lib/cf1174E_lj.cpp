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
int n,K,dp[N][21][2];

ll f(int x,int y) {
    return (n>>x)/(y?3:1);
}

int main() {
    //file_put();
    
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	
	cin>>n,K=63-__builtin_clzll(n);
	dp[1][K][0]=1;
    if (K) dp[1][K-1][1]=((1<<K-1)*3<=n);
	rep(i,1,n) per(x,0,K+1) per(y,0,2) {
	    (dp[i+1][x][y]+=dp[i][x][y]*(f(x,y)-i)%P)%=P;
	    if (x) (dp[i+1][x-1][y]+=dp[i][x][y]*(f(x-1,y)-f(x,y))%P)%=P;
	    if (y) (dp[i+1][x][y-1]+=dp[i][x][y]*(f(x,y-1)-f(x,y))%P)%=P;
    }
    cout<<dp[n][0][0]<<endl;
	
	return 0;
}


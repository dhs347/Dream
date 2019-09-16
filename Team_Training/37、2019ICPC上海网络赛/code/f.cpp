#include <bits/stdc++.h>
#include <map> 
#include <cstring>
using namespace std;
#define rep(i,a,b) for(int i=(a);i<(b);i++)
#define de(x) cout<<#x<<" = "<<x<<"\n"
#define dd(x) cout<<#x<<" = "<<x<<" "
#define mes(p) memset(p,0,sizeof(p))
#define all(x) x.begin(),x.end()
#define rson mid+1,r,rt<<1|1
#define sz(x) (int)x.size()
#define lson l,mid,rt<<1
#define pb push_back
#define mp make_pair
#define ls (rt<<1)
#define se second
#define rs (ls|1)
#define fi first
typedef pair <int ,int > pi;
typedef vector <int > vi;
typedef long long ll;
typedef __int128 ull;
const int maxn=3000005;
const ll mod = 1e9+ 7;

const int N = 30;

ull dp[N][N][N], f[N][N];

void print(ull x) {
	vi v;
	while(x) v.pb(x % 10), x /= 10;
	reverse(all(v));
	for(auto u : v) cout << u; cout << endl;
}

int main(){	
	ios_base::sync_with_stdio(0);
    cin.tie(0);
    rep(x, 0, 27) {
    	dp[x][x][0] = 1;
    	rep(i, x, 27) rep(j, 1, 27) {
    		dp[x][i][j] = dp[x][i][j - 1] * i;
    		if(i) dp[x][i][j] += dp[x][i - 1][j - 1];
		}
		rep(i, 0, 27) rep(j, x, 27) f[x][i] += dp[x][j][i];
	}
	int T; cin >> T;
	rep(ca, 1, T + 1) {
		cout << "Case #" << ca << ": ";
		int n; string ks; cin >> n >> ks;
		ull k = 0;
		for(auto u : ks) k = k * 10 + u - '0';
		int now = 0;
		rep(i, 1, n + 1) {
			rep(j, 1, 27) {
				int x = now; if(j > now) ++x;
				ull t = f[x][n - i];
				if(t < k) {
					k -= t;
				} else {
					cout << (char)(j + 'A' - 1);
					if(j > now) ++now;
					break;
				}
			}
		}
		cout << endl;
	}
//	rep(x, 1, 27) print(f[0][x]);
	return 0;
}

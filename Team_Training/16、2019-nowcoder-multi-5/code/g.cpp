#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a) --i)
#define dd(x) cout << #x << " = " << x << " "
#define de(x) cout << #x << " = " << x << endl
#define pw(x) (1ll<<(x))
#define endl "\n"
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef double db;

const int N = 3030, P = 998244353;

int n, m;
int dp[N][N], f[N][N][2];
char s[N], t[N];

void upd(int &a, int b) {
	if((a += b) >= P) a -= P;
}

void solve() {
	cin >> n >> m >> (s + 1) >> (t + 1);
	rep(i, 0, n + 1) rep(j, 0, n + 1) dp[i][j] = f[i][j][0] = f[i][j][1] = 0;
	dp[0][0] = f[0][0][0] = 1;
	rep(i, 0, n) rep(j, 0, i + 1) if(dp[i][j]) {
		if(j || (j == 0 && s[i + 1] >= '1')) upd(dp[i + 1][j + 1], dp[i][j]);
		upd(dp[i + 1][j], dp[i][j]);
	}
	rep(i, 0, n) rep(j, 0, i + 1) {
		if(f[i][j][0]) {
			if(s[i + 1] >= t[j + 1]) upd(f[i + 1][j + 1][s[i + 1] > t[j + 1]], f[i][j][0]);
			upd(f[i + 1][j][0], f[i][j][0]);
		} 
		if(f[i][j][1]) {
			upd(f[i + 1][j + 1][1], f[i][j][1]);
			upd(f[i + 1][j][1], f[i][j][1]);
		}
	}
	int ans = f[n][m][1];
	rep(i, m + 1, n + 1) upd(ans, dp[n][i]);
	cout << ans << endl;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int T; cin >> T;
	while(T--) solve();
	return 0;
}

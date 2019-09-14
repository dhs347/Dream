#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); i++)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define de(x) cout << #x << " = " << x << endl
#define dd(x) cout << #x << " = " << x << " " 
#define endl '\n'
#define pw(x) (1ll<<(x))
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int N = 2e4 + 7;

int n, m;
ll dp[N];

void solve() {
	memset(dp, 0x3f, sizeof(dp));
	dp[0] = 0;
	rep(i, 1, n + 1) {
		int p, c; cin >> p >> c;
		rep(j, c, N) dp[j] = min(dp[j], dp[j - c] + p);
	}
	int ans = m;
	rep(i, m + 1, N) if(dp[i] <= dp[ans]) ans = i;
	cout << dp[ans] << " " << ans << endl;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	while(cin >> n >> m) solve();
	return 0;
}

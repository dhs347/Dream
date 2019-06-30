
#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define dd(a) cout << #a << " = " << a << " " 
#define de(a) cout << #a << " = " << a << endl
#define sz(a) (int)a.size()
#define all(a) a.begin(), a.end()
#define pw(a) (1ll << (a))
#define endl "\n"
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef double db;

const int N = 3e5;
ll a[N], sum, ans, f[2][10][24][3], m, n;

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n >> m;
	rep(i, 1, n+1) cin >> a[i], sum += a[i];
	int o = 0;
	memset(f[o], -10, sizeof(f[o]));
	f[o][0][10][1] = 0;
	rep(i, 1, n+1) {
		o ^= 1;
		memset(f[o], -10, sizeof(f[o]));
		rep(j, 0, m+1) rep(k, -j, j+1) rep(l, 0, 3) {
			int d = k + 10;
			if (l + 1 <= 2) {
				ll &t = f[o][j][d][l+1];
				t = max(t, f[o ^ 1][j][d][l] + a[i]);
			}
			if (k <= 0 && l + 1 <= 2 && j + 1 <= m) {
				ll &t = f[o][j+1][d-1][l+1];		
				t = max(t, f[o ^ 1][j][d][l]);
			}
			if (k >= 0 && j + 1 <= m) {
				ll &t = f[o][j+1][d+1][0];		
				t = max(t, f[o ^ 1][j][d][l] + a[i]);
			}
			if (k < 0) {
				ll &t = f[o][j][d+1][0];		
				t = max(t, f[o ^ 1][j][d][l] + a[i]);
			}
			if (k > 0 && l + 1 <= 2) {
				ll &t = f[o][j][d-1][l+1];		
				t = max(t, f[o ^ 1][j][d][l]);
			}
			ll &t = f[o][j][d][0];		
			t = max(t, f[o ^ 1][j][d][l]);
		}
	}
	//de(f[1][0][10][2]);
	rep(j, 0, m+1) rep(k, 0, 2) ans = max(ans, f[o][j][10][k]);
	cout << sum - ans << endl;
	return 0;
}

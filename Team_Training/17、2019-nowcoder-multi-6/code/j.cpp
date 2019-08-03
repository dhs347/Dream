#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define pb push_back
#define mp make_pair
#define de(x) cout << #x << " = " << x << endl
#define dd(x) cout << #x << " = " << x << " "
#define endl "\n"
#define pw(x) (1ll<<(x))
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()
typedef long long ll;
typedef pair<int, int> pii;
typedef double db;
typedef vector<int> vi;

const int N = 1e3 + 7;

int T, n, m;

ll a[N][N], b[N][N], suf[N][N], pre[N][N], ans, d[N];

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> T;
	rep(cas, 0, T) {
		cin >> n >> m;
		rep(i, 1, n+1) {
			a[i][0] = 0;
			rep(j, 1, m+1) cin >> a[i][j], a[i][j] = -a[i][j], a[i][j] += a[i][j-1];
		}
		rep(i, 1, m+1) cin >> d[i], d[i] += d[i-1];
		rep(i, 1, n+1) {
			rep(j, 1, m+1) b[i][j] = a[i][j];
		}
		rep(i, 1, n+1) 
			per(j, 0, m) a[i][j] = max(a[i][j], a[i][j+1]);
		ans = 0;
		rep(i, 0, m+1) {
			pre[1][i] = a[1][i];
			suf[n][i] = a[n][i];
			suf[n+1][i] = 0;
			rep(j, 2, n+1) pre[j][i] = pre[j-1][i] + a[j][i];
			per(j, 1, n) suf[j][i] = suf[j+1][i] + a[j][i];
			rep(j, 1, n+1) {	
				ans = max(ans, suf[j+1][i] + pre[j-1][i] + d[i] + b[j][i]);
			}
		}
		cout << "Case #" << cas + 1 << ": ";
		cout << ans << endl;
	}
	return 0;
}

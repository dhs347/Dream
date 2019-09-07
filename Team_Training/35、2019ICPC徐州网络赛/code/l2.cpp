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

int calc(int x, int y) {
	x = abs(x), y = abs(y);
	if(x > y) swap(x, y);
	if(x == 1 && y == 1) return x + y + 4;
	if(x <= 1 && y % 4) return x + y + 2;
	return x + y;
}
const int N = 16;
int n; pii p[N];
int f[pw(N)][N];
void solve() {
	cin >> n;
	rep(i, 0, n) cin >> p[i].fi >> p[i].se;
	memset(f, 0x3f, sizeof(f));
	int inf = f[0][0];
	rep(i, 0, n) f[pw(i)][i] = calc(p[i].fi, p[i].se);
	rep(i, 1, pw(n)) rep(j, 0, n) if(i >> j & 1) {
		rep(k, 0, n) if(!(i >> k & 1)) {
			int t = f[i][j] + calc(p[j].fi - p[k].fi, p[j].se - p[k].se);
			int ni = i | pw(k);
			f[ni][k] = min(f[ni][k], t);
		}
	}
	int ans = inf;
	rep(i, 0, n) ans = min(ans, f[pw(n) - 1][i]);
	cout << ans << endl;
}
int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int T; cin >> T;
	while(T--) solve();
	return 0;
}

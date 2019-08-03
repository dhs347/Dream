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

const int N = 2020;

int ans[N][N];

void solve() {
	int n; cin >> n;
	if(n * 1ll * (n - 1) % 4 || (n % 2 == 0 && n > 4)) {
		cout << "No" << endl;
		return ;
	}
	if(n > 5) {
		cout << "No" << endl;
		return ;
	}
	cout << "Yes" << endl;
	if(n == 1) {
		cout << 0 << endl << 1 << endl;
		return ;
	}
	if(n == 4) {
		cout << "0100" << endl;
		cout << "1010" << endl;
		cout << "0101" << endl;
		cout << "0010" << endl;
		cout << "2 4 1 3" << endl;
		return ;
	}
	rep(i, 0, n) rep(j, 0, n) ans[i][j] = 0;
	int t = (n - 1) >> 2;
	rep(i, 0, n) {
		rep(j, -t, t + 1) if(j) {
			int v = (i + j + n) % n;
			ans[i][v] = ans[v][i] = 1;
			//		dd(i), de(v);
		}
	}
	rep(i, 0, n) {
		rep(j, 0, n) cout << ans[i][j];
		cout << endl;
	}
	t = n >> 1; int now = 1;
	rep(i, 1, n + 1) {
		cout << now << " \n"[i == n];
		now = now + t;
		if(now > n) now -= n;
	}
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int T; cin >> T;
	rep(i, 1, T + 1) cout << "Case #" << i << ": ", solve();
	return 0;
}

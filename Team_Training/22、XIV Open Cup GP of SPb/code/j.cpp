#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define de(x) cout << #x << " = " << x << endl
#define dd(x) cout << #x << " = " << x << " "
#define endl '\n'
#define pw(x) (1ll<<(x))
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int N = 33;

int n;
int k[N][N], ind[N][N];
int m[N];
pii t[N][N * N];
int ans[N][N * N];

int main() {
	freopen("snakes2.in", "r", stdin);
	freopen("snakes2.out", "w", stdout);
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n;
	rep(i, 1, n + 1) {
		cin >> m[i];
		rep(j, 1, m[i] + 1) {
			int x, y; cin >> x >> y;
			t[i][j] = mp(x, y);
			if(k[x][y]) {
				ans[k[x][y]][ind[x][y]] = -1;
				ans[i][j] = 1;
			}
			k[x][y] = i, ind[x][y] = j;
		}
	}
	rep(i, 1, n + 1) {
		rep(j, 1, m[i] + 1) if(ans[i][j]) cout << (ans[i][j] > 0 ? '+' : '-');
		cout << endl;
	}
	return 0;
}

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
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef long long ll;

const int N = 5e4 + 1;

int n;
char s[N][5];
bitset<N> f[5][75], tmp;
vector<pii> vec;

void solve() {
	rep(i, 0, n) {
		tmp.reset();
		rep(j, 0, 5) tmp = (tmp | f[j][s[i][j] - 48]);
		tmp.flip();
		for(int j = tmp._Find_first(); j < n; j = tmp._Find_next(j)) {
			if(i < j) vec.pb(mp(i + 1, j + 1));
			if(sz(vec) == 100000) return ;
		}
	}
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n;
	rep(i, 0, n) cin >> s[i];
	rep(i, 0, 5) rep(j, 0, 75) rep(k, 0, n) if(s[k][i] - 48 == j) f[i][j][k] = 1;
	solve();
	cout << sz(vec) << endl;
	for(auto u : vec) cout << u.fi << " " << u.se << endl;
	return 0;
}

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

const int N = 101010;

int n;
int ans[10];
string s[N];

int ds[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
inline int leap(int y) {
	return (y % 4 == 0 && y % 100 != 0) || y % 400 == 0;
}
inline int legal(int y, int m, int d) {
	if(m == 2) return d <= 28 + leap(y);
	return d <= ds[m - 1];
}
inline int wd(int y, int m, int d) {
	int tm = m >= 3 ? (m - 2) : (m + 10);
	int ty = m >= 3 ? (y) : (y - 1);
	return (ty + ty / 4 - ty / 100 + ty / 400 + (int) (2.6 * tm - 0.2) + d) % 7;
}

inline bool check(const string &s) {
	int y = 0, m = 0, d = 0;
	rep(i, 0, 4) y = y * 10 + ans[s[i] - 'A'];
	if(y < 1600) return 0;
	rep(i, 5, 7) m = m * 10 + ans[s[i] - 'A'];
	if(m < 1 || m > 12) return 0;
	rep(i, 8, 10) d = d * 10 + ans[s[i] - 'A'];
	if(d < 1 || d > 31) return 0;
	if(!legal(y, m, d)) return 0;
	if(wd(y, m, d) != 5) return 0;
	return 1;
}

inline bool check() {
	rep(i, 1, n + 1) if(!check(s[i])) return 0;
	return 1;
}

void solve() {
	cin >> n;
	rep(i, 1, n + 1) cin >> s[i];
	sort(s + 1, s + 1 + n);
	n = unique(s + 1, s + 1 + n) - s - 1;
	random_shuffle(s + 1, s + 1 + n);
	rep(i, 0, 10) ans[i] = i;
	do {
		if(check()) {
			rep(i, 0, 10) cout << ans[i]; cout << endl;
			return ;
		}
	} while(next_permutation(ans, ans + 10));
	cout << "Impossible" << endl;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	srand(time(0));
	int T; cin >> T;
	rep(i, 1, T + 1) cout << "Case #" << i << ": ", solve();
	return 0;
}

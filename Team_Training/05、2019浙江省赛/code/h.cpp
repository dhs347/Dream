#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define sz(a) (int)a.size()
#define all(a) a.begin(), a.end()
#define pw(x) (1ll <<(x))
#define endl "\n"
#define de(a) cout << #a << " = " << a << endl
#define dd(a) cout << #a << " = " << a << " "
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef double db;

const int N = 101010;

int n;
int a[N];

bool check(int i, int j, int k) {
	if(i < 1) return 0;
	if(k > n) return 0;
	return a[i] < a[j] && a[j] > a[k];
}

void solve() {
	cin >> n;
	rep(i, 1, n + 1) cin >> a[i];
	int tot = 0;
	rep(i, 2, n) if(a[i - 1] < a[i] && a[i] > a[i + 1]) ++tot;
	int ans = tot;
	rep(i, 1, n + 1) {
		int res = tot;
		res -= check(i - 2, i - 1, i);
		res -= check(i - 1, i, i + 1);
		res -= check(i, i + 1, i + 2);
		res += check(i - 2, i - 1, i + 1);
		res += check(i - 1, i + 1, i + 2);
		ans = min(ans, res);
	}
	cout << ans << endl;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int T;
	cin >> T;
	while(T--) {
		solve();
	}
	return 0;
}

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

const int N = 1010;

int n, k, a[N];
multiset<int> st;

bool check(int x) {
	st.clear();
	rep(i, 1, n + 1) st.insert(a[i]);
	rep(i, 1, k + 1) {
		int now = x;
		while(1) {
			auto u = st.upper_bound(now);
			if(u == st.begin()) break;
			--u; now -= *u;
			st.erase(u);
		}
	}
	return sz(st) == 0;
}

void solve() {
	cin >> n >> k; int tot = 0;
	rep(i, 1, n + 1) cin >> a[i], tot += a[i];
	for(int i = (tot + k - 1) / k; ; ++i) if(check(i)) {
		cout << i << endl;
		break;
	}
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int T; cin >> T;
	rep(i, 1, T + 1) cout << "Case #" << i << ": ", solve();
	return 0;
}

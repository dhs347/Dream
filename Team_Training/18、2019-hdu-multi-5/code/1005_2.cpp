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
#define pw(x) (1ll<<(x))
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()
#define endl "\n"
typedef long long ll;
typedef pair<int, int> pii;
typedef double db;
typedef vector<int> vi;

const int N = 44;

int n, cnt;
int b[40404][N], arr[40404];
vi ans[N];
vector<pii> Q[N];

bool cmp(int i, int j) {
	rep(t, 2, n + 1) if(b[i][t] - b[i][t - 1] != b[j][t] - b[j][t - 1]) {
		return b[i][t] - b[i][t - 1] < b[j][t] - b[j][t - 1];
	}
}

void solve() {
	if(!sz(Q[n])) return ;
	int a[N]; cnt = 0;
	if(n > 8) {
		a[1] = n; rep(i, 2, n + 1) a[i] = i - 1;
	} else {
		rep(i, 1, n + 1) a[i] = i;
	}
	int t = a[n - 8];
	do {
		if(n > 8 && a[n - 8] != t) break;
		++cnt;
		rep(i, 1, n + 1) b[cnt][i] = a[i];
	} while(next_permutation(a + 1, a + 1 + n));

	rep(i, 1, cnt + 1) arr[i] = i;
	for(auto u : Q[n]) {
		int k = u.fi, i = u.se;
		nth_element(arr + 1, arr + k, arr + cnt + 1, cmp);
		rep(t, 1, n + 1) ans[i].pb(b[arr[k]][t]);
	}
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int T; cin >> T;
	rep(i, 1, T + 1) {
		int n, k; cin >> n >> k;
		n = min((i + 3) / 2, 20), k = n;
		dd(n), de(k);
		Q[n].pb(mp(k, i));
	}
	rep(i, 2, 21) n = i, solve();
	rep(i, 1, T + 1) {
		rep(j, 0, sz(ans[i])) cout << ans[i][j] << " \n"[j == sz(ans[i]) - 1];
	}
	return 0;
}

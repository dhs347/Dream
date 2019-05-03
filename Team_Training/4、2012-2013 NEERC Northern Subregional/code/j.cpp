#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define sz(a) (int)a.size()
#define de(a) cout << #a << " = " << a << endl
#define dd(a) cout << #a << " = " << a << " "
#define all(a) a.begin(), a.end()
#define pw(x) (1ll << (x))
#define endl "\n"
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int N = 250;

int n, l;
int ans[N][2][11];
bool vis[N];

int calc(string &s) {
	int val = 0;
	rep(i, 0, sz(s)) {
		int c = 0;
		if(s[i] == '=') c = 1;
		else if(s[i] == '>') c = 2;
		val = val * 3 + c;
	}
	return val;
}
int calc(int a[], int b[]) {
	int val = 0;
	rep(i, 0, 5) {
		int c = 0;
		if(a[i] == b[i]) c = 1;
		else if(a[i] > b[i]) c = 2;
		val = val * 3 + c;
	}
	return val;
}
int LIS(int a[], int n) {
	int dp[11] = {0};
	rep(i, 1, n + 1) {
		dp[i] = 1;
		rep(j, 1, i) if(a[j] < a[i]) dp[i] = max(dp[i], dp[j] + 1);
	}
	int ans = 0;
	rep(i, 1, n + 1) ans = max(ans, dp[i]);
	return ans;
}
int lis(int a[], int n) {
	int dp[11] = {0};
	rep(i, 1, n + 1) {
		dp[i] = 1;
		if(i > 1 && a[i - 1] < a[i]) dp[i] += dp[i - 1];
	}
	int ans = 0;
	rep(i, 1, n + 1) ans = max(ans, dp[i]);
	return ans;
}
void gao(int a[], int n, int b[]) {
	rep(i, 0, 5) b[i] = 0;
	rep(i, 1, n + 1) rep(j, i + 1, n + 1) if(a[i] > a[j]) ++b[0];
	rep(i, 2, n + 1) if(a[i - 1] > a[i]) ++b[1];
	b[2] = LIS(a, n);
	b[3] = lis(a, n);
	rep(i, 1, n + 1) b[4] += (a[i] == i);
}
void print(int a[]) {
	rep(i, 1, n + 1) cout << a[i] << " \n"[i == n];
}
void solve1() {
	int cnt = 0;
	int a[11]; rep(i, 1, n + 1) a[i] = i;
	do {
		int aa[11];
		int b[11]; rep(i, 1, n + 1) b[i] = i;
		gao(a, n, aa);
		do {
			int bb[11];
			gao(b, n, bb);
			int val = calc(aa, bb);
			if(!vis[val]) {
				vis[val] = 1;
				rep(i, 1, n + 1) ans[val][0][i] = a[i], ans[val][1][i] = b[i];
			}
		} while(next_permutation(b + 1, b + 1 + n));
	} while(next_permutation(a + 1, a + 1 + n));
	rep(i, 1, l + 1) {
		string s;
		cin >> s;
		int val = calc(s);
		if(vis[val]) {
			cout << "Exists" << endl;
			rep(i, 1, n + 1) cout << ans[val][0][i] << " \n"[i == n];
			rep(i, 1, n + 1) cout << ans[val][1][i] << " \n"[i == n];
		} else {
			cout << "Not exists" << endl;
		}
	}
}
void print(vi a) {
	for(auto u : a) cout << u << " ";cout << endl;
}
namespace SOL {
	int M = 6;
	vector<pair<vi, vi> > pp;
	bool vis[N];
	pair<vi, vi> ans[N];
	void add(int a[], int m) {
		int aa[11];
		gao(a, m, aa);
		pp.pb(mp(vi(a + 1, a + 1 + m), vi(aa, aa + 5)));

	}
	void init() {
		int m = M;
		int a[11]; rep(i, 1, m + 1) a[i] = i;
		do {
			if(a[m] != m) {
				add(a, m);
			}
		} while(next_permutation(a + 1, a + 1 + m));
	}
	void solve() {
		init();
		int cnt = 0;
		rep(i, 0, sz(pp)) {
			auto a = pp[i].fi, aa = pp[i].se;
			rep(j, i, sz(pp)) {
				auto b = pp[j].fi, bb = pp[j].se;
				int val = calc(aa.data(), bb.data());
				if(!vis[val]) {
					++cnt;
					vis[val] = 1;
					ans[val] = mp(a, b);
				}
			}
		}
		while(l--) {
			string s;
			cin >> s;
			int val = calc(s);
			if(vis[val]) {
				cout << "Exists" << endl;
				vi a = ans[val].fi;
				vi b = ans[val].se;
				per(i, M + 1, n + 1) a.pb(i), b.pb(i);
				rep(i, 0, sz(a)) cout << a[i] << " \n"[i == sz(a) - 1];
				rep(i, 0, sz(a)) cout << b[i] << " \n"[i == sz(a) - 1];
			} else {
				cout << "Not exists" << endl;
			}
		}
	}
}

int main() {
	freopen("juggle.in", "r", stdin);
	freopen("juggle.out", "w", stdout);
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> l >> n;
	if(n <= 6) {
		solve1();
	} else {
		SOL::solve();
	}
	return 0;
}

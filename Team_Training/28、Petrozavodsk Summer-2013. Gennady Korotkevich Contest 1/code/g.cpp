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
typedef pair<int, int> pii;
typedef double db;
typedef vector<int> vi;

const int N = 1e6 + 7;

int n;
int a[N], b[N], pre[N], dp[N], f[N], st[N], ed[N];

int main() {
//	freopen("gem.in", "r", stdin);
//	freopen("gem.out", "w", stdout);
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n;
	rep(i, 1, n + 1) {
		cin >> a[i]; b[i] = a[i];
		ed[a[i]] = i;
	}
	per(i, 1, n + 1) {
		st[a[i]] = i;
	}
	sort(b + 1, b + 1 + n);
	rep(i, 2, n + 1) if(b[i] != b[i - 1]) {
		pre[b[i]] = b[i - 1];
	}
	int ans = 0;
	rep(i, 1, n + 1) {
		int x = a[i], y = pre[x];
		int k = f[x];
		if(ed[y] <= st[x]) k = max(k, f[y]);
		dp[i] = k + 1;
	//	dd(i), de(dp[i]);
		ans = max(ans, k + 1);
		f[a[i]] = max(f[a[i]], k + 1);
	}
	cout << n - ans << endl;
	return 0;
}

#include<bits/stdc++.h>
using namespace std;
#define fi first 
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a) --i)
#define de(c) cout << #c << " = " << c << endl
#define dd(c) cout << #c << " = " << c << " "
#define all(c) c.begin(), c.end()
#define sz(x) (int)x.size()
#define endl '\n'
#define pw(x) (1ll << (x))
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef double db;

const int N = 5e5 + 7;
int ans1, ans2, cnt[10], ma[N], mi[N], d = 140000, n, a[N];
string s;

void upd(int x, int p) {
	mi[x] = min(mi[x], p);
	ma[x] = max(ma[x], p);
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n >> s;
	rep(i, 1, n+1) if (s[i-1] == '0') a[i] = 1;else a[i] = -1;
	memset(mi, 10, sizeof(mi));
	memset(ma, -10, sizeof(ma));
	rep(i, 1, n+1) cnt[s[i-1] - '0']++, a[i] += a[i-1], upd(a[i] + d, i);
	upd(d, 0);
	rep(i, 1, n+1) ans1 = max(ans1, ma[a[i]+d] - mi[a[i]+d]);
	ans2 = min(cnt[1], cnt[0]) * 2;
	cout << ans1 << " " << ans2 << endl;
	return 0;
}

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
int l[N], r[N], a[N], cnt, ans, pp, rr;
vi tmp, p[N];
int main() {
	freopen("gem.in", "r", stdin);
	freopen("gem.out", "w", stdout);
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n;
	memset(l, 10, sizeof(l));
	memset(r, -10, sizeof(l));
	rep(i, 1, n + 1) {
		cin >> a[i]; tmp.pb(a[i]);
		p[a[i]].pb(i);
		l[a[i]] = min(l[a[i]], i);
		r[a[i]] = max(r[a[i]], i);
	}
	sort(all(tmp));
	tmp.erase(unique(all(tmp)), tmp.end());
	rep(i, 0, sz(tmp)) ans = max(ans, sz(p[tmp[i]]));
	rep(i, 1, sz(tmp)) {
		rep(j, 0, sz(p[tmp[i]])) {
			int pp = p[tmp[i]][j];
			int c = upper_bound(all(p[tmp[i-1]]), pp) - p[tmp[i-1]].begin();
			ans = max(ans, c + sz(p[tmp[i]]) - j);
		}
	}
	rr = 0;cnt = sz(p[tmp[0]]);
	rep(i, 0, sz(tmp)) {
		if (rr < i) rr = i, cnt += sz(p[tmp[i]]);
		while (rr + 1 < sz(tmp) && l[tmp[rr+1]] > r[tmp[rr]]) 
			rr++, cnt += sz(p[tmp[rr]]);
		int c1 = 0, c2 = 0;
		pp = r[tmp[rr]];
		if (rr + 1 < sz(tmp)) {
			int u = tmp[rr+1];
			c1 = sz(p[u]) - (upper_bound(all(p[u]), pp) - p[u].begin());
		}
		if (i - 1 >= 0) {
			int u = tmp[i-1];
			pp = l[tmp[i]];
			c2 = upper_bound(all(p[u]), pp) - p[u].begin();
		}
	//	dd(i), dd(rr), dd(c1), dd(c2), de(cnt);
		ans = max(ans, cnt + c1 + c2);
		cnt -= sz(p[tmp[i]]);
	}
	cout << n - ans << endl;
	return 0;
}

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
#define endl "\n"
#define all(a) a.begin(), a.end()
#define sz(a) (int)a.size()
typedef long long ll;
typedef double db;
typedef vector<int> vi;
typedef pair<int, int> pii;

const int N = 202020;

int n, k, a[N];
ll pre[N];
vector<ll> V;

int F(ll x) {
	return lower_bound(all(V), x) - V.begin() + 1;
}

struct Seg {
#define ls rt << 1
#define rs ls | 1
	static const int N = ::N << 2;
	int ma[N];
	void build(int l, int r, int rt) {
		ma[rt] = -1e9;
		if(l == r) return ;
		int mid = l + r >> 1;
		build(l, mid, ls);
		build(mid + 1, r, rs);
	}
	void upd(int p, int c, int l, int r, int rt) {
		ma[rt] = max(ma[rt], c);
		if(l == r) return ;
		int mid = l + r >> 1;
		if(p <= mid) upd(p, c, l, mid, ls);
		else upd(p, c, mid + 1, r, rs);
	}
	int qry(int L, int R, int l, int r, int rt) {
		if(L > R) return -1e9;
		if(L <= l && r <= R) return ma[rt];
		int mid = l + r >> 1, ans = -1e9;
		if(L <= mid) ans = max(ans, qry(L, R, l, mid, ls));
		if(R > mid) ans = max(ans, qry(L, R, mid + 1, r, rs));
		return ans;
	}
}seg;

bool check(ll x) {
	seg.build(1, sz(V), 1);
	seg.upd(F(0), 0, 1, sz(V), 1);
	rep(i, 1, n + 1) {
		int t = seg.qry(F(pre[i] - x), sz(V), 1, sz(V), 1);
		if(t >= 0) {
			int dp = t + 1;
			if(dp >= k) return 1;
			seg.upd(F(pre[i]), dp, 1, sz(V), 1);
		} 
	}
	return 0;
}

void solve() {
	cin >> n >> k;
	V.clear();
	rep(i, 1, n + 1) cin >> a[i], pre[i] = pre[i - 1] + a[i], V.pb(pre[i]);
	V.pb(0);
	sort(all(V));
	V.erase(unique(all(V)), V.end());
	ll l = -2e14 - 2, r = -l, ans = -1;
	while(l <= r) {
		ll mid = (l + r) / 2;
		if(check(mid)) {
			ans = mid;
			r = mid - 1;
		} else {
			l = mid + 1;
		}
	}
	cout << ans << endl;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int T; cin >> T;
	while(T--) solve();
	return 0;
}

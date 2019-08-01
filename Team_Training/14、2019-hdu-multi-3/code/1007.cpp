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

int n, m, a[N], ans;
vi V;

int F(int x) {
	return lower_bound(all(V), x) - V.begin() + 1;
}

struct Seg {
#define ls rt << 1
#define rs ls | 1
	static const int N = ::N << 2;
	ll sum[N]; int cnt[N];
	void build(int n) {
		fill_n(sum, n << 2 | 1, 0);
		fill_n(cnt, n << 2 | 1, 0);
	}
	void upd(int p, int l, int r, int rt) {
		sum[rt] += V[p - 1];
		++cnt[rt];
		if(l == r) return ;
		int mid = l + r >> 1;
		if(p <= mid) upd(p, l, mid, ls);
		else upd(p, mid + 1, r, rs);
	}
	void qry(int m, int l, int r, int rt) {
		if(sum[rt] <= m) {
			ans += cnt[rt];
			return ;
		}
		if(l == r) {
			int t = m / V[l - 1];
			m -= t * V[l - 1];
			ans += t;
			return ;
		}
		int mid = l + r >> 1;
		if(sum[ls] <= m) {
			ans += cnt[ls];
			qry(m - sum[ls], mid + 1, r, rs);
		} else {
			qry(m, l, mid, ls);
		}
	}
}seg;

void solve() {
	cin >> n >> m;
	V.clear(); rep(i, 1, n + 1) cin >> a[i], V.pb(a[i]);
	sort(all(V)); V.erase(unique(all(V)), V.end());
	seg.build(sz(V));
	rep(i, 1, n + 1) {
		ans = 0;
		seg.qry(m - a[i], 1, sz(V), 1);
		seg.upd(F(a[i]), 1, sz(V), 1);
		ans = i - 1 - ans;
		cout << ans << " \n"[0];
	}
	cout << endl;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int T; cin >> T;
	while(T--) solve();
	return 0;
}

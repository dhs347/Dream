#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define dd(a) cout << #a << " = " << a << " " 
#define de(a) cout << #a << " = " << a << endl
#define sz(a) (int)a.size()
#define all(a) a.begin(), a.end()
#define pw(a) (1ll << (a))
#define endl "\n"
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef double db;

const int N = 303030;

int n, c[N], d[N];
ll ans[N];
vi vec[N];

struct Seg {
#define ls rt << 1
#define rs ls | 1
	static const int N = ::N << 2;
	ll ma[N];
	void upd(int p, ll c, int l, int r, int rt, bool del = 0) {
		if(l == r) {
			if(del) ma[rt] = c;
			else ma[rt] = max(ma[rt], c);
			return ;
		}
		int mid = l + r >> 1;
		if(p <= mid) upd(p, c, l, mid, ls, del);
		else upd(p, c, mid + 1, r, rs, del);
		ma[rt] = max(ma[ls], ma[rs]);
	}
	ll qry(int L, int R, int l, int r, int rt) {
		if(L <= l && r <= R) return ma[rt];
		int mid = l + r >> 1;
		ll ans = 0;
		if(L <= mid) ans = max(ans, qry(L, R, l, mid, ls));
		if(R > mid) ans = max(ans, qry(L, R, mid + 1, r, rs));
		return ans;
	}
}seg;

bool cmp(int i, int j) {
	return c[i] > c[j];
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n;
	rep(i, 1, n + 1) {
		cin >> c[i];
		int t = i - c[i] + 1;
		if(1 <= t && t <= n) vec[t].pb(i);
	}
	rep(i, 1, n + 1) sort(all(vec[i]), cmp);
	rep(i, 1, n + 1) cin >> d[i];
	rep(i, 1, n + 1) {
		for(auto I : vec[i]) {
			if(1 <= c[I] && c[I] <= n - i + 1) {
		//		de(1);
				ll ma = seg.qry(c[I] + i - 1, n, 0, n, 1) + d[I];
				seg.upd(c[I] + i - 2, ma, 0, n, 1);
			}
		}
		ans[i] = seg.qry(i - 1, n, 0, n, 1);
//		rep(j, 0, n - i + 2) dd(j), de(seg.qry(j + i - 1, n, 0, n, 1));
//		cout << endl;
		if(i != n) {
			if(2 <= c[i] && c[i] <= n - i + 1) {
			//	de(2);
				ll ma = seg.qry(c[i] + i - 1, n, 0, n, 1) + d[i];
				seg.upd(c[i] + i - 1, ma, 0, n, 1);
			}
			seg.upd(i, 0, 0, n, 1, 1);
		}
	}
	rep(i, 1, n + 1) cout << ans[i] << " \n"[i == n];
	return 0;
}

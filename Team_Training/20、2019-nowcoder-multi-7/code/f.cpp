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
#define all(x) x.begin(), x.end()
#define pw(x) (1ll<<(x))
#define sz(x) (int)x.size()
typedef long long ll;
typedef pair<int, int> pii;
typedef double db;
typedef vector<int> vi;

const int N = 101010;

int n, m;
int e[N], l[N], c[N];
ll ans;

struct Seg {
#define ls rt << 1
#define rs ls | 1
	vi t[N << 2];
	void upd(int L, int R, int c, int l, int r, int c) {
		if(L <= l && r <= R) {
			t[rt].pb(c);
			return ;
		}
		int mid = l + r >> 1;
		if(L <= mid) upd(L, R, c, l, mid, ls);
		if(R > mid) upd(L, R, c, mid + 1, r, rs);
	}
}seg;

void solve() {
	ans = 0;
	cin >> n;
	rep(i, 1, n + 1) cin >> e[i] >> l[i] >> c[i];
	cin >> m;
	rep(i, 1, m + 1) {
		int t, l, r;
		cin >> t >> l >> r;
		seg.upd(l, r, t, 1, n, 1);
	}
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int T; cin >> T;
	rep(i, 1, T + 1) {
		solve();
		cout << "Case #" << i << ": " << ans << endl;
	}
	return 0;
}

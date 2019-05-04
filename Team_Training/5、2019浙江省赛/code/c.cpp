#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define sz(a) (int)a.size()
#define all(a) a.begin(), a.end()
#define pw(x) (1ll <<(x))
#define endl "\n"
#define de(a) cout << #a << " = " << a << endl
#define dd(a) cout << #a << " = " << a << " "
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef double db;

const int N = 101010;

int n;
int arr[N], a[N], b[N], mi[N], ans[N];

struct Seg {
#define ls rt << 1
#define rs ls | 1
	static const int N = ::N << 2;
	int sum[N], ma[N];
	void up(int rt) {
		sum[rt] = sum[ls] + sum[rs];
		ma[rt] = max(ma[ls], ma[rs]);
	}
	void build(int l, int r, int rt) {
		if(l == r) {
			sum[rt] = b[l];
			ma[rt] = a[l] + b[l];
			return ;
		}
		int mid = l + r >> 1;
		build(l, mid, ls);
		build(mid + 1, r, rs);
		up(rt);
	}
	void upd(int p, int o, int l, int r, int rt) {
		if(l == r) {
			if(o == 0) --a[l]; else --b[l];
			mi[l] = min(a[l], b[l]);
			sum[rt] = b[l];
			ma[rt] = a[l] + b[l];
			return ;
		}
		int mid = l + r >> 1;
		if(p <= mid) upd(p, o, l, mid, ls);
		else upd(p, o, mid + 1, r, rs);
		up(rt);
	}
	// o = 0 / 1
	int qry(int L, int R, int l, int r, int rt, int o) {
		if(L > R) return 0;
		if(L <= l && r <= R && (l == r || (o == 0 ? (ma[rt] < ma[1] || sum[rt] == 0) : sum[rt] == 0))) {
			if(o == 0 ? (ma[rt] == ma[1] && sum[rt]) : sum[rt]) return l;
			return 0;
		}
		int mid = l + r >> 1;
		if(L <= mid) {
			int t = qry(L, R, l, mid, ls, o);
			if(t) return t;
		} 
		if(R > mid) {
			int t = qry(L, R, mid + 1, r, rs, o);
			if(t) return t;
		}
		return 0;
	}
}seg;

int find(int p, int l) {
	int ans = 0;
	if(seg.ma[1] > l) {
		ans = seg.qry(1, p - 1, 1, n, 1, 0);
		if(ans) return ans;
		ans = seg.qry(p + 1, n, 1, n, 1, 0);
		if(ans) return ans;
	}
	ans = seg.qry(1, p - 1, 1, n, 1, 1);
	if(ans) return ans;
	return seg.qry(p + 1, n, 1, n, 1, 1);
}

void solve() {
	cin >> n;
	rep(i, 1, n + 1) a[i] = 0;
	rep(i, 1, n + 1) cin >> arr[i], ++a[arr[i]];
	rep(i, 1, n + 1) b[i] = mi[i] = a[i];
	seg.build(1, n, 1);
	rep(i, 1, n + 1) {
		if(seg.ma[1] > (n - i + 1)) {
			cout << "Impossible" << endl;
			return ;
		}
		int p = arr[i], q = find(p, (n - i));
		seg.upd(p, 0, 1, n, 1);
		seg.upd(q, 1, 1, n, 1);
		ans[i] = q;
		//	rep(i, 1, n + 1) dd(a[i]), dd(b[i]), de(mi[i]); cout << endl;
	}
	rep(i, 1, n + 1) cout << ans[i] << " \n"[i == n];
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int T;
	cin >> T;
	while(T--) {
		solve();
	}
	return 0;
}

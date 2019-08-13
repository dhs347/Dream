#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define de(x) cout << #x << " = " << x << endl
#define dd(x) cout << #x << " = " << x << " " 
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define endl '\n'
#define pw(x) (1ll <<(x))
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int N = 3e5 + 1, inf = 1e9 + 7;

int n, m, a[N], q, rt[N];
ll res;
vi vec[N];

struct Seg {
	static const int N = ::N * 67;
	int ls[N], rs[N], cntn;
	int la[N];
	void upd(int L, int R, ll c, int pre, int &now, int l = 1, int r = m) {
		now = ++cntn;
		assert(cntn < N);
		ls[now] = ls[pre];
		rs[now] = rs[pre];
		la[now] = la[pre];
		if(L > R) return ;
		if(L <= l && r <= R) {
			la[now] += c;
			la[now] = min(inf, la[now]);
			return ;
		}
		int mid = l + r >> 1;
		if(L <= mid) upd(L, R, c, ls[pre], ls[now], l, mid);
		if(R > mid) upd(L, R, c, rs[pre], rs[now], mid + 1, r);
	}
	void qry(int p, int rt, int l = 1, int r = m) {
		if(!rt) return ;
		if(res > inf) return ;
		res += la[rt];
		if(res > inf) return ;
		if(l == r) return ;
		int mid = l + r >> 1;
		if(p <= mid) qry(p, ls[rt], l, mid);
		else qry(p, rs[rt], mid + 1, r);
	}
}seg;

void solve(int u) {
	int l = 1, r = q, ans = -1;
	while(l <= r) {
		int mid = l + r >> 1;
		res = 0;
		for(auto i : vec[u]) {
			if(res >= a[u]) break;
			seg.qry(i, rt[mid]);
		}
		if(res >= a[u]) {
			ans = mid;
			r = mid - 1;
		} else {
			l = mid + 1;
		}
	}
	if(~ans) cout << ans << endl;
	else cout << "NIE" << endl;
}

int main() {
	//	db x = sizeof(seg);
//		de(x / 1024 / 1024);
	freopen("meteors.in", "r", stdin);
	freopen("meteors.out", "w", stdout);
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n >> m;
	rep(i, 1, m + 1) {
		int x; cin >> x;
		vec[x].pb(i);
	}
	rep(i, 1, n + 1) cin >> a[i];
	cin >> q;
	rep(i, 1, q + 1) {
		int l, r, c; cin >> l >> r >> c;
		if(l <= r) {
			seg.upd(l, r, c, rt[i - 1], rt[i]);
		} else {
			seg.upd(l, m, c, rt[i - 1], rt[i]);
			seg.upd(1, r, c, rt[i], rt[i]);
			//seg.upd(r + 1, l - 1, -c, rt[i - 1], rt[i]);
			//seg.la[rt[i]] += c;
		}
	}
	rep(i, 1, n + 1) solve(i);
	return 0;
}

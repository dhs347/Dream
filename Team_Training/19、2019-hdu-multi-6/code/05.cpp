#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define dd(x) cout << #x << " = " << x << " "
#define de(x) cout << #x << " = " << x << endl
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()
#define endl '\n'
#define pw(x) (1ll<<(x))
typedef long long ll;
typedef pair<int, int> pii;
typedef double db;
typedef vector<int> vi;

const int N = 2020;

int n;
vi V; int F(int x) { return lower_bound(all(V), x) - V.begin() + 1; }

struct Node {
	int x, y, w; 
	void read() { cin >> x >> y >> w; V.pb(y); }
	bool operator < (const Node &c) const {
		if(x != c.x) return x < c.x;
		return y < c.y;
	}
}nd[N];

struct Seg {
#define ls rt << 1
#define rs ls | 1
	static const int N = ::N << 2;
	ll mx[N], lmx[N], rmx[N], sum[N];
	void build(int l, int r, int rt) {
		mx[rt] = lmx[rt] = rmx[rt] = sum[rt] = 0;
		if(l == r) return ;
		int mid = l + r >> 1;
		build(l, mid, ls);
		build(mid + 1, r, rs);
	}
	void up(int rt) {
		sum[rt] = sum[ls] + sum[rs];
		mx[rt] = max(mx[ls], mx[rs]);
		mx[rt] = max(mx[rt], rmx[ls] + lmx[rs]);
		lmx[rt] = max(lmx[ls], sum[ls] + lmx[rs]);
		rmx[rt] = max(rmx[rs], sum[rs] + rmx[ls]);
	}
	void upd(int p, ll c, int l, int r, int rt) {
		if(l == r) {
			sum[rt] += c;
			mx[rt] = lmx[rt] = rmx[rt] = max(0ll, sum[rt]);
			return ;
		}
		int mid = l + r >> 1;
		if(p <= mid) upd(p, c, l, mid, ls);
		else upd(p, c, mid + 1, r, rs);
		up(rt);
	}
}seg;

void solve() {
	cin >> n;
	V.clear();
	rep(i, 1, n + 1) nd[i].read();
	sort(nd + 1, nd + 1 + n);
	sort(all(V));
	V.erase(unique(all(V)), V.end());
	ll ans = 0;
	rep(i, 1, n + 1) if(i == 1 || nd[i].x != nd[i - 1].x) {
		seg.build(1, sz(V), 1);
		rep(j, i, n + 1) {
			seg.upd(F(nd[j].y), nd[j].w, 1, sz(V), 1);
			if(j == n || nd[j].x != nd[j + 1].x) ans = max(ans, seg.mx[1]);
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

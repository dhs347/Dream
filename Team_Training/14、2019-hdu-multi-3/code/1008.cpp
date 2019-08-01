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

const int N = 1e5 + 4, B = 2154;

int n, m, a[N], b[N], blo[N], cnt[pw(21)];
int op[N];
ll ans[N], res;

struct Node {
	int o, l, r, i, t;
	Node() {}
	Node(int o, int l, int r, int t) : o(o), l(l), r(r), t(t) {}
	bool operator < (const Node &c) const {
		if(blo[l] != blo[c.l]) return blo[l] < blo[c.l];
		if(blo[r] != blo[c.r]) return blo[r] < blo[c.r];
		return (t < c.t) ^ (blo[r] & 1);
	}
}nd[N];

void upd(int p, int c) {
	if(c == 1) {
		res += cnt[p];
		++cnt[p];
	} else {
		--cnt[p];
		res -= cnt[p];
	}
}
int l, r, t;

void Upd(int p, int c) {
	int x = op[p];
	if(x < 0) return ;
	swap(a[x], a[x + 1]);
	if(l <= x && x <= r) upd(b[x], -1);
	b[x] = b[x - 1] ^ a[x];
	if(l <= x && x <= r) upd(b[x], 1);
}

void solve() {
	rep(i, 1, n + 1) cin >> a[i], b[i] = b[i - 1] ^ a[i];
	rep(i, 1, m + 1) {
		cin >> nd[i].o;
		if(nd[i].o == 1) {
			cin >> nd[i].l >> nd[i].r;
			int t = nd[i].r - nd[i].l + 2;
			ans[i] = t * 1ll * (t - 1) / 2;
			nd[i].l--;
			op[i] = -1;
		} else {
			cin >> nd[i].i;
			ans[i] = -1;
			op[i] = nd[i].i;
		}
		nd[i].t = i;
	}
	l = 1, r = t = 0;
	sort(nd + 1, nd + 1 + m);
	nd[m + 1] = Node(1, 1, 0, 0);
	rep(i, 1, m + 2) {
		if(nd[i].o == 1) {
			while(l < nd[i].l) upd(b[l++], -1);
			while(l > nd[i].l) upd(b[--l], 1);
			while(r < nd[i].r) upd(b[++r], 1);
			while(r > nd[i].r) upd(b[r--], -1);
			while(t < nd[i].t) Upd(++t, 1);
			while(t > nd[i].t) Upd(t--, -1);
			ans[nd[i].t] -= res;
		}
	}
	rep(i, 1, m + 1) if(ans[i] >= 0) cout << ans[i] << endl;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	rep(i, 0, N) blo[i] = i / B;
	while(cin >> n >> m) solve();
	return 0;
}

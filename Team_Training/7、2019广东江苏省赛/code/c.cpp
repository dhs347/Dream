#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define endl "\n"
#define pw(x) (1ll << (x))
#define all(x) x.begin(), x.end()
#define sz(a) (int)a.size()
#define de(x) cout << #x << " = " << x << endl
#define dd(x) cout << #x << " = " << x << " "
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int N = 27000 + 5;
int B;

int n, m, k;
int a[N];
ll res;
ll ans[N];
vi vec;
struct Node {
	int l, r, ind;
	bool operator < (const Node &c) const {
		if(l / B != c.l / B) return l / B < c.l / B;
		return (r < c.r) ^ ((l / B) & 1);
	}
}nd[N];
inline int F(int x) {
	return lower_bound(all(vec), x) - vec.begin() + 1;
}
#define lb(x) ((x)&-(x))
struct Fenwick {
	int n; int a[N];
	void ini(int _n) {
		n = _n; fill_n(a + 1, n, 0);
	}
	void upd(int p, int c) {
		for( ; p <= n; p += lb(p)) a[p] += c;
	}
	int _qry(int p) {
		int r = 0;
		for( ; p; p -= lb(p)) r += a[p];
		return r;
	}
	int qry(int l, int r) {
		if(l > r) return 0;
		return _qry(r) - _qry(l - 1);
	}
}fw;
void upd(int p, int c) {
	int x = a[p];
	if(c == -1) fw.upd(F(x), c);
	int l = F(x - k), r = upper_bound(all(vec), x + k) - vec.begin();
	res += c * fw.qry(l, r);
	if(c == 1) fw.upd(F(x), c);
}
int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int inf = 1e9;
	while(cin >> n >> m >> k) {
		B = sqrt(n);
		k = rand() % inf + 1;
		vec.clear();
		res = 0;
		rep(i, 1, n + 1) a[i] = rand() % inf + 1, vec.pb(a[i]);
//		rep(i, 1, n + 1) cin >> a[i], vec.pb(a[i]);
		sort(all(vec));
		vec.erase(unique(all(vec)), vec.end());
		fw.ini(sz(vec));
		rep(i, 1, m + 1) {
			nd[i].l = rand() % n + 1;
			nd[i].r = rand() % n + 1;
			if(nd[i].l > nd[i].r) swap(nd[i].l, nd[i].r);
			nd[i].ind = i;
		//	cin >> nd[i].l >> nd[i].r, nd[i].ind = i;
		}
		sort(nd + 1, nd + 1 + m);
		int l = 1, r = 0;
		rep(i, 1, m + 1) {
			while(l < nd[i].l) upd(l++, -1);
			while(l > nd[i].l) upd(--l, 1);
			while(r < nd[i].r) upd(++r, 1);
			while(r > nd[i].r) upd(r--, -1);
			ans[nd[i].ind] = res;
		}
		rep(i, 1, m + 1) cout << ans[i] << endl;
	}
	return 0;
}

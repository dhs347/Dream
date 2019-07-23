#include<bits/stdc++.h>
using namespace std;
#define fi first 
#define se second
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define mp make_pair
#define pb push_back
#define de(x) cout << #x << " = " << x << endl
#define dd(x) cout << #x << " = " << x << " "
#define endl '\n'
#define all(a) a.begin(), a.end()
#define sz(a) (int)a.size()
#define pw(x) (1ll << (x))
typedef long long ll;
typedef pair<int, int> pii;
typedef double db;
typedef vector<int> vi;

const int N = pw(20) + 10;
const char M = 30;

int n, m, pans;

struct Node {
	int a[M];
	char sz;
	Node() { }
	inline void add(int x) {
		for(int i = M - 1; i >= 0 && x; --i) if(x >> i & 1) {
			if(a[i] == 0) {
				a[i] = x;
				++sz;
				break;
			} 
			x ^= a[i];
		}
	}
	inline void init() {
		fill_n(a, M, 0); sz = 0;
	}
	inline Node operator + (const Node &c) const {
		if(sz > c.sz) {
			const Node &a = *this, &b = c;	
			if(a.sz == M) return a;
			Node res = a;
			rep(i, 0, M) if(b.a[i]) {
				res.add(b.a[i]);
				if(res.sz == M) return res;
			}
			return res;
		} else {
			const Node &b = *this, &a = c;	
			if(a.sz == M) return a;
			Node res = a;
			rep(i, 0, M) if(b.a[i]) {
				res.add(b.a[i]);
				if(res.sz == M) return res;
			}
			return res;
		}
	}
}ans;

struct Seg {
#define ls rt << 1
#define rs ls | 1
	static const int N = (::N << 1) + 10;
	Node val[N];
	/*
	inline void build(int l, int r, int rt) {
		val[rt].init();
		if(l == r) {
			if(l <= n) {
				int x;
				cin >> x;
				if(x) val[rt].add(x);
			}
			return ;
		}
		int mid = l + r >> 1;
		build(l, mid, ls);
		build(mid + 1, r, rs);
		val[rt] = val[ls] + val[rs];
	}
	*/
	inline void init(int n) {
		rep(i, 0, n << 1) val[i].init();
	}
	inline void qry(int L, int R, int l, int r, int rt) {
		if(L <= l && r <= R) {
			ans = ans + val[rt];
			return ;
		}
		int mid = l + r >> 1;
		if(L <= mid) qry(L, R, l, mid, ls);
		if(R > mid) qry(L, R, mid + 1, r, rs);
	}
	inline void upd(int p, int c, int l, int r, int rt) {
		val[rt].add(c);
		if(l == r) return ;
		int mid = l + r >> 1;
		if(p <= mid) upd(p, c, l, mid, ls);
		else upd(p, c, mid + 1, r, rs);
	}
}seg;

inline void solve() {
	cin >> n >> m;
	int sum = n + m;
	for(int i = 1; ; ++i) if(pw(i) >= sum) {
		sum = pw(i);
		break;
	}
	seg.init(sum);
	rep(i, 1, n + 1) {
		int x; cin >> x;
		seg.upd(i, x, 1, sum, 1);
	}
	pans = 0;
	rep(i, 1, m + 1) {
		int o; cin >> o;
		if(o == 0) {
			int l, r; cin >> l >> r;
			l = (l ^ pans) % n + 1, r = (r ^ pans) % n + 1;
			if(l > r) swap(l, r);
			ans.init();
			seg.qry(l, r, 1, sum, 1);
			pans = 0;
			per(k, 0, M) if(ans.a[k]) pans ^= ans.a[k];
			cout << pans << endl;
		} else {
			int x; cin >> x; x ^= pans;
			seg.upd(n + 1, x, 1, sum, 1);
			n++;
		}
	}
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int T; cin >> T;
	while(T--) solve();
	return 0;
}

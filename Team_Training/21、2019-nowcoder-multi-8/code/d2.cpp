#include<bits/stdc++.h>
using namespace std;
#define fi first 
#define se second
#define mp make_pair
#define pb push_back
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define de(x) cout << #x << " = " << x << endl
#define dd(x) cout << #x << " = " << x << " "
#define endl '\n'
#define pw(x) (1ll<<(x))
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()
typedef long long ll;
typedef double db;
typedef vector<int> vi;
typedef pair<int, int> pii;

const int N = 101010;

int n, m, h, q;
int ans[N], res;

struct Q {
	int o, x, y, z;
	void read() {
		o = rand() % 2 + 1;
		x = rand() % n + 1;
		y = rand() % m + 1;
		z = rand() % h + 1;
	//	cin >> o >> x >> y >> z;
	}
	void print() {
		cout << x << " " << y << " " << z << endl;
	}
}qq[N];

void Ma(int &a, int b) {
	if(a < b) a = b;
}

#define ls rt << 1
#define rs ls | 1
struct S1 {
	vi ma;
	void init() {
		ma = vi(h << 2 | 1);
		rep(i, 0, sz(ma)) ma[i] = -1e9;
	}
	void upd(int z, int c, int l = 1, int r = h, int rt = 1) {
		Ma(ma[rt], c);
		if(l == r) return ;
		int mid = l + r >> 1;
		if(z <= mid) upd(z, c, l, mid, ls);
		else upd(z, c, mid + 1, r, rs);
	}
	void qry(int z, int l = 1, int r = h, int rt = 1) {
		if(r <= z) {
			Ma(res, ma[rt]);
			return ;
		}
		int mid = l + r >> 1;
		qry(z, l, mid, ls);
		if(z > mid) qry(z, mid + 1, r, rs);
	}
}s1;
struct S2 {
	vector<S1> ma;
	void init() {
		ma = vector<S1>(m << 2 | 1);
		rep(i, 0, sz(ma)) ma[i].init();
	}
	void upd(int y, int z, int c, int l = 1, int r = m, int rt = 1) {
		ma[rt].upd(z, c);
		if(l == r) return ;
		int mid = l + r >> 1;
		if(y <= mid) upd(y, z, c, l, mid, ls);
		else upd(y, z, c, mid + 1, r, rs);
	}
	void qry(int y, int z, int l = 1, int r = m, int rt = 1) {
		if(r <= y) {
			ma[rt].qry(z);
			return ;
		}
		int mid = l + r >> 1;
		qry(y, z, l, mid, ls);
		if(y > mid) qry(y, z, mid + 1, r, rs);
	}
}s2;
struct S3 {
	vector<S2> ma;
	void init() {
		ma = vector<S2>(n << 2 | 1);
		rep(i, 0, sz(ma)) ma[i].init();
	}
	void upd(int x, int y, int z, int c, int l = 1, int r = n, int rt = 1) {
		ma[rt].upd(y, z, c);
		if(l == r) return ;
		int mid = l + r >> 1;
		if(x <= mid) upd(x, y, z, c, l, mid, ls);
		else upd(x, y, z, c, mid + 1, r, rs);
	}
	void qry(int x, int y, int z, int l = 1, int r = n, int rt = 1) {
		if(r <= x) {
			ma[rt].qry(y, z);
			return ;
		}
		int mid = l + r >> 1;
		qry(x, y, z, l, mid, ls);
		if(x > mid) qry(x, y, z, mid + 1, r, rs);
	}
}s3;

void solve() {
	s3.init();
	rep(i, 1, q + 1) {
		if(qq[i].o == 1) {
			s3.upd(qq[i].x, qq[i].y, qq[i].z, qq[i].x + qq[i].y + qq[i].z);
		} else {
			res = -1e9;
		//	if(ans[i] == 1) continue;
			s3.qry(qq[i].x, qq[i].y, qq[i].z);
			res = qq[i].x + qq[i].y + qq[i].z - res;
			if(ans[i] > res) ans[i] = res;
		}
	}

	//rep(i, 1, q + 1) if(qq[i].o == 2) cout << ans[i] << endl;
	//cout << endl;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	h = 1, m = 100, n = 1000;
	q = 1e5;
//	cin >> n >> m >> h >> q;
	rep(i, 1, q + 1) ans[i] = 1e9;
	rep(i, 1, q + 1) qq[i].read();
	solve(); // 000
	rep(i, 1, q + 1) qq[i].z = h + 1 - qq[i].z;
	solve(); // 001
	rep(i, 1, q + 1) qq[i].y = m + 1 - qq[i].y;
	solve(); // 011
	rep(i, 1, q + 1) qq[i].z = h + 1 - qq[i].z;
	solve(); // 010
	rep(i, 1, q + 1) qq[i].x = n + 1 - qq[i].x;
	solve(); // 110
	rep(i, 1, q + 1) qq[i].z = h + 1 - qq[i].z;
	solve(); // 111
	rep(i, 1, q + 1) qq[i].y = m + 1 - qq[i].y;
	solve(); // 101
	rep(i, 1, q + 1) qq[i].z = h + 1 - qq[i].z;
	solve(); // 100
	rep(i, 1, q + 1) if(qq[i].o == 2) cout << ans[i] << endl;
	return 0;
}

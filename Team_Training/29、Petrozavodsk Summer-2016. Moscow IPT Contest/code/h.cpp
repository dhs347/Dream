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
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()
#define pw(x) (1ll<<(x))
#define ls rt << 1
#define rs ls | 1
typedef long long ll;
typedef double db;
typedef vector<int> vi;
typedef pair<int, int> pii;

const int N = 150000 + 7;

int n, a[N], m = 3e5;
ll res;
vi nd[N << 2], sta[N << 2];

void upd(int L, int R, int h, int l = 1, int r = n, int rt = 1) {
	//if(rt == 1) dd(L), dd(R), de(h);
	if(L <= l && r <= R) return nd[rt].pb(h), void();
	int mid = l + r >> 1;
	if(L <= mid) upd(L, R, h, l, mid, ls);
	if(R > mid) upd(L, R, h, mid + 1, r, rs);
}

struct Seg {
	static const int N = ::N << 3;
	int sum[N];
	int qry(int L, int R, int l = 0, int r = m, int rt = 1) {
		if(L <= l && r <= R) {
			if(sum[rt] == r - l + 1) return -1;
			while(l < r) {
				int mid = l + r >> 1;
				if(sum[ls] != mid - l + 1) {
					r = mid;
					rt = ls;
				} else {
					l = mid + 1;
					rt = rs;
				}
			}
			return l;
		}
		int mid = l + r >> 1;
		if(L <= mid) {
			int t = qry(L, R, l, mid, ls);
			if(~t) return t;
		}
		if(R > mid) {
			int t = qry(L, R, mid + 1, r, rs);
			if(~t) return t;
		}
		return -1;
	}
	void upd(int p, int c, int l = 0, int r = m, int rt = 1) {
		sum[rt] += c;
		if(l == r) return ;
		int mid = l + r >> 1;
		if(p <= mid) upd(p, c, l, mid, ls);
		else upd(p, c, mid + 1, r, rs);
	}
}seg;

void dfs(int l = 1, int r = n, int rt = 1) {
	ll pres = res;
	for(auto h : nd[rt]) {
		int p = seg.qry(h, m);
		res += p - h;
		seg.upd(p, 1);
		sta[rt].pb(p);
	}
	if(l == r) {
		cout << res << endl;
	} else {
		int mid = l + r >> 1;
		dfs(l, mid, ls);
		dfs(mid + 1, r, rs);
	}
	for(auto p : sta[rt]) seg.upd(p, -1);
	res = pres;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n;
	rep(i, 1, n + 1) a[i] = -1;
//	seg.upd(3, 1);
//	de(seg.sum[1]);
//	de(seg.qry(3, 5));
	rep(i, 1, n + 1) {
		string o; int x, y;
		cin >> o >> x;
		if(o[0] == '+') {
			cin >> y;
			a[i] = x;
		} else {
//			de(x);
			upd(x, i - 1, a[x]);
			a[x] = -1;
		}
	}
	rep(i, 1, n + 1) if(~a[i]) upd(i, n, a[i]);
	dfs();
	return 0;
}

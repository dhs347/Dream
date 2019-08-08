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

const int N = 4e5 + 7, inf = 1e9;

int n;
ll x[2][N], a[2], b[2], c[2], m[2];

struct Seg {
	static const int N = ::N * 30;
	int ls[N], rs[N], rt, L;
	ll sum[N], la[N];
	void gao(int &rt, int c, int l, int r) {
		sum[rt] += c * 1ll * (r - l + 1);
		la[rt] += c;
	}
	void down(int rt, int l, int r, int mid) {
		if(!la[rt]) return ;
		gao(ls[rt]
	}
	void upd(int L, int R, int l, int r, int &rt) {
		if(!rt) rt = ++L;
		if(L <= l && r <= R) {
			gao(rt, 1, l, r);
			return ;
		}
		int mid = l + r >> 1;
		down(rt, l, r, mid);
		if(L <= mid) gao(L, R, l, mid, ls[rt]);
		if(R > mid) gao(L, R, mid + 1, r, rs[rt]);
		up(rt);
	}
}seg;

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n;
	rep(o, 0, 2) {
		cin >> x[o][1] >> x[o][2] >> a[o] >> b[o] >> c[o] >> m[o];
		rep(i, 3, n + 1) {
			x[o][i] = (a[o] * x[o][i - 1] + b[o] * x[o][i - 2] + c[o]) % m[o];
		}
	}
	rep(i, 1, n + 1) {
		int l = x[0][i] + 1, r = x[1][i] + 1;
		if(l > r) swap(l, r);
		seg.upd(l, r, 1, inf, seg.rt);
		ll k = seg.sum[rt];
		cout << seg.qry(k - k / 2, 1, inf, seg.rt) << endl;
	}
	return 0;
}

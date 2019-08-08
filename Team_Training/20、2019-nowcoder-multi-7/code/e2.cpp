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

const int N = 4e5 + 7, inf = pw(30);

int n;
ll x[2][N], a[2], b[2], c[2], m[2];

struct Seg {
	static const int N = 6e6;
	int ls[N], rs[N], rt, cntn;
	ll sum[N];
	int la[N]; ll pre;
	void up(int rt, int l, int r) {
		sum[rt] = sum[ls[rt]] + sum[rs[rt]] + la[rt] * 1ll * (r - l + 1);
	}
	void upd(int L, int R, int l, int r, int &rt) {
		if(!rt) rt = ++cntn;
		assert(cntn < N);
		if(L <= l && r <= R) {
			la[rt]++;
			sum[rt] += (r - l + 1);
			return ;
		}
		int mid = l + r >> 1;
		if(L <= mid) upd(L, R, l, mid, ls[rt]);
		if(R > mid) upd(L, R, mid + 1, r, rs[rt]);
		up(rt, l, r);
	}
	ll calc(int rt, int l, int r) {
		return pre * (r - l + 1) + sum[rt];
	}
	int qry(ll p, int l, int r, int rt) {
	//	dd(p), dd(l), dd(r), de(pre);
		if(!rt) {
			ll c = (p + pre - 1) / pre;
			return l + c - 1;
		}
		if(l == r) return l;
		int mid = l + r >> 1;
		pre += la[rt];
		ll t = calc(ls[rt], l, mid);
		if(t >= p) {
			return qry(p, l, mid, ls[rt]);
		} else {
			return qry(p - t, mid + 1, r, rs[rt]);
		}
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
		ll k = seg.sum[seg.rt]; seg.pre = 0;
		cout << seg.qry(k - k / 2, 1, inf, seg.rt) << endl;
	}
	return 0;
}

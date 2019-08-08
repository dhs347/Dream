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

int n, ans;
ll x[2][N], a[2], b[2], c[2], m[2];
vi V;
int F(int x) {
	return lower_bound(all(V), x) - V.begin() + 1;
}
int cc; 
struct Seg {
#define ls rt << 1
#define rs ls | 1
	static const int N = ::N << 3;
	ll la[N], sum[N];
	inline void gao(int rt, int l, int r, ll c) {
		la[rt] += c;
		sum[rt] += c * (V[r] - V[l - 1]);
	}
	inline void down(int rt, int l, int r, int mid) {
		if(!la[rt]) return ;
		gao(ls, l, mid, la[rt]);
		gao(rs, mid + 1, r, la[rt]);
		la[rt] = 0;
	}
	inline void up(int rt) {
		sum[rt] = sum[ls] + sum[rs];
	}
	inline void upd(int L, int R, int l, int r, int rt) {
		if(L <= l && r <= R) {
			gao(rt, l, r, 1);
			return ;
		}
		int mid = l + r >> 1;
		down(rt, l, r, mid);
		if(L <= mid) upd(L, R, l, mid, ls);
		if(R > mid) upd(L, R, mid + 1, r, rs);
		up(rt);
	}
	inline void qry(ll k, int l, int r, int rt) {
		if(l == r) {
			ll c = (k + la[rt] - 1) / la[rt];
			ans = V[l - 1] + c - 1;
			return ;
		}
		int mid = l + r >> 1;
		down(rt, l, r, mid);
		if(sum[ls] >= k) qry(k, l, mid, ls);
		else qry(k - sum[ls], mid + 1, r, rs);
		up(rt);
	}
}seg;

int main() {
	cin >> n;
	rep(o, 0, 2) {
		rep(i, 1, n + 1) {
			x[o][i] = rand() % inf;
		}
	}
	rep(i, 1, n + 1) {
		int l = x[0][i] + 1, r = x[1][i] + 1;
		if(l > r) swap(l, r);
		V.pb(l); V.pb(r + 1);
	}
	V.pb(1); V.pb(1e9 + 1); sort(all(V)); V.erase(unique(all(V)), V.end());
	de(sz(V));
	rep(i, 1, n + 1) {
		if(i % 1000 == 0) de(i);
		int l = x[0][i] + 1, r = x[1][i] + 1;
		if(l > r) swap(l, r);
		int L = F(l), R = F(r + 1) - 1;
		cc = 0;
		seg.upd(L, R, 1, sz(V), 1);
		de(cc);
		ll k = seg.sum[1];
	//	seg.qry(k - k / 2, 1, sz(V), 1);
	}
	return 0;
}

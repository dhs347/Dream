#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define dd(a) cout << #a << " = " << a << " " 
#define de(a) cout << #a << " = " << a << endl
#define sz(a) (int)a.size()
#define all(a) a.begin(), a.end()
#define pw(a) (1ll << (a))
#define endl "\n"
typedef unsigned int ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef double db;

const int N = 50505;

int n, m;
vi V; int F(int x) { return lower_bound(all(V), x) - V.begin() + 1; }
pair<pii, pair<int, ll> > Q[N];

struct Seg2 {
	static const int N = 1e7;
	int cntn, ls[N], rs[N];
	ll la[N], sum[N];
	void upd(int &rt, int L, int R, int l, int r) {
		if(!rt) rt = ++cntn;
		if(L <= l && r <= R) return la[rt]++, void();
		sum[rt] += min(r, R) - max(l, L) + 1;
		int mid = l + r >> 1;
		if(L <= mid) upd(ls[rt], L, R, l, mid);
		if(R > mid) upd(rs[rt], L, R, mid + 1, r);
	}
	void qry(int rt, int L, int R, int l, int r, ll &ans) {
		if(!rt) return ;
		ans += (min(r, R) - max(l, L) + 1) * la[rt];
		if(L <= l && r <= R) return ans += sum[rt], void();
		int mid = l + r >> 1;
		if(L <= mid) qry(ls[rt], L, R, l, mid, ans);
		if(R > mid) qry(rs[rt], L, R, mid + 1, r, ans);
	}
}seg2;

struct Seg1 {
#define ls rt << 1
#define rs ls | 1
	static const int N = ::N << 2;
	int root[N];
	void upd(int p, int L, int R, int l, int r, int rt) {
		seg2.upd(root[rt], L, R, 1, n);
		if(l == r) return ;
		int mid = l + r >> 1;
		if(p <= mid) upd(p, L, R, l, mid, ls);
		else upd(p, L, R, mid + 1, r, rs);
	}
	int qry(ll k, int L, int R, int l, int r, int rt) {
		if(l == r) return l;
		ll cnt = 0; seg2.qry(root[rs], L, R, 1, n, cnt);
		int mid = l + r >> 1;
		if(cnt >= k) return qry(k, L, R, mid + 1, r, rs);
		return qry(k - cnt, L, R, l, mid, ls);
	}
}seg1;

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n >> m;
	rep(i, 1, m + 1) {
		int o, l, r; ll c; cin >> o >> l >> r >> c;
		if(o == 1) V.pb(c);
		Q[i] = mp(mp(o, l), mp(r, c));
	}
	sort(all(V));
	V.erase(unique(all(V)), V.end());
	rep(i, 1, m + 1) {
		int o = Q[i].fi.fi, l = Q[i].fi.se, r = Q[i].se.fi; ll c = Q[i].se.se;
		if(o == 1) {
			seg1.upd(F(c), l, r, 1, n, 1);
		} else {
			int p = seg1.qry(c, l, r, 1, n, 1);
			cout << V[p - 1] << endl;
		}
	}
	return 0;
}

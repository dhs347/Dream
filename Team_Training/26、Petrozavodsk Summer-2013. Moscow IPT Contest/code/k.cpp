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
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()
#define endl '\n'
#define pw(x) (1ll<<(x))
typedef long long ll;
typedef pair<int, int> pii;
typedef double db;
typedef vector<int> vi;

const int N = 101010, P = 1e9 + 7;

int n, m;

int add(int a, int b) {
	if((a += b) >= P) a -= P;
	return a;
}
int mul(int a, int b) {
	return 1ll * a * b % P;
}

struct Seg {
#define ls rt << 1
#define rs ls | 1
	static const int N = ::N << 2;
	int la[2][N], sum[2][N], tot[N];
	void gao(int o, int c, int rt, int l, int r) {
		la[o][rt] = add(la[o][rt], c);
		sum[o][rt] = add(sum[o][rt], mul(r - l + 1, c));
		tot[rt] = add(tot[rt], mul(c, sum[o ^ 1][rt]));
	}
	void down(int rt, int l, int r, int mid) {
		 rep(o, 0, 2) if(la[o][rt]) {
		 	 gao(o, la[o][rt], ls, l, mid);
		 	 gao(o, la[o][rt], rs, mid + 1, r);
		 	 la[o][rt] = 0;
		 }
	}
	void up(int rt) {
		rep(o, 0, 2) sum[o][rt] = add(sum[o][ls], sum[o][rs]);
		tot[rt] = add(tot[ls], tot[rs]);
	}
	void upd(int L, int R, int o, int c, int l = 1, int r = n, int rt = 1) {
		if(L <= l && r <= R) {
			gao(o, c, rt, l, r);
			return ;
		}
		int mid = l + r >> 1;
		down(rt, l, r, mid);
		if(L <= mid) upd(L, R, o, c, l, mid, ls);
		if(R > mid) upd(L, R, o, c, mid + 1, r, rs);
		up(rt);
	}
	int qry(int L, int R, int l = 1, int r = n, int rt = 1) {
		if(L <= l && r <= R) return tot[rt];
		int mid = l + r >> 1, ans = 0;
		down(rt, l, r, mid);
		if(L <= mid) ans = add(ans, qry(L, R, l, mid, ls));
		if(R > mid) ans = add(ans, qry(L, R, mid + 1, r, rs));
		return ans;
	}
}seg;

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n >> m;
	rep(i, 1, m + 1) {
		int l, r, x;
		string s; cin >> s >> l >> r;
		if(s[0] == '?') {
			cout << seg.qry(l, r) << endl;
		} else {
			cin >> x;
			seg.upd(l, r, s[0] == '*', x);
		}
	}
	return 0;
}

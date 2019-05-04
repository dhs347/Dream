#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define sz(a) (int)a.size()
#define all(a) a.begin(), a.end()
#define pw(x) (1ll <<(x))
#define endl "\n"
#define de(a) cout << #a << " = " << a << endl
#define dd(a) cout << #a << " = " << a << " "
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef double db;

const int N = 101010;

int n, m, tot;
int pre[N], sz[N];
ll K, k;
ll C[N];

struct Seg {
#define ls rt << 1
#define rs ls | 1
	static const int N = ::N << 2;
	int tot[N], sz[N]; ll sum[N];
	void build(int l, int r, int rt) {
		tot[rt] = sz[rt] = sum[rt] = 0;
		if(l == r) return ;
		int mid = l + r >> 1;
		build(l, mid, ls);
		build(mid + 1, r, rs);
	}
	void upd(int p, int c, int l, int r, int rt) {
		tot[rt] += c * p;
		sum[rt] += c * C[p];
		sz[rt] += c;
		if(l == r) return ;
		int mid = l + r >> 1;
		if(p <= mid) upd(p, c, l, mid, ls);
		else upd(p, c, mid + 1, r, rs);
	}
	void qry(int l, int r, int rt, int &tt, ll &ts, int &tsz) {
		if(l == r) {
			int st = 0, ed = sz[rt], ans = -1;
			while(st <= ed) {
				int mid = st + ed >> 1;
				if(C[tt + mid * l] - (ts + mid * C[l]) + K >= k) ans = mid, ed = mid - 1;
				else st = mid + 1;
			}
			tt += ans * l, ts += ans * C[l], tsz += ans;
			return ;
		}
		int mid = l + r >> 1;
		if(C[tt + tot[rs]] - (ts + sum[rs]) + K < k) tt += tot[rs], ts += sum[rs], tsz += sz[rs], qry(l, mid, ls, tt, ts, tsz);
		else qry(mid + 1, r, rs, tt, ts, tsz);
	}
}seg;

void init() {
	seg.build(1, n, 1);
	rep(i, 1, n + 1) pre[i] = i, sz[i] = 1, seg.upd(1, 1, 1, n, 1);;
	tot = n; K = 0;
}
int find(int x) {
	return x == pre[x] ? x : pre[x] = find(pre[x]);
}
void join(int a, int b) {
	a = find(a), b = find(b);
	if(a == b) {
		K--;
		return ;
	}
	pre[a] = b;
	seg.upd(sz[a], -1, 1, n, 1);
	seg.upd(sz[b], -1, 1, n, 1);
	K += sz[a] * 1ll * sz[b] - 1;
	--tot;
	sz[b] += sz[a];
	seg.upd(sz[b], 1, 1, n, 1);
}
void solve() {
	cin >> n >> m;
	init();
	while(m--) {
		int o;
		cin >> o;
		if(o == 1) {
			int a, b;
			cin >> a >> b;
			join(a, b);
		} else {
			cin >> k;
			int ans1 = max(1ll, tot - k);
			int tt = 0, tsz = 0; ll ts = 0;
			if(K >= k) {
				cout << ans1 << " " << tot << endl;
				continue;
			}
			seg.qry(1, n, 1, tt, ts, tsz);
			int ans2 = tot - tsz + 1;
			cout << ans1 << " " << ans2 << endl;
		}
	}
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	rep(i, 1, N) C[i] = i * 1ll * (i - 1) / 2;
	int T;
	cin >> T;
	while(T--) {
		solve();
	}
	return 0;
}

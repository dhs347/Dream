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
#define all(a) a.begin(), a.end()
#define sz(a) (int)a.size()
#define dd(x) cout << #x << " = " << x << " "
#define de(x) cout << #x << " = " << x << endl
#define ff fflush(stdout);
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int N = 2020;

int tot;
int n, q, k, id[N], B;
ll a[N], pre[N][N], suf[N][N], b[N], ind[N];
map<pair<ll, ll>, ll> M;

ll add(ll a, ll b) {
	if(a > b) swap(a, b);
	if(M.count(mp(a, b))) return M[mp(a, b)];
	assert(tot);
	--tot;
	printf("? %lld %lld\n", a, b);
	ff;
	ll c; scanf("%lld", &c);
	M[mp(a, b)] = c;
	return c;
}

struct Seg {
#define ls rt << 1
#define rs ls | 1
	static const int N = ::N << 2;
	ll sum[N];
	void up(int rt) {
		sum[rt] = add(sum[ls], sum[rs]);
	}
	void build(int l, int r, int rt) {
		if(l == r) {
			sum[rt] = b[l];
			return ;
		}
		int mid = l + r >> 1;
		build(l, mid, ls);
		build(mid + 1, r, rs);
		up(rt);
	}
	ll qry(int L, int R, int l, int r, int rt) {
		if(L <= l && r <= R) return sum[rt];
		int mid = l + r >> 1;
		ll ans; bool F = 0;
		if(L <= mid) ans = qry(L, R, l, mid, ls), F = 1;
		if(R > mid) {
			ll t = qry(L, R, mid + 1, r, rs);
			if(F) ans = add(ans, t);
			else ans = t;
		}
		return ans;
	}
}seg;

void gao(int c, int l, int r) {
	pre[c][l] = b[l];
	rep(i, l + 1, r + 1) pre[c][i] = add(pre[c][i - 1], b[i]);
	suf[c][r] = b[r];
	per(i, l, r) suf[c][i] = add(suf[c][i + 1], b[i]);
}

ll solve(int cnt, int l, int r, int L, int R) {
	if(l == L) return pre[cnt][R];
	if(r == R) return suf[cnt][L];
	return seg.qry(L, R, 1, n, 1);
}

ll solve(int l, int r) {
	int cnt = 0;
	ll ans; bool F = 0;
	for(int i = 1; i <= n; i += B) {
		int L = i, R = min(n, i + B - 1);
	//	dd(L), dd(R), dd(l), de(r);
		++cnt;
		if(max(L, l) <= min(R, r)) {
			if(F) {
				ans = add(ans, solve(cnt, L, R, max(L, l), min(R, r)));
			} else {
				ans = solve(cnt, L, R, max(L, l), min(R, r));
				F = 1;
			}
		}
	}
	return ans;
}

void solve() {
	printf("next\n");
	ff;
	rep(i, 1, k + 1) scanf("%d", ind + i), ind[i] = id[ind[i]];
	bool F = 0; ll ans;
	sort(ind + 1, ind + 1 + k);
	ind[0] = 0, ind[k + 1] = n + 1;
	rep(i, 0, k + 1) {
		int l = ind[i] + 1, r = ind[i + 1] - 1;
		if(l <= r) {
			if(F) {
				ans = add(ans, solve(l, r));
			} else {
				ans = solve(l, r);
				F = 1;
			}
		}
	}
	printf("! %lld\n", ans);
	ff;
}

int main() {
	scanf("%d%d%d", &n, &q, &k);
	tot = 4 * (n + q + q * k);
	rep(i, 1, n + 1) scanf("%lld", a + i), id[i] = i;
	srand(time(0));
	random_shuffle(id + 1, id + 1 + n);
	rep(i, 1, n + 1) b[id[i]] = a[i];
	seg.build(1, n, 1);
	B = max(1, (int)(n * 1. / (k + 1) / 3));
	assert(B);
	int cnt = 0;
	for(int i = 1; i <= n; i += B) {
		int l = i, r = min(n, i + B - 1);
		gao(++cnt, l, r);
	}
	rep(i, 1, q + 1) solve();
	return 0;
}

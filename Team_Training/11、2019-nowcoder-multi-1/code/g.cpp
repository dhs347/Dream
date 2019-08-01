#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define de(c) cout << #c << " = " << c << endl
#define dd(c) cout << #c << " = " << c << " "
#define all(c) c.begin(), c.end()
#define sz(x) (int)x.size()
#define endl '\n'
#define pw(x) (1ll << (x))
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef double db;

const int N = 5e4 + 5, S = 223, seed = 233;

int n, a[N], cnt, ns, ne[N], pre[N], cur[N], mo[N], di[N];
ull B[N];

struct Block {
	ull pre[S + 5]; int val[S + 5];
	void init() {
		fill_n(pre, S + 5, 0);
		fill_n(val, S + 5, 0);
	}
	void ins(int p, int c) {
		val[++p] = c;
		rep(i, p, S + 1) pre[i] = pre[i - 1] * B[1] + val[i];
	}
}blo[N << 1];

struct Suf {
	ull pre[N / S + 5]; int id[N / S + 5];
	void init() { rep(i, 1, ns + 1) pre[i] = 0, blo[cnt].init(), id[i] = cnt++; }
	void ins(int p, int c) {
		int b = p / S + 1;
		if(c) {
			blo[cnt] = blo[id[b]]; id[b] = cnt;
			blo[cnt++].ins(p % S, c);
			rep(i, b, ns + 1) pre[i] = pre[i - 1] * B[S] + blo[id[i]].pre[S];
		}
	}
	ull Pre(int p) {
		int b = di[p] + 1; ull ans = pre[b - 1];
		return ans * B[mo[p] + 1] + blo[id[b]].pre[mo[p] + 1];
	}
	ull get(int l, int r) {
		if(l == 1) return Pre(r);
		return Pre(r) - Pre(l - 1) * B[r - l + 1];
	}
	int getV(int p) {
		if(p > n) return -1;
		int b = p / S + 1;
		return blo[id[b]].val[p % S + 1];
	}
}suf[N];

int lcp(int i, int j) {
	if(i == 0 || j == 0) return 0;
	int l = 1, r = n - max(i, j) + 1, ans = 0;
	while(l <= r) {
		int mid = l + r >> 1;
		if(suf[i].get(i, i + mid - 1) == suf[j].get(j, j + mid - 1)) {
			ans = mid;
			l = mid + 1;
		} else {
			r = mid - 1;
		}
	}
	//  rep(k, 1, ans + 1) assert(suf[i].get(i, i + k - 1) == suf[j].get(i, j + k - 1));
	return ans;
}

bool cmp(int i, int j) {
	int p = lcp(i, j);
	int x = suf[i].getV(p + i), y = suf[j].getV(p + j);
	//  assert(x != y);
	return x < y;
}

void solve() {
	fill_n(pre + 1, n, 0);
	per(i, 1, n + 1) ne[i] = pre[a[i]], pre[a[i]] = i;
	cnt = 0; ns = n / S + 1; suf[n + 1].init();
	per(i, 1, n + 1) {
		suf[i] = suf[i + 1];
		suf[i].ins(i, 0);
		if(ne[i]) suf[i].ins(ne[i], ne[i] - i);
	}
	rep(i, 1, n + 1) cur[i] = i;
	sort(cur + 1, cur + 1 + n, cmp);
	ll ans = 0;
	rep(i, 1, n + 1) {
		int l = lcp(cur[i - 1], cur[i]);
		ans += n - cur[i] + 1 - l;
		//cout << cur[i] << endl;
	}
	cout << ans << endl;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	B[0] = 1; rep(i, 1, N) B[i] = B[i - 1] * seed;
	rep(i, 0, N) di[i] = i / S, mo[i] = i % S;
	while(cin >> n) {
		rep(i, 1, n + 1) cin >> a[i];
		solve();
	}
	return 0;
}

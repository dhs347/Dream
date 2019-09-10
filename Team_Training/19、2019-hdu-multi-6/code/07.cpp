#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); i++)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define de(x) cout << #x << " = " << x << endl
#define dd(x) cout << #x << " = " << x << " " 
#define endl '\n'
#define pw(x) (1ll<<(x))
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int N = 101010, M = 2e6 + 2;

int n, k;
int hx[M], hy[M], hz[M];
vi res;

struct O {
	int x, y, z, r;
	void read() {
		cin >> x >> y >> z >> r;
		x <<= 1, y <<= 1, z <<= 1, r <<= 1;
	}
	bool operator < (const O &c) const {
		return r > c.r;
	}
}o[N];

struct H {
	static const int N = pw(19) - 1;
	int L, hd[N], ne[N]; ll val[N];
	int cntd, del[N];
	void _init() { fill_n(hd, N, -1); }
	void init() {
		rep(i, 1, cntd + 1) hd[del[i]] = -1;
		L = cntd = 0;
	}
	int ins(int x, int y, int z) {
		int u = (hx[x] ^ hy[y] ^ hz[z]) & N;
		ll v = (x * 1ll << 42) | (y * 1ll << 21) | z;
		int p = 0;
		for(int i = hd[u]; ~i; i = ne[i]) if(val[i] == v) return i;
		if(hd[u] == -1) del[++cntd] = u;
		val[L] = v, ne[L] = hd[u], hd[u] = L;
		return L++;
	}
	int find(int x, int y, int z) {
		int u = (hx[x] ^ hy[y] ^ hz[z]) & N;
		ll v = (x * 1ll << 42) | (y * 1ll << 21) | z;
		for(int i = hd[u]; ~i; i = ne[i]) if(val[i] == v) return i;
		return -1;
	}
}has;

int l[N], cnt[N], cur[N], st[N], ed[N];
void rebuild(int st, int now) {
	has.init();
	rep(i, st, n + 1) {
		l[i] = has.ins(o[i].x / now, o[i].y / now, o[i].z / now);
	}
	rep(i, 0, has.L) cnt[i] = 0;
	rep(i, st, n + 1) ++cnt[l[i]];
	cnt[0] += st - 1; rep(i, 1, has.L) cnt[i] += cnt[i - 1];
	rep(i, st, n + 1) cur[cnt[l[i]]--] = i;
	rep(i, st, n + 1) ::ed[l[cur[i]]] = i;
	per(i, st, n + 1) ::st[l[cur[i]]] = i;
}
ll sqr(int x) {
	return 1ll * x * x;
}
int dis(int i, int j) {
	ll t = sqr(o[i].x - o[j].x >> 1) + sqr(o[i].y - o[j].y >> 1) + sqr(o[i].z - o[j].z >> 1);
	int l = 0, r = 1e6 + 5e5, ans = 0;
	while(l <= r) {
		int mid = l + r >> 1;
		if(mid * 1ll * mid >= t) {
			ans = mid; 
			r = mid - 1;
		} else {
			l = mid + 1;
		}
	}
	return max(0, ans - (o[i].r + o[j].r >> 1));
}
int calc(int mid, bool flag = 0) {
	int pre = 1e9, ret = 0;
	rep(i, 1, n + 1) {
		int now = o[i].r + mid << 1;
		if(now * 2 <= pre && i < n) rebuild(i + 1, pre = now);
		int A = o[i].x / pre, B = o[i].y / pre, C = o[i].z / pre;
		rep(x, max(0, A - 1), A + 2) rep(y, max(0, B - 1), B + 2) rep(z, max(0, C - 1), C + 2) {
			int t = has.find(x, y, z);
			if(~t) {
				rep(p, st[t], ed[t] + 1) {
					int j = cur[p];
					if(j <= i) break;
					if(sqr(o[i].x - o[j].x) + sqr(o[i].y - o[j].y) + sqr(o[i].z - o[j].z) <= sqr(o[i].r + o[j].r + mid * 2)) {
						++ret;
						if(ret >= k) return ret;
						if(flag) res.pb(dis(i, j));
					}
				}
			}
		}
	}
	return ret;
}

void solve() {
	cin >> n >> k;
	rep(i, 1, n + 1) o[i].read();
	sort(o + 1, o + 1 + n);
	int l = 0, r = 1e6 + 5e5, ans = -1;
	while(l <= r) {
		int mid = l + r >> 1;
		int t = calc(mid);
		if(t >= k) {
			ans = mid;
			r = mid - 1;
		} else {
			l = mid + 1;
		}
	}
	res.clear();
	calc(ans - 1, 1);
	while(sz(res) < k) res.pb(ans);
	sort(all(res));
	for(auto u : res) cout << u << endl;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	srand(time(0));
	rep(i, 0, M) {
		hx[i] = (1ll * rand() << 15 ^ rand()) & (~0U>>1);
		hy[i] = (1ll * rand() << 15 ^ rand()) & (~0U>>1);
		hz[i] = (1ll * rand() << 15 ^ rand()) & (~0U>>1);
	}
	has._init();
	int T; cin >> T;
	while(T--) solve();
	return 0;
}

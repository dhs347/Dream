#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define dd(x) cout << #x << " = " << x << " "
#define de(x) cout << #x << " = " << x << endl
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()
#define endl '\n'
#define pw(x) (1ll<<(x))
typedef long long ll;
typedef pair<int, int> pii;
typedef double db;
typedef vector<int> vi;

const int N = 250000 + 5;

int n, a[N], b[N], cur[N], bi[N], ai[N], rk[N];

bool cmp(int i, int j) {
	return a[i] * (a[j] + b[j]) < a[j] * (a[i] + b[i]);
}

struct Seg {
#define ls rt << 1
#define rs ls | 1
	static const int N = ::N << 2;
	int sa[N], sb[N];
	void build(int n) {
		fill_n(sa, n << 2 | 1, 0);
		fill_n(sb, n << 2 | 1, 0);
	}
	void upd(int p, int a, int b, int l, int r, int rt) {
		sa[rt] += a, sb[rt] += b;
		if(l == r) return ;
		int mid = l + r >> 1;
		if(p <= mid) upd(p, a, b, l, mid, ls);
		else upd(p, a, b, mid + 1, r, rs);
	}
	void solve() {
		int tot = sb[1], l = 1, r = n, rt = 1, p = 0, pa = 0, pb = 0;
		while(l <= r) { 
			if(l < r) {
				int mid = l + r >> 1;
				//dd(l), dd(r), dd(mid), dd(pa + sa[ls]), de(tot - (pb + sb[ls]));
				if(pa + sa[ls] - (tot - (pb + sb[ls])) <= 0) {
					p = mid;
					pa += sa[ls], pb += sb[ls];
					l = mid + 1; rt = rs;
				} else {
					r = mid; rt = ls;
				}
			} else {
				if(pa + sa[rt] - (tot - (pb + sb[rt])) <= 0) p = l;
				break;
			}
		}
		++p; 
		int x = pa, y = tot - pb - bi[p];
		ll fz = (y - x + bi[p]) * 1ll * ai[p], fm = ai[p] + bi[p];
		ll g = __gcd(fz, fm);
		fz /= g, fm /= g;
		fz += fm * x;
		cout << fz << "/" << fm << endl;
	}
}seg;

void solve() {
	cin >> n;
	rep(i, 1, n + 1) cin >> a[i] >> b[i];
	rep(i, 1, n + 1) cur[i] = i;
	sort(cur + 1, cur + 1 + n, cmp);
	rep(i, 1, n + 1) rk[cur[i]] = i;
	rep(i, 1, n + 1) {
		ai[rk[i]] = a[i];
		bi[rk[i]] = b[i];
	}
	seg.build(n);
	rep(i, 1, n + 1) {
		int u = rk[i];
		seg.upd(u, a[i], b[i], 1, n, 1);
		seg.solve();
	}
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int T; cin >> T;
	while(T--) solve();
	return 0;
}

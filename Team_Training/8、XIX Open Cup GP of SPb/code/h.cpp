#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) -1; i >= (a); --i)
#define endl "\n"
#define pw(a) (1ll << (a))
#define all(a) a.begin(), a.end()
#define sz(a) (int)a.size()
#define de(x) cout << #x << " = " << x << endl
#define dd(x) cout << #x << " = " << x << " "
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int P = 1e9 + 7;

int n, k, C;
int a[18][20], b[1 << 18][20], ans[20], cnt[1 << 18];
int sum[1 << 18];

int add(int a, int b) {
	if((a += b) >= P) a -= P;
	return a;
}
int sub(int a, int b) {
	if((a -= b) < 0) a += P;
	return a;
}
int mul(int a, int b) {
	return a * 1ll * b % P;
}

bool solve() {
	rep(j, k, k << 1) ans[j] = C;
	rep(i, 0, k) {
		rep(j, 0, 1 << n) {
			sum[j] = 1;
			rep(t, 0, k) if(t != i) {
				int L = max(b[j][t], ans[t]);
				int R = min(b[j][t + k], ans[t + k]);
				sum[j] = mul(sum[j], L > R ? 0 : R - L + 1);
			}
		}
		int l = ans[i], r = ans[i + k], res = -1;
		int tt = 1;
		rep(t, 0, k) if(t != i) tt = mul(tt, ans[t + k] - ans[t] + 1);
		while(l <= r) {
			int mid = l + r >> 1;
			int rr = 0;
			rep(j, 1, 1 << n) {
				int L = max(l, b[j][i]), R = min(mid, b[j][i + k]);
				int t = mul(sum[j], (L > R ? 0 : R - L + 1));
				if(cnt[j] & 1) rr = add(rr, t);
				else rr = sub(rr, t);
			}
			int tot = mul(tt, mid - l + 1);
			if(tot != rr) {
				res = mid;
				r = mid - 1;
			} else {
				l = mid + 1;
			}
		}
		if(res == -1) {
			return 0;
		}
		ans[i] = ans[i + k] = res;
	}
	return 1;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n >> k >> C; --C;
	rep(i, 0, n) {
		rep(j, 0, k << 1) cin >> a[i][j];
		rep(j, k, k << 1) --a[i][j];
	}
	rep(i, 0, 1 << n) {
		rep(j, k, k << 1) b[i][j] = C;
		rep(j, 0, n) if(i >> j & 1) {
			rep(t, 0, k) b[i][t] = max(b[i][t], a[j][t]);
			rep(t, k, k << 1) b[i][t] = min(b[i][t], a[j][t]);
		}
	}
	rep(i, 0, 1 << n) {
		int x = i;
		while(x) {
			if(x & 1) ++cnt[i];
			x >>= 1;
		}
	}
	if(solve()) {
		cout << "YES" << endl;
		rep(i, 0, k) cout << ans[i] << " \n"[i == k - 1];
	} else {
		cout << "NO" << endl;
	}
	return 0;
}

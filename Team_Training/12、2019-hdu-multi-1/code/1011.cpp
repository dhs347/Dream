#include<bits/stdc++.h>
using namespace std;
#define fi first 
#define se second
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define mp make_pair
#define pb push_back
#define de(x) cout << #x << " = " << x << endl
#define dd(x) cout << #x << " = " << x << " "
#define endl '\n'
#define all(a) a.begin(), a.end()
#define sz(a) (int)a.size()
#define pw(x) (1ll << (x))
typedef long long ll;
typedef pair<int, int> pii;
typedef double db;
typedef vector<int> vi;

const int N = 1e7 + 7;
const int P = 998244353;
int M, f[N], phi[N], p[N], ans, l, r, m, T;
__int128 mid, n;

string s;
void prime(int n) {
	phi[1] = 1;
	rep(i, 2, n+1) {
		if (!f[i]) {
			p[++M] = i;
			f[i] = i;
			phi[i] = i-1;
		}
		for(int j = 1, k; j <= M && p[j] <= f[i] && i * p[j] <= n; j ++) {
			f[k = i * p[j]] = p[j];
			if (p[j] < f[i]) {
				phi[k] = phi[i] * phi[p[j]];
			}else {
				phi[k] = phi[i] * p[j];
			}
		}
	}
}

int get(__int128 n) {
		int m = 0;
		l = 0; r = 1e9;
		while (l <= r) {
			mid = l + r >> 1;
			if (mid * mid * mid <= n) m = mid, l = mid + 1;
			else r = mid - 1;
		}
		return m;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	prime(1e7 + 5);
	cin >> T;
	rep(cas, 0, T) {
		cin >> s;n = 0; 
		rep(i, 0, sz(s)) n = n * 10 + s[i] - '0';
		ans = 0;
		m = get(n);
		rep(d, 1, m+1) {
			ll tmp = 0, nn, w;
			nn = m / d * d;
			if (nn < m) {
				nn = m / d; 
				tmp += nn + nn * (nn + 1) / 2 * 3 % P + nn * (nn + 1) / 2 % P * (2 * nn + 1) % P * d % P;
				tmp %= P;
			}else {
				nn = m / d - 1; 
				tmp += nn + nn * (nn + 1) / 2 * 3 % P + nn * (nn + 1) / 2 % P * (2 * nn + 1) % P * d % P;
				tmp %= P;
				w = m / d * d;
				tmp += n / d % P;
				w = w / d * w % P * w %P - 1;
				tmp -= w;
				tmp = (tmp % P + P) % P;
			}
			ans = (ans + tmp * phi[d] % P) % P;
		}
		cout << ans << endl;
	}

	return 0;
}

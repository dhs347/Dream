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

const int N = 5e5 + 7;
int n, k, x, a[N], b[N], c[N], cc[N], m, ans1, ans2;
unordered_map<int, int> M;

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	while (cin >> n >> k) {
		M.clear(); ll s = 0;
		rep(i, 1, n+1) cin >> a[i], s += a[i];
		sort(a+1, a+n+1);
		rep(i, 1, n+1) b[i] = a[i], M[a[i]]++;
		m = unique(b+1, b+n+1) - (b + 1);
		if (m == 1) {
			cout << 0 << endl;
			continue;
		}
		rep(i, 1, m+1) c[i] = M[b[i]];
		rep(i, 1, m+1) cc[i] = c[i];
		int kk = k;
		ans1 = b[1];
		rep(i, 1, m) {
			ll k1 = 1ll * (b[i+1] - b[i]) * c[i];
			if (k1 <= k) {
				k -= k1;
				c[i+1] += c[i];
				ans1 = b[i+1];
			}else {
				ans1 = b[i] + k / c[i];
				break;
			}
		}
		k = kk; 
		ans2 = b[m];
		rep(i, 1, m+1) c[i] = cc[i];
		per(i, 2, m+1) {
			ll k1 = 1ll * (b[i] - b[i-1]) * c[i];
			if (k1 <= k) {
				k -= k1;
				c[i-1] += c[i];
				ans2 = b[i-1];
			}else {
				ans2 = b[i] - k / c[i];
				break;
			}	
		}
		if (ans2 - ans1 <= 0) cout << (s % n > 0) << endl;
		else cout << ans2 - ans1 << endl;
	}
	return 0;
}

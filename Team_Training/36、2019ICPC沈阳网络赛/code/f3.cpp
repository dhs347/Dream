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

const int N = 505050;

int n, k, a[N];

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	while(cin >> n >> k) {
		ll sum = 0;
		rep(i, 1, n + 1) cin >> a[i], sum += a[i];
		if(k >= sum) {
			int ans = (sum % n > 0);
			cout << ans << endl;
		} else {
			int sk = k, p = n + 1, ap;
			sort(a + 1, a + 1 + n);
			per(i, 1, n + 1) {
				ll t = (n - i + 1) * 1ll * (a[i] - a[i - 1]);
				if(k >= t) {
					k -= t;
					p = i, ap = a[i - 1];
				} else {
					ll c = k / (n - i + 1);
					a[i] -= c;
					rep(j, i + 1, n + 1) a[j] = a[i];
					ll cnt = k % (n - i + 1);
					rep(j, i, i + cnt) a[j]--;
					p = n + 1;
					break;
				}
			}
			rep(i, p, n + 1) a[i] = ap;
			sort(a + 1, a + 1 + n);
			k = sk; p = 0;
			rep(i, 1, n) {
				ll t = i * 1ll * (a[i + 1] - a[i]);
				if(k >= t) {
					k -= t;
					p = i, ap = a[i + 1];
				} else {
					ll c = k / i;
					a[i] += c;
					rep(j, 1, i) a[j] = a[i];
					ll cnt = k % i;
					rep(j, 1, cnt + 1) ++a[j];
					k = p = 0;
					break;
				}
			}
			rep(i, 1, p + 1) a[i] = ap;
			if(k % n) {
				cout << 0 << endl;
			} else {
				sort(a + 1, a + 1 + n);
				cout << a[n] - a[1] << endl;
			}
		}
	}
	return 0;
}

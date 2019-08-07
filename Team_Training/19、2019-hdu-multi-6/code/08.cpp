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

ll k, n, ans;
int cnt, m, T, f[30000], p[2000], cntp;

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	/*rep(i, 2, 2000+1) {
		if (!f[i]) p[++cntp] = i;
		for (int j = i + i; j <= 2000; j += i) f[j] = 1;
	}
	de(p[100]);
	*/
	cin >> T;
	rep(cas, 0, T) {
		cin >> k >> m;
		ans = -1;
		rep(i, 1, 700) {
			n = k ^ i;
			cnt = 0;
			if (__gcd(i*1ll, n) != 1) continue;
			rep(j, 1, i+1) if (__gcd(n, 1ll * j) == 1) {
				cnt++;
				if (cnt > m) break;
			}
			if (cnt == m) {
				if (ans == -1) ans = n;else	ans = min(ans, n);
			}
		}
		cout << ans << endl;
	}
	return 0;
}

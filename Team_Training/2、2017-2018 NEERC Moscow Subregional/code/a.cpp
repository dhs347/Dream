#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define mp make_pair
#define pb push_back
#define sz(a) (int)a.size()
#define de(a) cout << #a << " = " << a << endl
#define dd(a) cout << #a << " = " << a << " "
#define all(a) a.begin(), a.end()
#define pw(a) (1ll << (a))
#define endl "\n"
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

ll n, now;
int tim, ans, k;

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n >> k;
	ans = pw(30);
	rep(i, 1, k+1) {
		now = i; tim = 1;
		if (now >= n) {
			ans = min(ans, tim);
			continue;
		}
		now = now + min(now, (n - now) / 2);
		while (1) {
			tim++;
			if (now == n - 1 && k - i == 0) break;
			if (now + k - i >= n) {
				ans = min(ans, tim);
				break;
			}else now = now + min(now, (n - now) / 2);
		}
	}
	cout << ans << endl;
	return 0;
}

#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define dd(a) cout << #a << " = " << a << " " 
#define de(a) cout << #a << " = " << a << endl
#define sz(a) (int)a.size()
#define all(a) a.begin(), a.end()
#define pw(a) (1ll << (a))
#define endl "\n"
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef double db;

ll ans, a, b, c, d, l1, l2, r1, r2, r, l;

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> a >> b >> c >> d;
	rep(i, 1, 1000)
		rep(j, 1, 1000) if (__gcd(i, j) == 1){
			if (i + j >= 1000) break;
			l1 = a / i + (a % i != 0);
			r1 = b / i;

			l2 = c / j + (c % j != 0);
			r2 = d / j;
			l = max(l1, l2);
			r = min(r1, r2);
			if (l <= r) ans += r - l + 1;
		}
	cout << ans << endl;
	return 0;
}

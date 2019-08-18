#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define de(x) cout << #x << " = " << x << endl
#define dd(x) cout << #x << " = " << x << " "
#define endl '\n'
#define pw(x) (1ll<<(x))
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()
typedef long long ll;
typedef pair<int, int> pii;
typedef double db;
typedef vector<int> vi;

int T;

ll y, ans, sum, a, b, c, x, ok;

void exgcd(int a, int b, ll &xx, ll &yy) {
	if (b == 0) {
		xx = 1; yy = 0;
		return;
	}
	exgcd(b, a % b, yy, xx);
	yy -= a / b * xx;
}

//unordered_set<int> M;
int main() {
	freopen("end.in", "r", stdin);
	freopen("end.out", "w", stdout);
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> T;
	//T = 1000;
	rep(cas, 0, T) {
		cin >> a >> b >> c;
		//a = rand() % 20 + 1;
		//b = rand() % 20 + 1;
		//c = rand() % 20 + 1;
		if (a < b) swap(a, b);
		if (c > a) {
			cout << -1 << endl;
			continue;
		}
		if (c == a || c == b) {
			cout << 1 << endl;
			continue;
		}
		ll xx, yy;
		int g = __gcd(a, b);
		if (c % g != 0) {
			cout << -1 << endl;
			continue;
		}
		c /= g; a /= g; b /= g;
		exgcd(a, b, xx, yy);
		xx = xx * c ;
		yy = yy * c;
		ll d = xx / b;
		xx -= b * d;
		yy += a * d;
		if (xx <= 0) {
			xx += b;
			yy -= a;
		}
		//dd(xx), de(yy);
		ans = pw(60);
		ans = min(ans, xx * 2 + abs(yy) * 2 - 2 * (xx > 0));
		//de(ans);
		xx -= b;
		yy += a;
		//dd(xx), de(yy);
		sum = abs(xx) * 2 + yy * 2 - 2 * (c <= b);
		//de(sum);
		ans = min(ans, sum);
		//cout << ans << endl;
		//de(ans);
		cout << ans << endl;
		continue;
		ll ans2 = ans;
		//de(ans2);
		ans = pw(60);
		sum = 0; x = 0; ok = 0;
		while (1) {
			sum += 1;
			y = (x + a) % b;
			if (c % b == y) {
				sum += 2 * ((x + a - c) / b) - 1;
				ok = 1;
				break;
			} 
			sum += 2 * ((x + a) / b) + 1;
			x = y;
			//assert(!M.count(x));
			//M.insert(x);
			//de(x);
			if (x == 0) break;
		}
		if (ok) ans = min(ans, sum);
	//	de(sum);
		sum = 0; x = 0; ok = 0;
		while (1) {
			if (c % b == x) {
				sum += (c - x) / b * 2;
				ok = 1;
				break;
			}
			int d = a / b;
			if (x + d * b < a) d++;
			//de(d);
			y = (x + d * b) % a;
			//de(y);
			if (y == c) {
				sum += 2 * d;
				ok = 1;
				break;
			}
			sum += 2 * d + 2;
			x = y;
			if (x == 0) break;
		}
		if (ok) ans = min(ans, sum);
		if (ans < pw(60)) cout << ans << endl;
		else cout << -1 << endl;
		if (ans2 != ans) {
			//dd(a), dd(b), de(c);
			assert(ans2 == ans);
			return 0;
		}
	} 
	return 0;
}

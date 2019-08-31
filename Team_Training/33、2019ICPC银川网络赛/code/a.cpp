
#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define de(c) cout << #c << " = " << c << endl
#define dd(c) cout << #c << " = " << c << " "
#define endl '\n'
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()
#define pw(x) (1ll<<(x))
typedef long long ll;
typedef pair<int, int> pii;
typedef double db;
typedef vector<int> vi;
typedef unsigned int uint;

int n, p, q, m;

uint sa, sb, sc;

uint rng61() {
	sa ^= sa << 16;
	sa ^= sa >> 5;
	sa ^= sa << 1;
	uint t = sa; sa = sb;
	sb = sc;
	sc ^= t ^ sa;
	return sc;
}

const int N = 5e6 + 100;
ll ans, a[N];
int T, cnt;

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> T;
	rep(cas, 1, T+1) {
		cin >> n >> p >> q >> m >> sa >> sb >> sc;
		cnt = 0; ans = 0;
		rep(i, 1, n+1) {
			if (rng61() % (p + q) < p) {
				a[cnt+1] = max((uint)a[cnt], rng61() % m + 1);
				cnt++;
				ans ^= 1ll * i * a[cnt];
			}else {
				if (cnt > 0) cnt--;
				ans ^= 1ll * i * a[cnt];
			}
		}
		cout << "Case #" << cas << ": " << ans << endl;
	}
	return 0;
}

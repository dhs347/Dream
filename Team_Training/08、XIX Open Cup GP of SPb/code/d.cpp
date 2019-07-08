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
typedef pair<ll, ll> pii;
typedef double db;
typedef vector<int> vi;

ll a, b, c, d, xx, yy;
int dx[] = {-1, 1, 0, 0, 0};
int dy[] = {0, 0, 1, -1, 0};
pii s, t;

pii get(ll x, ll y) {
	rep(i, 0, 5) {
		xx = x + dx[i];
		yy = y + dy[i];
		if ((xx * 2 + yy) % 5 == 0 && (xx - 2 * yy) % 5 == 0) {
			return mp((xx * 2 + yy) / 5, (xx - 2 * yy) / 5);
		}
	}
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> a >> b >> c >> d;
	s = get(a, b);
	t = get(c, d);
	cout << abs(s.fi - t.fi) + abs(s.se - t.se) << endl;
	return 0;
}

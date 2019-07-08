#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define endl "\n"
#define pw(x) (1ll << (x))
#define all(a) a.begin(), a.end()
#define sz(a) (int)a.size()
#define dd(x) cout << #x << " = " << x << " "
#define de(x) cout << #x << " = " << x << endl
typedef long long ll;
typedef double db;
typedef pair<ll, ll> pii;
typedef vector<int> vi;

ll a, b, c, d, x, y, w[2], v[2], num, ans;

int dx[] = {0, 1, 0, -1};
int dy[] = {1, 0, -1, 0};

pair<pii, int> p1, p2; 
pii inf = mp(-pw(30), -pw(30)), t;

pii check(ll a, ll b) {
	ll i = a * 2 + b;
	ll j = a - 2 * b;
	if (i % 5 || j % 5) return inf;
	return mp(i / 5, - j / 5);
}


pair<pii, int> solve(ll a, ll b) {
	rep(i, 0, 4) {
		x = a + dx[i];
		y = b + dy[i];
		t = check(x, y);
		if (t != inf) {
			if (i == 2) return mp(t, 3);
			if (i == 1) return mp(mp(t.fi - 1, t.se), 2);
			if (i == 0) return mp(mp(t.fi - 1, t.se - 1), 1);
			if (i == 3) return mp(mp(t.fi, t.se - 1), 0);
		}
	}
}

void print(pair<pii, int> p) {
	dd(p.fi.fi), dd(p.fi.se), de(p.se);
}

int get(int x, int y) {
	int t = abs(x - y);
	return min(t, 4 - t);
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> a >> b >> c >> d;
	p1 = solve(a, b);
	p2 = solve(c, d);
	ans = pw(60);
//	print(p1);
//	print(p2);
	if (p1.fi == p2.fi) ans = get(p1.se, p2.se);
	else {
		x = p2.fi.fi - p1.fi.fi;
		y = p2.fi.se - p1.fi.se;
		w[0] = abs(x);
		w[1] = abs(y);
		rep(o1, 0, 2)
			rep(o2, 0, 2) {
				if (w[o1] < 1) continue;
				if (w[o2] < 1) continue;
				if (o1 == o2 && w[o1] < 2 && w[0] + w[1] > 1) continue;
				num = (w[0] + w[1]) * 2 - 1;
				if (w[0] + w[1] > 1) {
					v[0] = w[0]; v[1] = w[1];
					v[o1]--; v[o2]--;
					if (o1 == o2) num += abs(v[o1] + 1 - v[o1 ^ 1]);
					else num += abs(v[o1] - v[o2]);
				}
				ans = min(ans, num + get(p1.se, o1 == 0 ? (x > 0 ? 1 : 3) : (y > 0 ? 0 : 2)) + 
					get(p2.se, o2 == 0 ? (x > 0 ? 3 : 1) : (y > 0 ? 2 : 0)));
			}
	} 
	cout << ans << endl;
	return 0;
}

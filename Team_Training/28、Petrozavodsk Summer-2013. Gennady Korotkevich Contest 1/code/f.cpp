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

vector<pii> vec;

bool cmp(pii a, pii b) {
	return a.fi * 1ll * b.se - a.se * 1ll * b.fi > 0;
}
void print(int a, int b) {
	cout << a << " " << b << endl;
}
void solve() {
	int n; cin >> n;
	if(n == 3) {
		cout << 1 << endl;
		cout << "0 0" << endl;
		cout << "0 1" << endl;
		cout << "1 0" << endl;
	} else if(n == 4) {
		cout << 4 << endl;
		cout << "0 0" << endl;
		cout << "1 0" << endl;
		cout << "1 1" << endl;
		cout << "0 1" << endl;
	} else if(n == 5) {
		cout << 3 << endl;
		cout << "0 0" << endl;
		cout << "2 0" << endl;
		cout << "2 1" << endl;
		cout << "1 2" << endl;
		cout << "0 1" << endl;
	} else if(n % 3 == 0) {
		int h = 1, tot = n / 3;
		cout << tot * 2 + 1 << endl;
		rep(i, 0, tot - 2) h += vec[i].se;
		cout << "0 0" << endl;
		cout << 0 << " " << h + 1 << endl;
		cout << 1 << " " << h + 1 << endl;
		cout << 1 << " " << h << endl;
		int x = 1, y = h;
		rep(i, 0, tot - 2) {
			print(x + vec[i].se, y + vec[i].fi);
			print(x + vec[i].se + vec[i].fi, y + vec[i].fi - vec[i].se);
			print(x = x + vec[i].fi, y = y - vec[i].se);
		}
		print(x + 1, y);
		print(x + 1, 0);
	} else if(n % 3 == 1) {
		n += 2;
		int h = 1, tot = n / 3;
		cout << tot * 2 - 1 << endl;
		rep(i, 0, tot - 2) h += vec[i].se;
		cout << "0 0" << endl;
		cout << 0 << " " << h + 1 << endl;
		cout << 1 << " " << h + 1 << endl;
		cout << 1 << " " << h << endl;
		int x = 1, y = h;
		rep(i, 0, tot - 3) {
			print(x + vec[i].se, y + vec[i].fi);
			print(x + vec[i].se + vec[i].fi, y + vec[i].fi - vec[i].se);
			print(x = x + vec[i].fi, y = y - vec[i].se);
		}
		print(x = x + vec[tot - 3].fi, y = y - vec[tot - 3].se);
		print(x + 1, y);
		print(x + 1, 0);
	} else {
		n -= 2;
		int h = 1, tot = n / 3;
		cout << tot * 2 + 2 << endl;
		rep(i, 0, tot - 2) h += vec[i].se;
		print(0, 0);
		print(0, h + 1);
		print(1, h + 1);
		print(1, h + 2);
		print(2, h + 2);
		print(2, h);
		int x = 2, y = h;
		rep(i, 0, tot - 2) {
			print(x + vec[i].se, y + vec[i].fi);
			print(x + vec[i].se + vec[i].fi, y + vec[i].fi - vec[i].se);
			print(x = x + vec[i].fi, y = y - vec[i].se);
		}
		print(x + 1, y);
		print(x + 1, 0);
	}
}

int main() {
	freopen("foss.in", "r", stdin);
	freopen("foss.out", "w", stdout);
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	rep(i, 1, 24) rep(j, 1, 24) if(__gcd(i, j) == 1) vec.pb(mp(i, j));
	sort(all(vec), cmp);
	int T; cin >> T;
	while(T--) solve();
	return 0;
}

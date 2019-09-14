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

const int N = 101010;

int n;
struct Node {
	string name, str;
	int rk, x, y, z;
	vi a;
	void gao() {
		a.clear();
		for(int i = 0; i < sz(str); ++i) {
			if(str[i] == '1') {
				a.pb(10); ++i;
			} else {
				auto c = str[i];
				if(c == 'A') a.pb(1);
				else if(c == 'J') a.pb(11);
				else if(c == 'Q') a.pb(12);
				else if(c == 'K') a.pb(13);
				else a.pb(c - '0');
			}
		}
		sort(all(a));
		if(a[0] == 1 && a[1] == 10 && a[2] == 11 && a[3] == 12 && a[4] == 13) {
			rk = 8;
		} else if(check()) {
			rk = 7; x = a[0];
		} else if(a[0] == a[3]) {
			rk = 6; x = a[0], y = a[4];
		} else if(a[1] == a[4]) {
			rk = 6; x = a[1], y = a[0];
		} else if(a[0] == a[2] && a[3] == a[4]) {
			rk = 5; x = a[0], y = a[3];
		} else if(a[0] == a[1] && a[2] == a[4]) {
			rk = 5; x = a[2], y = a[0];
		} else if(a[0] == a[2]) {
			rk = 4; x = a[0], y = a[3] + a[4];
		} else if(a[1] == a[3]) {
			rk = 4; x = a[1], y = a[0] + a[4];
		} else if(a[2] == a[4]) {
			rk = 4; x = a[2], y = a[0] + a[1];
		} else if(a[0] == a[1] && a[2] == a[3]) {
			rk = 3; x = a[2], y = a[0], z = a[4];
		} else if(a[0] == a[1] && a[3] == a[4]) {
			rk = 3; x = a[3], y = a[0], z = a[2];
		} else if(a[1] == a[2] && a[3] == a[4]) {
			rk = 3; x = a[3], y = a[2], z = a[0];
		} else if(check2()) {
			rk = 2; x = check2(), y = 0;
			for(auto u : a) if(u != x) y += u;
		} else {
			rk = 1; x = 0;
			for(auto u : a) x += u;
		}
	}
	bool operator < (const Node &c) const {
		if(rk != c.rk) return rk > c.rk;
		if(rk == 8) {
		} else if(rk == 7 || rk == 1) {
			if(x != c.x) return x > c.x;
		} else if(rk == 3) {
			if(x != c.x) return x > c.x;
			if(y != c.y) return y > c.y;
			if(z != c.z) return z > c.z;
		} else {
			if(x != c.x) return x > c.x;
			if(y != c.y) return y > c.y;
		}
		return name < c.name;
	}
	bool check() {
		rep(i, 1, 5) if(a[i] != a[i - 1] + 1) return 0;
		return 1;
	}
	int check2() {
		rep(i, 1, 5) if(a[i] == a[i - 1]) return a[i];
		return 0;
	}
}nd[N];

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	while(cin >> n) {
		rep(i, 1, n + 1) cin >> nd[i].name >> nd[i].str, nd[i].gao();
		sort(nd + 1, nd + 1 + n);
		rep(i, 1, n + 1) cout << nd[i].name << endl;
	}
	return 0;
}

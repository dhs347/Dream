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

int n;
ll tmp, t, x, op;
vector<ll> ans;

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n;
	t = 1; tmp = 0;
	rep(i, 1, n+1) {
		cin >> x;
		if (x <= 127) {		
			if (t == 1) {
				if (x % 2 == 1) {
					x = x + 1;
					x /= 2;
					op = -1;
					tmp += x * t;
				}else {
					op = 1;
					x = x / 2;
					tmp += x * t;
				}
			}
			else tmp += x * t;
			ans.pb(tmp * op);
			tmp = 0; t = 1;
		} else {
			x -= 128;
			if (t == 1) {
				if (x % 2 == 1) {
					x = x + 1;
					x /= 2;
					op = -1;
					tmp += x * t;
					t <<= 6;
				}else {
					op = 1;
					x = x / 2;
					tmp += x * t;
					t <<= 6;
				}
			}
			else tmp += x * t, t <<= 7;
		}
	}
	for (auto v : ans) {
		cout << v  << endl;
	}

	return 0;
}

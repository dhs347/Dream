#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define de(x) cout << #x << " = " << x << endl
#define dd(x) cout << #x << " = " << x << " "
#define endl "\n"
#define pw(x) (1ll<<(x))
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()
typedef long long ll;
typedef pair<int, int> pii;
typedef double db;
typedef vector<int> vi;

int a[1000][1000];

void solve() {
	int n, k; cin >> n >> k;
	if(n * 1ll * (n + 1) / 2 % k) {
		cout << "no" << endl;
		return ;
	}
	if(k == 1) {
		cout << "yes" << endl;
		rep(i, 1, n + 1) cout << i << " \n"[i == n];
		return ;
	}
	if(n % 2 == 0) {
		cout << "yes" << endl;
		int t = n / k;
		int l = 1, r = n;
		rep(i, 1, k + 1) {
			rep(j, 1, t + 1) {
				int c = (j & 1) ? l++ : r--;
				cout << c << " \n"[j == t];
			}
		}
	} else {
		if(n == 1ll * k * k) {
			cout << "yes" << endl;
			int x = 1, y = k / 2 + 1;
			rep(i, 1, n + 1) {
				a[x][y] = i;
				if(i % k == 0) {
					++x;
					if(x == k + 1) x = 1;
				} else {
					--x, ++y;
					if(x == 0) x = k;
					if(y == k + 1) y = 1;
				}
			}
			rep(i, 1, k + 1) {
				ll sum = 0;
				rep(j, 1, k + 1) cout << a[i][j] << " \n"[j == k], sum += a[i][j];
				while(!(sum == n * 1ll * (n + 1) / 2 / k));
			}
		} else {
			cout << "no" << endl;
		}
	}
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int T; cin >> T;
	while(T--) solve();
	return 0;
}

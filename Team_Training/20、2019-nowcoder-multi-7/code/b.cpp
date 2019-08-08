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
#define all(x) x.begin(), x.end()
#define pw(x) (1ll<<(x))
#define sz(x) (int)x.size()
typedef long long ll;
typedef pair<int, int> pii;
typedef double db;
typedef vector<int> vi;

ll a[100];
int T, n;
int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> T;
	rep(cas, 0, T) {
		cin >> n;
		rep(i, 0, n+1) cin >> a[i];
		if (n > 2) {
			cout << "No";
		}
		if (n < 2) cout << "Yes";
		if (n == 2) {
			if (a[1] * a[1] - 4 * a[0] * a[2] < 0) cout << "Yes";
			else cout << "No";
		}
		cout << endl;
	}
	return 0;
}

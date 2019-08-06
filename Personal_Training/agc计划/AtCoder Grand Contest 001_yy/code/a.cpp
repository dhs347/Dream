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
#define pw(x) (1ll<<(x))
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()
#define endl "\n"
typedef long long ll;
typedef pair<int, int> pii;
typedef double db;
typedef vector<int> vi;

int a[111];

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int n; cin >> n; n <<= 1;
	rep(i, 1, n + 1) cin >> a[i];
	sort(a + 1, a + 1 + n);
	ll ans = 0;
	for(int i = 1; i < n; i += 2) ans += a[i];
	cout << ans << endl;
	return 0;
}

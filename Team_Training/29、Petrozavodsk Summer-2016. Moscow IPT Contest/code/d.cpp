#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define de(x) cout << #x << " = " << x << endl
#define dd(x) cout << #x << " = " << x << " "
#define endl '\n'
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()
#define pw(x) (1ll<<(x))
typedef long long ll;
typedef double db;
typedef vector<int> vi;
typedef pair<int, int> pii;

const int N = 1e6 + 10;
db a[N], h, ans;
int n;
int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n >> h;
	rep(i, 1, n+1) cin >> a[i];
	reverse(a+1, a+n+1);
	a[++n] = h;
	rep(i, 1, n+1) ans += max(0.0, (a[i] - a[i-1]) - ans / 2);
	printf("%.10f", ans);
	return 0;
}

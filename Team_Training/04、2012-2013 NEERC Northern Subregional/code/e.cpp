#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define sz(a) (int)a.size()
#define de(a) cout << #a << " = " << a << endl
#define dd(a) cout << #a << " = " << a << " "
#define all(a) a.begin(), a.end()
#define pw(x) (1ll << (x))
#define endl "\n"
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int N = 1e5 + 6;
int n, m, s1, s2, ans, cnt, a[N], b[N];

int main() {
	freopen("electricity.in", "r", stdin);
	freopen("electricity.out", "w", stdout);
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n >> m;
	rep(i, 1, n+1) cin >> a[i], s1 += a[i];
	rep(i, 1, m+1) cin >> b[i];
	sort(b+1, b+m+1);
	per(i, 1, m+1) {
		if (cnt + 1 <= s1) s2 += b[i], cnt++;else break;
	}
	sort(a+1, a+n+1);
	ans = s2 + 1;
	per(i, 1, n+1) {
		ans--;
		cnt -= a[i];
		if (cnt <= 0) break;
	} 
	cout << ans << endl;
	return 0;
}

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

const int N = 101010;

int n, x;
int a[N], p[N], b[N];

bool check(int x) {
	int k = x + a[1], p = 1;
	int cnt = 0;
	rep(i, 2, n + 1) {
		while(p <= n && (a[i] + b[p] <= k || (b[p] == x && (p == 1 || b[p] != b[p - 1])))) ++p;
		if(p <= n) {
			++cnt; ++p;
		} else {
			break;
		}
	}
	return cnt < ::x;
}

int main() {
	freopen("hop.in", "r", stdin);
	freopen("hop.out", "w", stdout);
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n >> x;
	rep(i, 1, n + 1) cin >> a[i];
	rep(i, 1, n + 1) cin >> p[i], b[i] = p[i];
	sort(a + 2, a + 1 + n);
	reverse(a + 2, a + 1 + n);
	sort(b + 1, b + 1 + n);
	int l = 1, r = n, ans = -1;
	while(l <= r) {
		int mid = l + r >> 1;
		if(check(p[mid])) {
			ans = mid;
			l = mid + 1;
		} else {
			r = mid - 1;
		}
	}
	cout << ans << endl;
	return 0;
}

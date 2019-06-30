#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define dd(a) cout << #a << " = " << a << " " 
#define de(a) cout << #a << " = " << a << endl
#define sz(a) (int)a.size()
#define all(a) a.begin(), a.end()
#define pw(a) (1ll << (a))
#define endl "\n"
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef double db;

const int N = 101010;

int n;
int a[N], pre[N];
pii ans[N];

int gao(int x) {
	int l = x, r = n, ans = x;
	while(l <= r) {
		int mid = l + r >> 1;
		if(pre[mid] - pre[x - 1] == (pre[x] - pre[x - 1]) * (mid - x + 1)) {
			ans = mid;
			l = mid + 1;
		} else {
			r = mid - 1;
		}
	}
	return ans;
}

void solve(int x) {
	if(ans[x].fi) {
		cout << ans[x].fi << " " << ans[x].se << endl;
		return ;
	}
	for(int i = 1; i <= n; ) {
		if(i == n) {
			ans[x].fi++;
			break;
		}
		int r = gao(i + 1);
		if(r - i + 1 < x) {
			int nr = min(n, r + x - (r - i + 1));
			ans[x].se += nr - r, r = nr;
		}
		ans[x].fi++;
		i = r + 1;
	}
	cout << ans[x].fi << " " << ans[x].se << endl;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n;
	rep(i, 1, n + 1) cin >> a[i];
	pre[1] = 0;
	rep(i, 2, n + 1) {
		pre[i] = pre[i - 1] + (a[i] >= a[i - 1]);
	}
	int q; cin >> q;
	while(q--) {
		int x; cin >> x; solve(x);
	}
	return 0;
}

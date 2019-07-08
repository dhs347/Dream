#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define endl "\n"
#define pw(x) (1ll << (x))
#define all(a) a.begin(), a.end()
#define sz(a) (int)a.size()
#define dd(x) cout << #x << " = " << x << " "
#define de(x) cout << #x << " = " << x << endl
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int N = 1010101;

int n;
int a[N];
int ans[N];

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	memset(ans, -1, sizeof(ans));
	cin >> n;
	rep(i, 1, n + 1) cin >> a[i];
	int cnt[2] = {0};
	rep(i, 1, n + 1) {
		if(a[i] % 15 == 0) {
		} else if(a[i] % 3 == 0) {
			++cnt[0];
			ans[i] = 0;
		} else {
			++cnt[1];
			ans[i] = 1;
		}
	}
//	rep(i, 1, n + 1) cout << (ans[i] == -1 ? ' ' : (ans[i] == 0 ? 'F' : 'B')); cout << endl;
	rep(i, 1, n + 1) if(ans[i] == -1) {
		if(cnt[0] <= n / 8. * 3) {
			++cnt[0];
			ans[i] = 0;
		} else {
			ans[i] = 1;
		}
	}
	rep(i, 1, n + 1) cout << (ans[i] == 0 ? 'F' : 'B'); cout << endl;
	return 0;
}

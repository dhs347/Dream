#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define dd(x) cout << #x << " = " << x << " "
#define de(x) cout << #x << " = " << x << endl
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()
#define endl '\n'
#define pw(x) (1ll<<(x))
typedef long long ll;
typedef pair<int, int> pii;
typedef double db;
typedef vector<int> vi;

const int N = 50000 + 5, inf = N;

int n = 100;
int a[N], f[N], ok[N], b[N], c[N];

void test() {
	srand(time(0));
	rep(i, 1, n + 1) a[i] = i;
	rep(i, 1, n+1) b[i] = i;
	random_shuffle(a + 1, a + 1 + n);
	random_shuffle(b + 1, b + 1 + n);
	int ans = 0;
	rep(n, 1, 101) {
		rep(i, 0, n + 2) f[i] = inf;
		rep(i, 1, n+1) ok[b[i]] = 1;
		int m = 0;
		rep(i, 1, n+1) if (ok[i]) c[++m] = a[i];
		rep(i, 1, n + 1) {
			int p = lower_bound(f + 1, f + 1 + n, c[i]) - f;
			ans = max(ans, p);
			f[p] = c[i];
		}
		de(ans);
	}
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	test();
	return 0;
}

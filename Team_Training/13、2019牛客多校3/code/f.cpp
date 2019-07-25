#include<bits/stdc++.h>
using namespace std;
#define fi first 
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a) --i)
#define de(c) cout << #c << " = " << c << endl
#define dd(c) cout << #c << " = " << c << " "
#define all(c) c.begin(), c.end()
#define sz(x) (int)x.size()
#define endl '\n'
#define pw(x) (1ll << (x))
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef double db;

const int N = 505, inf = 1e9;

int n, m;
int vec[N][N], a[N], b[N], q1[N], l1, r1, q2[N], l2, r2;

void solve() {
	cin >> n >> m;
	//	de(m);
	rep(i, 1, n + 1) rep(j, 1, n + 1) cin >> vec[i][j];//, dd(i), dd(j), de(vec[i][j]);
	int ans = 0;
	rep(L, 1, n + 1) {
		rep(i, 1, n + 1) a[i] = 0, b[i] = inf;
		rep(R, L, n + 1) {
			//		dd(L), de(R);
			l1 = l2 = 1; r1 = r2 = 0;
			int p = 1;
			rep(i, 1, n + 1) {
				a[i] = max(a[i], vec[R][i]);
				b[i] = min(b[i], vec[R][i]);
				//dd(i), dd(a[i]), dd(b[i]);
				// q1 max
				while(l1 <= r1 && a[q1[r1]] <= a[i]) --r1;
				q1[++r1] = i;
				while(l2 <= r2 && b[q2[r2]] >= b[i]) --r2;
				q2[++r2] = i;
				//	dd(a[q1[l1]]), dd(b[q2[l2]]), dd(p), de(i);
				while(p <= i) {
					if(a[q1[l1]] - b[q2[l2]] <= m) {
						ans = max(ans, (R - L + 1) * (i - p + 1));
						//	dd(a[q1[l1]]), dd(b[q2[l2]]), dd(p), dd(i), dd(L), de(R);
						break;
					}
					++p;
					while(l1 <= r1 && q1[l1] < p) ++l1;
					while(l2 <= r2 && q2[l2] < p) ++l2;
				}
			}
			//		cout << endl;
		}
	}
	cout << ans << endl;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int T; cin >> T;
	while(T--) solve();
	return 0;
}

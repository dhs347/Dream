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
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()
#define pw(x) (1ll<<(x))
typedef long long ll;
typedef long double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int N = 1005;
int n, A, B, a[N], p[N];
db ans, f[N][N], dp[N][N], w[N];

int main() {
//	std::ios::sync_with_stdio(0);
//	std::cin.tie(0);
	cin >> n >> A >> B;
	int m = 501;
	srand(time(0));
	rep(i, 1, n+1) {
		cin >> a[i];
		//a[i] = rand() % 500 + 1;
	}
/*	A = 300;  B = 500;
	rep(i, 1, n+1) p[i] = i;
	ll cnt = 0, cnt2 = 0, sum;
	do  {
		sum = 0;
		rep(i, 1, n+1) {
			sum += a[p[i]];
			if (sum > A) {
				if (sum <= B) cnt++;
				break;
			}
		}
		cnt2++;
	} while (next_permutation(p + 1, p + n + 1));
	printf("%.10f\n", cnt * 1.0 / cnt2);
*/
	rep(i, 1, n+1) w[i] = (db)i / (n - i + 1);
	f[0][0] = 1;
	rep(i, 1, n+1) per(j, 1, n+1) rep(s, 0, m - a[i]+1) {
		f[j][s + a[i]] += f[j - 1][s] * w[j];
		//j / (n - j + 1);
	}
	rep(i, 1, n+1) {
		int l = A - a[i] + 1, r = min(B - a[i], A);
		l = max(l, 0);
		if (l > r) continue;
		rep(j, 0, n+1) rep(k, 0, r+1) dp[j][k] = f[j][k];
		rep(j, 1, n+1) rep(k, a[i], r+1) {
			dp[j][k] -= dp[j - 1][k - a[i]] * w[j];//* j / (n - j + 1);
		}
		rep(j, 0, n) {
			db tmp = 0;
			rep(k, l, r+1) tmp += dp[j][k];
			ans += tmp / (n - j);
		}
	}
	//cout << ans << endl;
	printf("%.10Lf", ans);
	return 0;
}

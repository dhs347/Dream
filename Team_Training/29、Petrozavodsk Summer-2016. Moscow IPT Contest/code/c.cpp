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

const int N = 505;
int n, m, B, C, a[N], f[2][N][N * 2], o, ans;

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n >> m >> B >> C;
	rep(i, 1, n+1) cin >> a[i];
	o = 0; int d = n;
	memset(f, 10, sizeof(f));
	f[0][0][d] = 0;
	rep(i, 0, n) {
		rep(j, 0, m+1) rep(l, -n, n+1) {
			int k = d + l;
			int w = f[o][j][k];
			if (j > 0) {
				int &t1 = f[o ^ 1][j+1 >= m ? 0 : j + 1][k];
				t1 = min(t1, w);
				int &t2 = f[o ^ 1][j+1 >= m ? 0 : j + 1][k + 1];
				t2 = min(t2, w + a[i+1] + C);
			}else {
				int &t1 = f[o ^ 1][j][k];
				t1 = min(t1, w + a[i+1]);
				int &t2 = f[o ^ 1][j+1 >= m ? 0 : j + 1][k];
				t2 = min(t2, w + B);
				//if (k - 1 >= 0) {
					int &t3 = f[o ^ 1][j][k-1];
					t3 = min(t3, w);
				//}
			}
		}
		memset(f[o], 10, sizeof(f[o]));
		o ^= 1;
	}
	ans = pw(30);
	rep(i, 0, m+1) rep(k, d, d+n+1) ans = min(ans, f[o][i][k]);
	cout << ans << endl;
	return 0;
}

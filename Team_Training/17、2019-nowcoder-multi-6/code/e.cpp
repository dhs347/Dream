#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define pb push_back
#define mp make_pair
#define de(x) cout << #x << " = " << x << endl
#define dd(x) cout << #x << " = " << x << " "
#define endl "\n"
#define pw(x) (1ll<<(x))
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()
typedef long long ll;
typedef pair<int, int> pii;
typedef double db;
typedef vector<int> vi;
 
const int N = 2020;
 
int ans[N][N], use[N][N], ans2[N][N], p[N], m;
void get(int n) {
	int m = n / 4;
	rep(i, 1, m+1) rep(j, i+1, m+1) ans[i][j] = ans[j][i] = 1;
	rep(i, n - m + 1, n+1) rep(j, i + 1, n+1) ans[i][j] = ans[j][i] = 1;
	rep(i, 1, m+1) rep(j, m+1, m+m+1) ans[i][j] = ans[j][i] = 1;
	rep(i, m+1, m+m+1) rep(j, m+m+1, m+m+m+1) ans[i][j] = ans[j][i] = 1;
	rep(i, m+m+1, m+m+m+1) rep(j, m+m+m+1, m+m+m+m+1) ans[i][j] = ans[j][i] = 1;
	rep(i, 1, m+1) p[i] = i + m;
	rep(i, m+1, m+m+1) p[i] = i + m + m;
	rep(i, m+m+1, m+m+m+1) p[i] = i - m - m;
	rep(i, m+m+m+1, m+m+m+m+1) p[i] = i - m;

}
 
void solve() {
    int n; cin >> n;
    if((n % 4) > 1) { cout << "No" << endl; return ; }
    cout << "Yes" << endl;
    if(n == 1) {
        cout << 0 << endl << 1 << endl;
        return ;
    }
    rep(i, 1, n+1) rep(j, 1, n+1) ans[i][j] = 0;
    if (n & 1) {
		get(n - 1);
		m = (n - 1) / 4;
		rep(i, 1, m+1) ans[i][n] = ans[n][i] = 1;
		rep(i, n - m, n) ans[i][n] = ans[n][i] = 1;
		p[n] = n;
	}else get(n);
	rep(i, 1, n+1) rep(j, 1, n+1) if (i != j) ans2[i][j] = ans[i][j] ^ 1;
	rep(i, 1, n+1) rep(j, 1, n+1) if (i != j) assert(ans[i][j] == ans2[p[i]][p[j]]);
	rep(i, 1, n+1) {
        rep(j, 1, n+1) cout << ans[i][j];
        cout << endl;
    }
    rep(i, 1, n+1) cout << p[i] << " \n"[i == n];
}
 
int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    int T; cin >> T;
    rep(i, 1, T + 1) cout << "Case #" << i << ": ", solve();
    return 0;
}

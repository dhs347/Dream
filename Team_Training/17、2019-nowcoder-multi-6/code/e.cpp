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
 
int ans[N][N], use[N][N], tmp[N][N], p[N];
void get(int n) {
    if (n == 4) {
        rep(i, 1, 4+1) rep(j, 1, 5) ans[i][j] = 0;
        ans[1][2] = ans[2][1] = 1;
        ans[2][3] = ans[3][2] = 1;
        ans[3][4] = ans[4][3] = 1;
        p[1] = 2; p[2] = 4; p[3] = 1; p[4] = 3;
        return;
    }
    get(n / 2);
    int m = n / 2;
    rep(i, m+1, n+1) p[i]  = p[i - m] + m;
    rep(i, 1, n+1) rep(j, 1, n+1) use[i][j] = 0;
    rep(i, 1, n+1) rep(j, i+1, n+1) {
        if (i <= m && j <= m) tmp[i][j] = ans[i][j];
        if (i > m && j > m) tmp[i][j] = ans[i - m][j - m];
        if (i <= m && j > m) {
            if (use[i][j] == 0 && use[p[i]][p[j]] != 1) {
                use[i][j] = 1;
                use[p[i]][p[j]] = 2;
                tmp[i][j] = 1;
            }
            if (use[p[i]][p[j]] == 1) use[i][j] = 2;
        }
    }
    rep(i, 1, n+1) rep(j, i+1, n+1) tmp[j][i] = tmp[i][j];
    rep(i, 1, n+1) rep(j, 1, n+1) ans[i][j] = tmp[i][j];
}
 
void solve() {
    int n; cin >> n;
    if(n % 4 > 1) { cout << "No" << endl; return ; }
    cout << "Yes" << endl;
    if(n == 1) {
        cout << 0 << endl << 1 << endl;
        return ;
    }
    if(n == 4) {
        cout << "0100" << endl;
        cout << "1010" << endl;
        cout << "0101" << endl;
        cout << "0010" << endl;
        cout << "2 4 1 3" << endl;
        return ;
    }
    if (n == 2 || n == 3) { cout << "No"; return; }
    if ()
    rep(i, 1, n+1) cout << p[i] << " \n"[i == n];
}
 
int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    int T; cin >> T;
    rep(i, 1, T + 1) cout << "Case #" << i << ": ", solve();
    return 0;
}

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
#define pw(x) (1ll<<(x))
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()
typedef long long ll;
typedef double db;
typedef vector<int> vi;
typedef pair<int, int> pii;

int n, m, a[2000][2000];

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> m;
	n = 1;
	a[n][n] = 1;
	while (n < m) {
		rep(i, 1, n+1) rep(j, n+1, 2*n+1) a[i][j] = a[i][j-n];
		rep(i, n+1, 2*n+1) rep(j, 1, n+1) a[i][j] = a[i - n][j];
		rep(i, n+1, 2*n+1) rep(j, n+1, 2*n+1) a[i][j] = -a[i-n][j-n];
		n *= 2;
	}
	rep(i, 1, m+1) rep(j, 1, m+1) cout << a[i][j] << " \n"[j == m];
	return 0;
}

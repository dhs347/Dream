#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define de(x) cout << #x << " = " << x << endl
#define dd(x) cout << #x << " = " << x << " "
#define endl "\n"
#define pw(x) (1ll<<(x))
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()
typedef long long ll;
typedef pair<int, int> pii;
typedef double db;
typedef vector<int> vi;

int n = 4;
int a[5][5];

void gao(int x, int y, int val) {
	int nx, ny;
	rep(i, x, n) rep(j, 0, n) if(!a[i][j]) nx = i, ny = j;
	while(ny < y) {
		swap(a[nx][ny], a[nx][ny + 1]);
		ny++;
	}
	while(ny > y) {
		swap(a[nx][ny], a[nx][ny - 1]);
		ny--;
	}
	while(nx > x) {
		swap(a[nx][ny], a[nx - 1][ny]);
		nx--;
	}
	rep(i, x, n) rep(j, 0, n) if(a[i][j] == val) nx = i, ny = j;
	if(ny < y) {
		swap(a[x][y], a[x + 1][y]);
		gao(x + 1, y, nx, ny);

	} else {
		gao(x, y, nx, ny);
	}
}

bool solve() {
	rep(i, 0, n) rep(j, 0, n) cin >> a[i][j];
	int p = 0;
	rep(i, 0, n - 1) rep(j, 0, n) {
		++p;
		if(a[i][j] != p) gao(i, j, p);
	}
	sort(a[3], a[3] + n);
	rep(i, 1, n) if(a[3][i] != i + 12) return 0;
	return 1;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int T; cin >> T;
	while(T--) cout << (solve() ? "Yes" : "No") << endl;
	return 0;
}

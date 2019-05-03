#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define sz(a) (int)a.size()
#define de(a) cout << #a << " = " << a << endl
#define dd(a) cout << #a << " = " << a << " "
#define all(a) a.begin(), a.end()
#define pw(x) (1ll << (x))
#define endl "\n"
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int N = 10;

int n = 10, x, y;
int a[N][N], ans[N][N];

void gao(int x, int y, int len) {
	rep(j, y, y + len) ans[x][j] = 1;
}

void solve(int x, int o) {
	if(o == 1) {
		if(y == 4 || y == 8) {
			gao(x, 0, 1);
			gao(x, 2, 3);
			gao(x, 6, 4);
		} else {
			gao(x, 0, 4);
			gao(x, 5, 3);
			gao(x, 9, 1);
		}
	} else if(o == 2) {
		gao(x, 0, 3);
		gao(x, 4, 2);
		gao(x, 7, 2);
	} else {
		gao(x, 0, 2);
		gao(x, 3, 1);
		gao(x, 5, 1);
		gao(x, 7, 1);
	}
}

int main() {
	freopen("battleship.in", "r", stdin);
	freopen("battleship.out", "w", stdout);
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	rep(i, 0, n) rep(j, 0, n) {
		cin >> a[i][j];
		if(a[i][j] == 100) x = i, y = j;
	}
	solve(x, 1);
	int cnt = 2;
	for(int j = x - 2; j >= 0 && cnt <= 3; j -= 2) solve(j, cnt++);
	for(int j = x + 2; j < n  && cnt <= 3; j += 2) solve(j, cnt++);
	rep(i, 0, n) {
		rep(j, 0, n) cout << (ans[i][j] ? '#' : '.');
		cout << endl;
	}
	return 0;
}

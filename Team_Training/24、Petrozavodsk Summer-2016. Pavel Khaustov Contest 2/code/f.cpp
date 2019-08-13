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
#define pw(x) (1ll<<(x))
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int N = 6;

bool a[N][N];

bool check() {
	rep(i, 0, 6) rep(j, i + 1, 6) {
		int cnt = 0;
		rep(k, 0, 6) cnt += (a[i][k] != a[j][k]);
		if(cnt < 3) return 0;
		cnt = 0;
		rep(k, 0, 6) cnt += (a[k][i] != a[k][j]);
		if(cnt < 3) return 0;
	}
	return 1;
}

void tes() {
	rep(x, 0, pw(36)) {
		int p = 0;
		rep(i, 0, 6) rep(j, 0, 6) a[i][j] = (x >> p & 1), ++p;
		if(check()) {
			rep(i, 0, 6) {
				cout << "\"";
				rep(j, 0, 6) cout << (char)(a[i][j] + 'A');
				cout << "\",";
				cout << endl;
			}
			cout << endl;
			return ;
		}
	}
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	tes();
	return 0;
}

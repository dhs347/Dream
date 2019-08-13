#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define de(x) cout << #x << " = " << x << endl
#define dd(x) cout << #x << " = " << x << " " 
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define endl '\n'
#define pw(x) (1ll <<(x))
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

void solve(int n, int m) {
	dd(n), dd(m);
	--n, --m;
	int cnt = 0;
	rep(i, 0, n + 1) rep(j, 0, m + 1) {
		if(i ^ (n - i) ^ j ^ (m - j)) {
		} else ++cnt;
	}
	de(cnt);
}

int main() {
	//freopen(".in", "r", stdin);
	//freopen(".out", "w", stdout);
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	solve(10000, 10000);
	//rep(n, 1, 50) rep(m, n, 50) solve(n, m);
	return 0;
}

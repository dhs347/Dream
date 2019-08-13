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

map<pair<pii, int>, ll> M;
int n, m, T; 

ll solve(int n, int m, int k) {
	if (k < 0) return n == 0 && m == 0; 
	if (n > m) swap(n, m);
	auto t = mp(mp(n, m), k);
	ll s = 2 * (pw(k+1) - 1);
	if (n < 0 || m < 0 || n > s || m > s) return 0;
	if (M.find(t) != M.end()) return M[t];
	ll res = 0;
	res += solve(n - pw(k+1), m, k-1);
	res += solve(n - pw(k+1), m - pw(k+1), k-1);
	res += solve(n, m - pw(k+1), k-1);
	res += solve(n, m, k-1);
	res += 4 * solve(n - pw(k), m - pw(k), k-1);
	return M[t] = res;
}

int main() {
	freopen("chocolate.in", "r", stdin);
	freopen("chocolate.out", "w", stdout);
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> T;
	//T = 10000;
	rep(cas, 0, T) {
		cin >> n >> m;
		//n = 1ll * rand() * rand() % 1000000000;
		//m = 1ll * rand() * rand() % 1000000000;
		cout << solve(n - 1, m - 1, 30) << endl;
	}
	return 0;
}

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

int n, a[2000], p, d, k;

int solve(){ 
	if (d == 1) {
		if (n == k) {
			if (p % n) return 0;
			rep(i, 1, n+1) a[i] = p / n;
		}else {
			rep(i, 1, k+1) a[i] = p / k;
			a[k+1] = p % k;
			return 1;
		}
	}else {
		if (d * (d - 1) / 2 > p) return 0;
		rep(i, 1, d+1) a[i] = d - i;
		a[1] += p - d * (d - 1) / 2;
		return 1;
	}
}
int main() {
	freopen("final.in", "r", stdin);
	freopen("final.out", "w", stdout);
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n >> p >> k >> d;
	int ok = solve();
	if (!ok) cout << "Wrong information";
	else rep(i, 1, n+1) cout << a[i] << endl;
	return 0;
}

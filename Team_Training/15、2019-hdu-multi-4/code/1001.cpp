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

const int N = 3e5;
int T, n, p, ans[N];

int get(int n) {
	int p = 0;
	rep(i, 0, 22) if (pw(i) <= n) p = i;	
	return pw(p);
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> T;
	rep(cas, 0, T) {
		cin >> n;
		rep(i, 0, 22) if (pw(i) <= n) p = i;
		p = pw(p);
		if (n == p + p - 1) cout << 1 << endl;else cout << 0 << endl;
		rep(i, 2, n+1) {
			int t = get(i);
			if (i == t + t - 1) {
				if (t + t <= n) ans[i] = t + t;
				else ans[i] = 1;
			}else {
				rep(j, 0, 22) if (!(pw(j) & i)) {ans[i] = pw(j); break;}
			}
		}
		rep(i, 2, n+1) cout << ans[i] << " \n"[i == n]; 
	}
	return 0;
}

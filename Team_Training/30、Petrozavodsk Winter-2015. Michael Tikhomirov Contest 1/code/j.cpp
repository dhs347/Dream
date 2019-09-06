#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define rep(i, a, b) for(int i=(a); i<(b); i++)
#define per(i, a, b) for(int i=(b)-1; i>=(a); i--)
#define sz(a) (int)a.size()
#define de(a) cout << #a << " = " << a << endl
#define dd(a) cout << #a << " = " << a << " "
#define all(a) a.begin(), a.end()
#define pw(x) (1ll<<(x))
#define endl "\n"
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	int n, m; cin >> n >> m;
	if(n == 3) {
		cout << "2\n1 2\n2 3\n";
	} else {
		vector<pii> vec;
		rep(i, 1, 101) rep(j, i + 1, 101) vec.pb(mp(i, j));
		rep(i, 101, 201) vec.pb(mp(i, i - 1));
		cout << sz(vec) << endl;
		for(auto u : vec) cout << u.fi << " " << u.se << endl;
	}
	return 0;
}


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
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()
typedef long long ll;
typedef pair<int, int> pii;
typedef double db;
typedef vector<int> vi;

string s;
int ans;
vi tmp;
int main() {
	freopen("bad.in", "r", stdin);
	freopen("bad.out", "w", stdout);
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> s;
	rep(i, 0, sz(s)) if (s[i] == '1') tmp.pb(i);
	int n = sz(tmp);
	tmp.pb(sz(s));
	ans = pw(30);
	if (n == 0) {
		cout << 0 << endl;
		return 0;
	}else if (n == 1) {
		cout << min(tmp[0], sz(s) - tmp[0]) * 7 + 4;
		return 0;
	}else {
		rep(i, 0, sz(tmp) - 1) {
			int t1 = tmp[i];
			int t2 = sz(s) - tmp[i+1];
			ans = min(ans, min(t1, t2) + t1 + t2);
		}
		ans = min(ans, sz(s) - tmp[0]); 
		cout << ans * 7 + n * 4 << endl;
	}
	return 0;
}

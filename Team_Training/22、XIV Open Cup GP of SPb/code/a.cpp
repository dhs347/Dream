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
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

int n;
string s;

ll solve(int l, int r) {
	if (l > r) return 1;
	ll cnt = 0;
	rep(i, l, r+1) {
		if (s[i] == '(') cnt++;else cnt--;
		if (cnt == 0) {
			return (solve(l+1, i-1) + 1) * solve(i + 1, r);
		}
	}
}

int main() {
	freopen("bracket-expression.in", "r", stdin);
	freopen("bracket-expression.out", "w", stdout);
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> s;
	n = sz(s);
	cout << solve(0, n-1) << endl;
	return 0;
}

#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define endl "\n"
#define pw(x) (1ll << (x))
#define all(x) x.begin(), x.end()
#define sz(a) (int)a.size()
#define de(x) cout << #x << " = " << x << endl
#define dd(x) cout << #x << " = " << x << " "
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

string s, t;
int n, m;

bool check() {
	if(s[0] != t[0] || s[n - 1] != t[n - 1]) return 1;
	sort(all(s));
	sort(all(t));
	rep(i, 0, n) if(s[i] != t[i]) return 1;
	return 0;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	while(cin >> s >> t) {
		n = sz(s), m = sz(t);
		if(s == t) {
			cout << "Equal" << endl;
		} else if(n != m || check()) {
			cout << "No" << endl;
		} else {
			cout << "Yes" << endl;
		}
	}	
	return 0;
}

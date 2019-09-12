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
typedef unsigned int uint;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int N = pw(21);

uint f[N], g[32], s[N], ini[5];
int main() {
	freopen("forbidden-words.in", "r", stdin);
	freopen("forbidden-words.out", "w", stdout);
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	rep(i, 0, 32) {
		uint &k = g[i];
		rep(j, 0, 5) if(!(i >> j & 1)) k |= pw(i | pw(j));
	}
	rep(i, 0, 5) rep(j, 0, 32) if(!(j >> i & 1)) ini[i] |= pw(j);
	int n; cin >> n;
	rep(i, 1, n + 1) {
		string s; cin >> s;
		int j = 0; for(auto c : s) j |= pw(c - 'a');
		::s[j >> 5] |= pw(j & 31);
	}
	rep(i, 0, 26) {
		if(i >= 5) {
			int x = i - 5;
			rep(j, 0, N) if(j >> x & 1) s[j] |= s[j ^ pw(x)];
		}
		else {
			rep(j, 0, N) {
				uint t = s[j] & ini[i];
				s[j] |= (uint)(t << pw(i));
			}
		}
	}
	per(i, 0, N) {
		rep(j, 0, 21) if(!(i >> j & 1)) f[i] |= f[i | pw(j)];
		per(j, 0, 32) {
			if(s[i] >> j & 1) f[i] &= ((pw(32) - 1) ^ pw(j));
			else {
				if(f[i] & g[j]) f[i] |= pw(j);
				f[i] ^= pw(j);
			}
		}
	}
	cout << ((f[0] & 1) ? "Second" : "First") << endl;
	return 0;
}


#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define pb push_back
#define mp make_pair
#define de(x) cout << #x << " = " << x << endl
#define dd(x) cout << #x << " = " << x << " "
#define endl "\n"
#define pw(x) (1ll<<(x))
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()
typedef long long ll;
typedef pair<int, int> pii;
typedef double db;
typedef vector<int> vi;

int T;
string s, s2;
int a[2000], c1,c2, c3;

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> T;
	rep(cas, 1, T+1) {
		cin >> s >> s2;
		c1 = c2 = c3 = 0;
		rep(i, 0, 26) a[i + 'a'] = s2[i];
		for (auto u : s) {
			if (a[u] == 'd') c1++;
			if (a[u] == 'w') c2++;
			if (a[u] == 'h') c3++;
		}
		cout << "Case #" << cas << ": ";
		if (c3 * 10 <= sz(s)) cout << "Recyclable";
		else if (c3 * 4 >= sz(s)) cout << "Harmful";
		else if (c1 >= 2 * c2) cout << "Dry";
		else cout << "Wet";
		cout << endl;
	}
	return 0;
}

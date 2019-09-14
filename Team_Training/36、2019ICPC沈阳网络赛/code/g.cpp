#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); i++)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define de(x) cout << #x << " = " << x << endl
#define dd(x) cout << #x << " = " << x << " " 
#define endl '\n'
#define pw(x) (1ll<<(x))
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

int T, n;
db x, a;
string s;
int main() {
	//std::ios::sync_with_stdio(0);
	//std::cin.tie(0);
	//printf("%.12f\n", 1 / (1 / x + 1.0 / 3));
	//return 0;
	cin >> T;
	rep(cas, 0, T) {
		cin >> s;
		x = 15.0 / 4;
		if (sz(s) >= 3) n = 100;
		else {
			n = 0;
			rep(i, 0, sz(s)) n = n * 10 + s[i] - '0';
		}		
		cin >> a;
		rep(i, 1, n) {		
			x = (18 * x + 9) / (5 * x + 3);
		}
		printf("%.10f\n", 1 / (1 / x + 1.0 / 3));
	}
	return 0;
}

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
#define pw(x) (1ll<<(x))
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()
#define endl "\n"
typedef long long ll;
typedef pair<int, int> pii;
typedef double db;
typedef vector<int> vi;

const int P = 998244353, N = 1e5 + 7;

int T, f[N], s[N], x, y, n;
int add(int a, int b) {return (a + b) % P;}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> T;
	int n = N - 3;
	f[1] = f[2] = 0; f[3] = 1;
	s[3] = 1;	
	rep(i, 4, n+1) f[i] = s[i-3], s[i] = add(s[i-1] ,f[i]);
	//rep(i, 1, 20+1) dd(i), de(s[i]);
	rep(cas, 0, T) {
		cin >> n >> x >> y;
		if (x > y) swap(x, y);
		int len = y - x + 1;
		if (x == 1) len++;
		if (y == n) len++;
		cout << s[len] << endl;
	}
	return 0;
}

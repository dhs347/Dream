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
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()
#define endl '\n'
#define pw(x) (1ll<<(x))
typedef long long ll;
typedef pair<int, int> pii;
typedef double db;
typedef vector<int> vi;

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int n, k;
	cin >> n >> k;
	rep(i, 0, pw(n)) {
		int x = i, c = 0;
		while(x) {
			c += (x & 1);
			x >>= 1;
		}
		cout << "AB"[c & 1];
	}
	cout << endl;
	return 0;
}

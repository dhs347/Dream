#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define dd(a) cout << #a << " = " << a << " " 
#define de(a) cout << #a << " = " << a << endl
#define sz(a) (int)a.size()
#define all(a) a.begin(), a.end()
#define pw(a) (1ll << (a))
#define endl "\n"
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef double db;

const int N = 5050;

int n;
int f[N], mex[N];

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	f[0] = f[1] = 0;
	rep(i, 2, N) {
		memset(mex, 0, sizeof(mex));
		for(int x = 0, y = i - 2; x <= y; ++x, --y) mex[f[x] ^ f[y]] = 1;
		for(int j = 0; ; ++j) if(!mex[j]) {
			f[i] = j; break;
		}
	}

	int T;
	cin >> T;
	while(T--) {
		int x; cin >> x;
		cout << (f[x] ? "First" : "Second") << endl;
	}
	return 0;
}

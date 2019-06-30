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

int a[N];

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int c = 0, now = 1;
	rep(i, 2, N) {
		a[i] = now;
		++c;
		if(c == 2) now ^= 1, c = 0;
	}
	int T;
	cin >> T;
	while(T--) {
		int x; cin >> x;
		cout << (a[x] ? "First" : "Second") << endl;
	}
	return 0;
}

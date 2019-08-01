#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define de(x) cout << #x << " = " << x << endl
#define dd(x) cout << #x << " = " << x << " "
#define endl "\n"
#define pw(x) (1ll<<(x))
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()
typedef long long ll;
typedef pair<int, int> pii;
typedef double db;
typedef vector<int> vi;

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int T; cin >> T;
	while(T--) {
		int a[16];
		rep(i, 0, 16) cin >> a[i];
		int t = 0;
		rep(i, 0, 16) if(a[i] == 0) {
			a[i] = 16;
			int x = 3, y = 3;
			t = abs(x - i / 4) + abs(y - i % 4);
		}
		int cnt = 0;
		rep(i, 0, 16) rep(j, i + 1, 16) if(a[i] > a[j]) ++cnt;
		cout << (((cnt & 1) ^ (t & 1)) ? "No" : "Yes") << endl;
	}
	return 0;
}

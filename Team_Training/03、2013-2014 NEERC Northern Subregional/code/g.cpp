#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define sz(a) (int)a.size()
#define de(a) cout << #a << " = " << a << endl
#define dd(a) cout << #a << " = " << a << " "
#define all(a) a.begin(), a.end()
#define pw(x) (1ll << (x))
#define endl '\n'
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

int W, H, w, h, ans1, ans2;

int main() {
	freopen("garage.in", "r", stdin);
	freopen("garage.out", "w", stdout);
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> W >> H >> w >> h;
	rep(i, 1, 100000) {
		if ((2 * i + 1) * w > W) {ans1 = i;break;}
	}
	rep(i, 1, 100000) {
		if ((2 * i + 1) * h > H) {ans2 = i;break;}
	}
	cout << ans1 * ans2;
	return 0;
}

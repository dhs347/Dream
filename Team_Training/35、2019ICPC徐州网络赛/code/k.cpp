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

const int N = 2020;

int n;
pii a[N];
map<pii, int> cnt;

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n;
	rep(i, 1, n + 1) {
		int x, y; cin >> x >> y; x *= 2, y *= 2;
		a[i] = mp(x, y);
	}
	rep(i, 1, n + 1) {
		cnt[a[i]]++;
		rep(j, i + 1, n + 1) cnt[mp((a[i].fi + a[j].fi) / 2, (a[i].se + a[j].se) / 2)] += 2;
	}
	int ans = 0;
	for(auto u : cnt) {
		ans = max(ans, u.se);
	}
	cout << n - ans << endl;
	return 0;
}

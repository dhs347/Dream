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
#define endl '\n'
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()
#define pw(x) (1ll<<(x))
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int N = 303030;

int n, r, sum[N];
priority_queue<pii> que;
vi vec[N];

void init() {
	rep(i, 2 * r, 3e5 + 1) 
		que.push(mp(sum[i - 2 * r] + sum[i - r] + sum[i], i));
}
void upd(int p, int c) {
	sum[p] += c;
	for(int i = p; i < 3e5 + 1 && i - 2 * r <= p; i += r) {
		if(i - 2 * r >= 0) que.push(mp(sum[i - 2 * r] + sum[i - r] + sum[i], i));
	}
}
int qry() {
	while(!que.empty()) {
		auto u = que.top();
		int i = u.se;
		if(sum[i - 2 * r] + sum[i - r] + sum[i] != u.fi) {
			que.pop();
		} else {
			return u.fi;
		}
	}
	return 0;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n >> r;
	rep(i, 1, n + 1) {
		int x, y; cin >> x >> y;
		vec[x].pb(y);
		sum[y]++;
	}
	int ans = 0;
	init();
	rep(i, 2 * r, 3e5 + 1) {
		int res = 0;
		for(auto y : vec[i]) upd(y, -1), ++res;
		for(auto y : vec[i - r]) upd(y, -1), ++res;
		for(auto y : vec[i - 2 * r]) upd(y, -1), ++res;
		ans = max(ans, res + qry());
		for(auto y : vec[i]) upd(y, 1);
		for(auto y : vec[i - r]) upd(y, 1);
		for(auto y : vec[i - 2 * r]) upd(y, 1);
	}
	cout << ans << endl;
	return 0;
}

#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define endl "\n"
#define pw(x) (1ll << (x))
#define all(a) a.begin(), a.end()
#define sz(a) (int)a.size()
#define dd(x) cout << #x << " = " << x << " "
#define de(x) cout << #x << " = " << x << endl
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

int cc;
deque<int> que;
map<int, int> pre, dis;

void gao(int u, int v, int c) {
	int t = dis[u] + c;
	if(!dis.count(v) || dis[v] > t) {
		dis[v] = t;
		c ? que.pb(v) : que.push_front(v);
		if(c) pre[v] = u;
		else {
			while(u != v) {
				if(u % 2 == 0 && u / 2 % v == 0) pre[u >> 1] = u, u >>= 1;
				else pre[u / 3] = u, u /= 3;
			}
		}
	}
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int n; cin >> n;
	dis[n] = 0;
	que.push_back(n);
	while(!que.empty()) {
		int u = que.front(); que.pop_front();
		if(u == 1) break;
		gao(u, u + 1, 1);
		if(u % 2 == 0) gao(u, u / 2, 0);
		if(u % 3 == 0) gao(u, u / 3, 0);
	}
	vi ans;
	int now = 1;
	while(1) {
		ans.pb(now);
		if(now == n) break;
		now = pre[now];
	}
	reverse(all(ans));
	cout << dis[1] << endl;
	rep(i, 0, sz(ans)) cout << ans[i] << " \n"[i == sz(ans) - 1];
	return 0;
}

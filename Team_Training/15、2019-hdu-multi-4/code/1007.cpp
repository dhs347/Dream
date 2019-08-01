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
typedef __int128 ll;
typedef pair<int, int> pii;
typedef double db;
typedef vector<int> vi;

map<ll, int> dis;
int pre[16];

int find(int x) {
	return x == pre[x] ? x : pre[x] = find(pre[x]);
}
void join(int x, int y) {
	x = find(x); y = find(y);
	pre[x] = y;
}

ll get(int a[]) {
	ll ans = 0;
	rep(i, 0, 16) ans = ans * 16 + a[i];
	return ans;
}
void print(int a[]) {
	int 
	return ;
	rep(i, 0, 16) cout << a[i] << " \n"[i == 15];
	cout << endl;
}
void print(ll x) {
	if(x < 0) de("ERR");
}
bool check(int i, int j) {
	if(abs(i - j) == 4) return 1;
	if(i / 4 == j / 4 && abs(i % 4 - j % 4) == 1) return 1;
	return 0;
}
int C = 120;
int main() {
//	std::ios::sync_with_stdio(0);
//	std::cin.tie(0);
	vector<ll> que; 
	int a[16]; rep(i, 0, 16) a[i] = (i + 1) % 16;
	ll u = get(a);
	dis[u] = 0; que.pb(u);
	rep(i, 0, sz(que)) {
		ll u = que[i];
		int D = dis[u];
		de(D);
		if(D >= C) continue;
		int p = 15;
		ll x = u;
		while(p >= 0) {
			a[p] = x % 16;
			x /= 16;
			--p;
		}
		print(a, D);
		rep(j, 0, 16) if(!a[j]) p = j;
		rep(j, 0, 16) if(j != p && check(p, j)) {
			swap(a[p], a[j]);
			ll v = get(a);
			if(!dis.count(v)) {
				dis[v] = D + 1;
				que.pb(v);
			}
			swap(a[p], a[j]);
		}
	}
	int T; cin >> T;
	while(T--) {
		rep(i, 0, 16) cin >> a[i];
		ll u = get(a);
		cout << (dis.count(u) ? "Yes" : "No") << endl;
	}
	return 0;
}

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

const int N = 3e6 + 7;

int n, q, pre[N];
bool vis[N];
pii a[N];
vi V;

int F(int x) {
	return lower_bound(all(V), x) - V.begin() + 1;
}

int find(int x) {
	return x == pre[x] ? x : pre[x] = find(pre[x]);
}
void join(int x, int y) {
	x = find(x), y = find(y);
	pre[x] = y;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n >> q;
	rep(i, 1, q + 1) {
		cin >> a[i].fi >> a[i].se;
		V.pb(a[i].se);
		if(a[i].se + 1 <= n) V.pb(a[i].se + 1);
		if(a[i].se - 1 >= 1) V.pb(a[i].se - 1);
	}
	sort(all(V));
	V.erase(unique(all(V)), V.end());
	rep(i, 1, sz(V) + 1) pre[i] = i;
	rep(i, 1, q + 1) {
		if(a[i].fi == 1) {
			int p = F(a[i].se);
			if(vis[p - 1]) join(p - 1, p);
			if(vis[p + 1]) join(p, p + 1);
			vis[p] = 1;
		} else {
			int t = find(F(a[i].se));
			int ans = V[t - 1] + vis[t];
			if(ans > n) ans = -1;
			cout << ans << endl;
		}
	}
	return 0;
}

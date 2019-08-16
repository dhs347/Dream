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
#define pw(x) (1ll<<(x))
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<int, pii> piii;
typedef double db;
typedef vector<int> vi;

const int N = 4200;


struct node{
	ll w; int sa, sb, ida, idb;
	node (ll w = 0, int sa = 0, int sb = 0, int ida = 0, int idb = 0) :w(w), sa(sa), sb(sb), ida(ida), idb(idb) {}
	bool operator < (const node &b) const {
		return w * b.sa * b.sb > b.w * sa * sb;  
	}
};

int w, siz[N], a[N][N], n, use[N];
string s;
priority_queue<node> q;

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cout << setiosflags(ios::fixed);
	cout << setprecision(10);
	cin >> n;
	rep(i, 1, n+1) {
		cin >> s;
		rep(j, 1, n+1) {
			a[i][j] = s[j - 1] - '0';
			if (i != j) q.push(node(a[i][j], 1, 1, i, j));
		}
	}
	rep(i, 1, n+1) siz[i] = 1;
	while (!q.empty()) {
		auto u = q.top(); q.pop();
		if (use[u.ida] || use[u.idb]) continue;
		cout << u.ida << " " << u.idb << " " << (db)u.w / u.sa / u.sb << endl;
		use[u.ida] = use[u.idb] = 1;
		rep(i, 1, n+1) if (!use[i]) {
			a[n+1][i] = a[u.ida][i] + a[u.idb][i];
			a[i][n+1] = a[n+1][i];
			q.push(node(a[u.ida][i] + a[u.idb][i], siz[u.ida] + siz[u.idb], siz[i], n+1, i));
		}
		siz[++n] = siz[u.ida] + siz[u.idb];
	}
	return 0;
}

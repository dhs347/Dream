#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define mp make_pair
#define pb push_back
#define sz(a) (int)a.size()
#define de(a) cout << #a << " = " << a << endl
#define dd(a) cout << #a << " = " << a << " "
#define all(a) a.begin(), a.end()
#define pw(a) (1ll << (a))
#define endl "\n"
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int N = 26, M = 1010;

int n, m, k;
struct Node {
	char c[N]; int a[N], t[N];
	int num, tim, las, id;
	string nam;
	void calc() {
		num = tim = las = 0;
		rep(i, 0, n) if(c[i] == '+') {
			++num;
			tim += (a[i] - 1) * 20 + t[i];
			las = max(las, t[i]);
		}
	}
	bool operator < (const Node &c) const {
		if(num != c.num) return num > c.num;
		if(tim != c.tim) return tim < c.tim;
		if(las != c.las) return las < c.las;
		return nam < c.nam;
	}
}nd[M], nn[M];
map<string, int> id;
bool vis[M];

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n >> m >> k;
	rep(i, 0, m) {
		cin >> nd[i].nam;
		id[nd[i].nam] = i;
		nd[i].id = i;
		rep(j, 0, n) {
			string o;
			cin >> o >> nd[i].a[j] >> nd[i].t[j];
			nd[i].c[j] = o[0];
		}
		nd[i].calc();
	}
	rep(_, 0, k) {
		string nam; cin >> nam;
		int i = id[nam];
		rep(j, 0, n) {
			string o;
			cin >> o >> nd[i].a[j] >> nd[i].t[j];
			nd[i].c[j] = o[0];
		}
		nd[i].calc();
		vis[i] = 1;
	}
	sort(nd, nd + m);
	int st = m, ed = -1;
	rep(i, 0, m) if(vis[nd[i].id]) st = min(st, i), ed = max(ed, i);
	rep(i, st, ed + 1) if(!vis[nd[i].id]) {
		rep(j, 0, n) if(nd[i].c[j] != '+') {
			nd[i].c[j] = '+';
			nd[i].a[j]++;
			nd[i].t[j] = 240;
		}
		nd[i].calc();
	}
	sort(nd, nd + m);
	st = m, ed = -1;
	rep(i, 0, m) if(vis[nd[i].id]) st = min(st, i), ed = max(ed, i);
	cout << (ed - st + 1 == k ? "Leaked" : "Fake") << endl;
	return 0;
}

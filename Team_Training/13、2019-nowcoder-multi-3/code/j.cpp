#include<bits/stdc++.h>
using namespace std;
#define fi first 
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a) --i)
#define de(c) cout << #c << " = " << c << endl
#define dd(c) cout << #c << " = " << c << " "
#define all(c) c.begin(), c.end()
#define sz(x) (int)x.size()
#define endl '\n'
#define pw(x) (1ll << (x))
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef double db;

const int N = 5e5 + 8;

int n, m, L, R, pos[N], val[N];
set<pii> st;
vector<ll> V;
int F(ll x) { return lower_bound(all(V), x) - V.begin() + 1; }

struct Node {
	int o, val;
	ll x;
}nd[N];

void solve() {
	cin >> n >> m;

	L = 1, R = 0;
	fill_n(pos, n + 1, 0);
	st.clear();
	V.clear();

	rep(i, 1, n + 1) cin >> nd[i].o >> nd[i].x >> nd[i].val, V.pb(nd[i].x);
	sort(all(V)); 
	V.erase(unique(all(V)), V.end());

	rep(i, 1, n + 1) {
		int x = F(nd[i].x);
		if(nd[i].o) {
			auto it = st.find(mp(pos[x], x));
			if(pos[x] && it != st.end()) {
				if(nd[i].val == -1) {
					if(it == st.begin()) cout << "Invalid" << endl;
					else {
						--it;
						cout << val[it -> se] << endl;
					}
				} else if(nd[i].val == 0) {
					cout << val[x] << endl;
				} else {
					++it;
					if(it == st.end()) cout << "Invalid" << endl;
					else cout << val[it -> se] << endl;
				}
			} else {
				cout << "Invalid" << endl;
			}
		} else {
			auto it = st.find(mp(pos[x], x));
			if(pos[x] && it != st.end()) {
				cout << val[x] << endl;
				st.erase(it);
				st.insert(mp(++R, x));
				pos[x] = R;
			} else {
				cout << nd[i].val << endl;
				pos[x] = ++R;
				st.insert(mp(R, x));
				val[x] = nd[i].val;
				while(sz(st) > m) st.erase(st.begin());
			}
		}
	}
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int T; cin >> T;
	while(T--) solve();
	return 0;
}

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

int n, k, x;
map<int, int> M;

void upd1(pii t, int k) {
	int x = t.se - k % t.se, y = k / t.se;
	M.erase(t.fi);
	M[t.fi + y] += x;
	if (t.se - x) M[t.fi + y + 1] += t.se - x;
}

void upd2(pii t, int k) {
	int x = t.se - k % t.se, y = k / t.se;
	M.erase(t.fi);
	M[t.fi - y] += x;
	if (t.se - x) M[t.fi - y - 1] += t.se - x;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	while (cin >> n >> k) {
		M.clear();
		rep(i, 1, n+1) {
			cin >> x;
			M[x]++;
		}
		if (sz(M) == 1) {
			cout << 0 << endl;
			continue;
		}
		while (sz(M) > 2 && k > 0) {
			auto t1 = *M.begin(), t2 = *(++M.begin()), t3 = *(--M.end()), t4 = *(--(--M.end()));
			ll k1 = 1ll * (t2.fi - t1.fi) * t1.se;
			ll k2 = 1ll * (t3.fi - t4.fi) * t3.se;
			if (k <= k1 && k <= k2) {
				upd1(t1, k);
				upd2(t3, k);
			}else if (k1 < k2) {
				upd1(t1, k1), upd2(t3, k1), k -= k1;
			}else upd1(t1, k2), upd2(t3, k2), k -= k2;
		}
		if (k == 0) {
			auto t1 = *M.begin(), t2 = *(++M.begin()), t3 = *(--M.end()), t4 = *(--(--M.end()));
			cout << t3.fi - t1.fi << endl;
		}else {	
			auto t1 = *M.begin(), t2 = *(++M.begin()), t3 = *(--M.end()), t4 = *(--(--M.end()));
			ll xx = t3.fi - k / t3.se;
			ll yy = t1.fi + k / t1.se;
			if (xx - yy <= 1) cout << 1 << endl;
			else cout << xx - yy << endl;
		}
	}
	return 0;
}

#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define de(x) cout << #x << " = " << x << endl
#define dd(x) cout << #x << " = " << x << " " 
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define endl '\n'
#define pw(x) (1ll <<(x))
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int N = 1e6 + 7;

int n;
int pre[N][55], pp[55], tt[55];
pii a[N];

int main() {
	freopen("sticks.in", "r", stdin);
	freopen("sticks.out", "w", stdout);
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);


	int m; cin >> m;
	rep(i, 1, m + 1) {
		int k; cin >> k;
		rep(j, 1, k + 1) {
			int x; cin >> x;
			a[++n] = mp(x, i);
		}
	}
	sort(a + 1, a + 1 + n);
	rep(i, 1, n + 1) {
		int ma = 0, ma2 = 0;
		rep(j, 1, m + 1) if(j != a[i].se && pp[j]) {
			if(pp[j] > pp[ma]) {
				ma2 = ma;
				ma = j;
			} else if(pp[j] > pp[ma2]) {
				ma2 = j;
			}
		}
		if(ma && ma2 && pp[ma] + pp[ma2] > a[i].fi) {
			cout << ma << " " << pp[ma] << " ";
			cout << ma2 << " " << pp[ma2] << " ";
			cout << a[i].se << " " << a[i].fi << endl;
			return 0;
		}
		pp[a[i].se] = a[i].fi;
	}
	cout << "NIE" << endl;
	return 0;
}

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

const int N = 1e6 + 7;

int n, k, to[4];
pii a[N];

bool cmp(pii a, pii b) {
	int arr[] = {0, 1, 2, 3, 4};
	per(i, 1, k + 1) {
		int a1 = a.fi >> (i - 1);
		int b1 = a.se >> (i - 1);
		int a2 = b.fi >> (i - 1);
		int b2 = b.se >> (i - 1);
		int x = a1 << 1 | b1, y = a2 << 1 | b2;
		if(x == y) {
			int inf = pw(i - 1) - 1;
			a.fi &= inf;
			a.se &= inf;
			b.fi &= inf;
			b.se &= inf;
			if(arr[to[x]] == 1) swap(arr[2], arr[4]);
			if(arr[to[x]] == 4) swap(arr[1], arr[3]);//, swap(arr[2], arr[4]);
		} else {
			return arr[to[x]] < arr[to[y]];
		}
	}
	return 0;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	to[0] = 1, to[2] = 2, to[3] = 3, to[1] = 4;
	cin >> n >> k;
	rep(i, 1, n + 1) cin >> a[i].fi >> a[i].se, --a[i].fi, --a[i].se;
	sort(a + 1, a + 1 + n, cmp);
	rep(i, 1, n + 1) cout << a[i].fi + 1 << " " << a[i].se + 1 << endl;
	return 0;
}

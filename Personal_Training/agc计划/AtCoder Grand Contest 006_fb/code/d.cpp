#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse2")
#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define rep(i, a, b) for(int i=(a); i<(b); i++)
#define per(i, a, b) for(int i=(b)-1; i>=(a); i--)
#define sz(a) (int)a.size()
#define de(a) cout << #a << " = " << a << endl
#define dd(a) cout << #a << " = " << a << " "
#define all(a) a.begin(), a.end()
#define pw(x) (1ll<<(x))
#define endl "\n"
typedef double db;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int N = 3e5 + 7;
const int P = 1e9 + 7;

int a[N], b[N], n, ok, l, r, mid, ans;

bool check(int mid) {
	rep(i, 1, n*2) if (a[i] >= mid) b[i] = 1;else b[i] = 0;
	int t1 = 0, t2 = 0;
	b[0] = b[1];
	b[n*2] = b[n*2-1];
	rep(i, n+1, n*2+1) {
		t1++;
		if (b[i] != (b[n] ^ (t1 & 1))) break;
	}
	per(i, 0, n) {
		t2++;
		if (b[i] != (b[n] ^ (t2 & 1))) break;
	}
	if (t1 < t2) return b[n + t1 - 1];else return b[n - t2 + 1];
}

int main(){
	freopen("a.in", "r", stdin);
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n;
	//n = 10000;
	rep(i, 1, n*2) cin >> a[i];
	//rep(i, 1, n * 2) a[i] = i;
	//random_shuffle(a+1, a+n*2);
	l = 1; r = n * 2 - 1; ans = 0;
	while (l <= r) {
		mid = l + r >> 1;
		if (check(mid)) ans = mid, l = mid + 1;
		else r = mid - 1;
	} 
	cout << ans;
	return 0;
}

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
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef long long ll;

const int N = 1e6 + 3;

int a[N], sta[N], st = 1, ed = 0;

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int n, k; cin >> n >> k;
	rep(i, 1, n + 1) cin >> a[i];
	int p = 1;
	rep(i, 1, n + 1) {
		while(p <= n && p <= i + k - 1) {
			while(st <= ed && a[sta[ed]] > a[p]) --ed;
			sta[++ed] = p++;
		}
		while(st <= ed && sta[st] < i + 1) ++st;
		if(st <= ed && a[sta[st]] < a[i]) {
			int l = i, r = min(n, i + k - 1);
			sort(a + l, a + r + 1); break;
		}
	}
	rep(i, 1, n + 1) cout << a[i] << " \n"[i == n];
	return 0;
}

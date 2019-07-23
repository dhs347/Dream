#include<bits/stdc++.h>
using namespace std;
#define fi first 
#define se second
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define mp make_pair
#define pb push_back
#define de(x) cout << #x << " = " << x << endl
#define dd(x) cout << #x << " = " << x << " "
#define endl '\n'
#define all(a) a.begin(), a.end()
#define sz(a) (int)a.size()
#define pw(x) (1ll << (x))
typedef long long ll;
typedef pair<int, int> pii;
typedef double db;
typedef vector<int> vi;

const int N = 101010;

int n;
int l[N], s[N], v[N];
ll pre[N];

int main() {
	while(~scanf("%d", &n)) {
		rep(i, 0, n + 1) scanf("%d", l + i);
		rep(i, 0, n + 1) scanf("%d", s + i);
		rep(i, 0, n + 1) scanf("%d", v + i);
		rep(i, 1, n + 1) pre[i] = pre[i - 1] + l[i];
		db ans = s[0] * 1. / v[0];
		rep(i, 1, n + 1) {
			ans = max(ans, (pre[i] + s[i]) * 1. / v[i]);
		}
		printf("%.8f\n", ans);
	}
	return 0;
}

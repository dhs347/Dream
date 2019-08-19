#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
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
typedef vector<int> vi;
typedef pair<int, int> pii;
typedef uniform_int_distribution<ll> RR;

const int N = 1e5 + 7;
const int inf = 460;

int n, f[N], a[N], ans, ma, x;

int lis(int n, int a[]) {
	memset(f, 0x3f, sizeof(f));
	rep(i, 1, n + 1) {
		auto p = lower_bound(f + 1, f + 1 + n, a[i]) - f;
		f[p] = a[i];
	}
	return lower_bound(f + 1, f + 1 + n, f[N - 1]) - f - 1;
}

int pos;
void print(int c) {
	if(c) ma = x, ++ans;
	printf("%d\n", c);
	fflush(stdout);
}

ll rnd(ll l, ll r) {
	mt19937 gen(rand());
	RR dis(l, r);
	return dis(gen);
}
int main() {
	srand(time(0));
	/*rep(tim, 0, 1000) {
	n = 1e5;
	rep(i, 1, n + 1) a[i] = i;
	random_shuffle(a + 1, a + 1 + n);
	int cc = lis(n, a);
	*/
	scanf("%d", &n);
	rep(i, 1, n + 1) {
		//x = a[i];
		scanf("%d", &x);
		if(x <= ma) {
			print(0);
			continue;
		}
		int t = inf;
		t = ((x - ma) + t - 1) / t;
		//if(t == 0) t = 1;
		print(t == 1);
	}
	//de(cc);
	//assert(1.0 * ans / cc > 0.65);
	//}
	return 0;
}

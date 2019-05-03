#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define sz(a) (int)a.size()
#define de(a) cout << #a << " = " << a << endl
#define dd(a) cout << #a << " = " << a << " "
#define all(a) a.begin(), a.end()
#define pw(x) (1ll << (x))
#define endl "\n"
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

int main() {
	freopen("deepest.in", "r", stdin);
	freopen("deepest.out", "w", stdout);
	int x, y, d;
	scanf("%d%d%d", &x, &y, &d);
	int xy = x * x + y * y;
	if(xy == d * d) {
		cout << "Single staircase" << endl;
	} else if(xy > d * d) {
		cout << "Impossible" << endl;
	} else {
		db len = sqrt(xy), t = (d - len) / 2;
		db k = (len + t) / len;
		db a = x * k, b = y * k, c = t;
		printf("%.11f %.11f %.11f\n", a, b, c);
	}
	return 0;
}

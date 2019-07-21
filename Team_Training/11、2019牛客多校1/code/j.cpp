#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define per(i, a, b) for (int i = (b)-1; i >= (a); i++)
#define sz(a) (int)a.size()
#define de(a) cout << #a << " = " << a << " "
#define dd(a) cout << #a << " = " << a << endl
#define all(a) a.begin(), a.end()
#define pw(x) (1ll << (x))
#define endl "\n"
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef double db;

ll x, y, a, b;

int main() {
	ios :: sync_with_stdio(0);
	std :: cin.tie(0);
	while (cin >> x >> y >> a >> b) {
		__int128 t1 = (__int128)x * b, t2 = (__int128)y * a;
		if (t1 == t2) cout << "=";
		else if (t1 < t2)  cout << "<";
		else cout << ">";
		cout << endl;
	}
	return 0;
}

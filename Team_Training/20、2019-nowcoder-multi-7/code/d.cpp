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
#define all(x) x.begin(), x.end()
#define pw(x) (1ll<<(x))
#define sz(x) (int)x.size()
typedef long long ll;
typedef pair<int, int> pii;
typedef double db;
typedef vector<int> vi;
int n, p, a[2000000], m;
int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n >> p;
	while (p > 0) {
		a[++m] = p % 10;
		p /= 10;
	}
	if (m > n) {
		cout << "T_T" << endl;
	}else {
		reverse(a+1, a+m+1);
		rep(i, 1, n+1) cout << a[i];
		cout << endl;
	}
	return 0;
}

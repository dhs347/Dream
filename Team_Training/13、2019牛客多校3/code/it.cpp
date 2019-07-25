#include<bits/stdc++.h>
using namespace std;
#define fi first 
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a) --i)
#define de(c) cout << #c << " = " << c << endl
#define dd(c) cout << #c << " = " << c << " "
#define all(c) c.begin(), c.end()
#define sz(x) (int)x.size()
#define endl '\n'
#define pw(x) (1ll << (x))
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef double db;

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int n = 5;
	int a[11];
	rep(i, 1, n + 1) a[i] = i;
	do {
		rep(i, 1, n + 1) cout << a[i] << " \n"[0];
		cout << ' ';
		rep(i, 3, n + 1) {
			int b[] = {a[i - 2], a[i - 1], a[i]};
			sort(b, b + 3);
			cout << b[1] << " \n"[i == n];
		}
	} while(next_permutation(a + 1, a + 1 + n));
	return 0;
}

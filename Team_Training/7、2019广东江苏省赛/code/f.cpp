#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define endl "\n"
#define pw(x) (1ll << (x))
#define all(x) x.begin(), x.end()
#define sz(a) (int)a.size()
#define de(x) cout << #x << " = " << x << endl
#define dd(x) cout << #x << " = " << x << " "
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int N = 2e5 + 7;
int n, f[N];

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int k = 3;
	n = 30;
	rep(i, 1, n+1) f[i] = 1;
	rep(t, 2, k+1) {
		per(i, 1, n+1) 
			per(j, 1, i) if (i % j == 0) f[i] += f[j];
	}
	rep(i, 1, n+1) dd(i), cout << f[i] << endl;
	return 0;
}

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
typedef long long ll;
typedef long double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int N = 1e6 + 5;

int n, l, m;
db f[N];

int main() {
	freopen("intset.in", "r", stdin);
	freopen("intset.out", "w", stdout);
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n >> l >> m;
	cout << l * 1ll * m / n << endl;
	return 0;
}

#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define mp make_pair
#define pb push_back
#define sz(a) (int)a.size()
#define de(a) cout << #a << " = " << a << endl
#define dd(a) cout << #a << " = " << a << " "
#define all(a) a.begin(), a.end()
#define pw(a) (1ll << (a))
#define endl "\n"
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int N = 2020;

int n, k;
int a[N][N], sum[N];

bool solve() {
	rep(i, 1, n + 1) if(sum[i] % 2 == 0) return 0;
	return 1;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n >> k;
	rep(i, 1, n + 1) rep(j, 1, k + 1) cin >> a[i][j], sum[i] += a[i][j];
	cout << (solve() ? "Yes" : "No") << endl;
	return 0;
}

#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define de(x) cout << #x << " = " << x << endl
#define dd(x) cout << #x << " = " << x << " " 
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define endl '\n'
#define pw(x) (1ll <<(x))
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int N = 3e3 + 6;
int n, m, u, v, col[N];
bool g[N][N];

int main() {
	freopen("party.in", "r", stdin);
	freopen("party.out", "w", stdout);
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n >> m;
	rep(i, 1, m+1) {
		cin >> u >> v;
		g[u][v] = g[v][u] = 1;
	}
	rep(i, 1, n+1) if (!col[i])
		rep(j, i+1, n+1) if (!col[j] && !g[i][j]) {
			col[i] = 1;
			col[j] = 1;
			break;
		}
	int m = n / 3;
	rep(i, 1, n+1) if (!col[i]) {
		m--;
		cout << i << " \n"[m == 0];
		if (m == 0) break;
	}
	return 0;
}

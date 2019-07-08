#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define sz(a) (int)a.size()
#define all(a) a.begin(), a.end()
#define pw(x) (1ll <<(x))
#define endl "\n"
#define de(a) cout << #a << " = " << a << endl
#define dd(a) cout << #a << " = " << a << " "
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef double db;

void solve(int n) {
	while(1) {
		if(n % 7 == 0 && n % 4) {
			cout << n << endl;
			return ;
		}
		n++;
	}
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int T;
	cin >> T;
	while(T--) {
		int n; cin >> n;
		solve(n);
	}
	return 0;
}

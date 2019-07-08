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

const int N = 202020;

int n;
string s;
int pre[5];

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	while(cin >> n >> s) {
		memset(pre, 0, sizeof(pre));
		rep(i, 0, n) {
			if(s[i] == 'x') {
				pre[0]++;
			} else if(s[i] == 't' && pre[0]) {
				--pre[0], ++pre[1];
			} else if(s[i] == 'C' && pre[1]) {
				--pre[1], ++pre[2];
			} else if(s[i] == 'p' && pre[2]) {
				--pre[2], ++pre[3];
			} else if(s[i] == 'c' && pre[3]) {
				--pre[3], ++pre[4];
			}
		}
		cout << pre[4] << endl;
	}
	return 0;
}

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

const int N = 5050, P = 1e9 + 7;

int n;
int in[N], ans[N], pw[N];
string s;

void solve(int l, int r) {
	rep(i, l, r + 1) {
		if(s[i] == '<') {
			rep(j, l, i) ++in[j];
		} else {
			rep(j, i + 1, r + 1) ++in[j];
		}
	}
	in[l] = in[r] = 1;
}

int add(int a, int b) {
	if((a += b) >= P) a -= P;
	return a;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	pw[0] = 1;
	rep(i, 1, N) pw[i] = pw[i - 1] * 2 % P;
	cin >> s;
	n = sz(s);
	bool all = true;
	rep(i, 1, n) if(s[i] != s[0]) all = false;
	if(s[0] == '<' && s[n - 1] == '>') {
	} else if(s[0] == '<') {
		if(all) ans[0] = 1;
		else {
			rep(i, 0, n) if(s[i] != '<') {
				solve(i, n - 1);
				rep(j, i, n) if(s[j] == '<') ans[0] = add(ans[0], pw[in[j] - 1]);
				break;
			}
		}
	} else if(s[n - 1] == '>') {
		if(all) ans[n - 1] = 1;
		else {
			per(i, 0, n) if(s[i] != '>') {
				solve(0, i);
				rep(j, 0, i + 1) if(s[j] == '>') ans[n - 1] = add(ans[n - 1], pw[in[j] - 1]);
				break;
			}
		}
	} else {
		solve(0, n - 1);
		rep(i, 0, n) ans[i] = pw[in[i] - 1];
	}
	rep(i, 0, n) cout << ans[i] << " \n"[i == n - 1];
	return 0;
}

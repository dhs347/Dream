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
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef long long ll;

const int N = 3e4 + 7;
int ans, n, vis[N], sg[N], a[N];
vi tmp;
string s;
int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> s;
	n = sz(s);
	rep(i, 0, n) {
		//rep(j, 0, i+1) a[j] = 0;
		tmp.pb(0); vis[0] = 1;
		for (int d = 1; i - d >= 0; d++) {
			int t = 0;
			for (int j = i - d; j >= 0; j -= d) {
				t ^= sg[j];
				vis[t] = 1; tmp.pb(t);
			}
		}
		rep(j, 0, 10000) {
			if (!vis[j]) {
				sg[i] = j; break;
			} 
		}
		for (auto u : tmp) vis[u] = 0; tmp.clear();
	}
	//rep(i, 0, n) de(sg[i]);
	reverse(all(s));
	rep(i, 0, n) if (s[i] == 'N'){
		ans ^= sg[i];
	}
	if (ans == 0) {
		cout << "NIE" << endl;
		return 0;
	}
	rep(i, 0, n) a[i] = s[i] == 'N';
	rep(i, 0, n) if (a[i] == 1) {
		a[i] = 0; 
		if ((ans ^ sg[i]) == 0) {
			per(i, 0, n) cout << "SN"[a[i]];
			cout << endl;
			return 0;
		}
		for (int d = 1; i - d >= 0; d++) {
			int t = ans ^ sg[i]; 
			for (int j = i - d; j >= 0; j -= d) {
				t ^= sg[j]; a[j] ^= 1;
				if (t == 0) {
					per(i, 0, n) cout << "SN"[a[i]];
					cout << endl;
					return 0;
				}
			}
			for (int j = i - d; j >= 0; j -= d) a[j] ^= 1;
		}
		a[i] = 1;
	}
	return 0;
}

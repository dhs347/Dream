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
#define all(a) a.begin(), a.end()
#define sz(a) (int)a.size()
#define dd(x) cout << #x << " = " << x << " "
#define de(x) cout << #x << " = " << x << endl
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

void tes() {
	int n = 1e9, cnt = 0;
	while(1) {
		++cnt;
		if(n == 1) break;
		n = max(n / 2, n - n / 2 - 1);
	}
	de(cnt);
}

void print(int x) {
	char s[] = "<=>";
	cout << s[x] << endl;
	fflush(stdout);
}

int main() {
//	tes();
	int l = 1, r = 1e9;
	int cnt = 0;
	while(cnt < 100) {
		++cnt;
		int x; cin >> x;
		if(x < l) print(2);
		else if(x > r) print(0);
		else if(l == r) {
			print(1);
			break;
		} else if(x - l < r - x) {
			print(2);
			l = x + 1;
		} else {
			print(0);
			r = x - 1;
		}
	}
	return 0;
}

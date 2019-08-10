#include<bits/stdc++.h>
using namespace std;
#define fi first 
#define se second
#define mp make_pair
#define pb push_back
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define de(x) cout << #x << " = " << x << endl
#define dd(x) cout << #x << " = " << x << " "
#define endl '\n'
#define pw(x) (1ll<<(x))
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()
typedef long long ll;
typedef double db;
typedef vector<int> vi;
typedef pair<int, int> pii;

const int N = 101010;

char s[N], sta[N];
int top, ans;;

void gao() {
	if(top < 3) return ;
	if(sta[top] == sta[top - 1] && sta[top] == sta[top - 2]) top -= 3, ++ans;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> s;
	int n = strlen(s);
	rep(i, 0, n) {
		sta[++top] = s[i];
		gao();
	}
	cout << ans << endl;
	return 0;
}

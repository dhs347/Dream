#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define pb push_back
#define mp make_pair
#define de(x) cout << #x << " = " << x << endl
#define dd(x) cout << #x << " = " << x << " "
#define endl "\n"
#define pw(x) (1ll<<(x))
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()
typedef long long ll;
typedef pair<int, int> pii;
typedef double db;
typedef vector<int> vi;

const int N = 101010;

ll ans;

// [0,p) , 0(even) and 1(odd) is virtual , init!!
struct Palindromic_Tree {
	static const int N = ::N , M = 26;
	int ne[N][M] , fail[N] , len[N] , S[N] , last , n , p, cnt[N], las[N], col[N]; ll res;
	int newnode(int l){
		fill(ne[p] , ne[p] + M , 0);
		len[p] = l;
		las[p] = n;
		cnt[p] = 0;
		return p++;
	}
	void ini(){
		p = 0;newnode(0);newnode(-1);
		S[n = last = 0] = -1;
		fail[0] = 1;
	}
	int get_fail(int x){
		while(S[n - len[x] - 1] != S[n]) x = fail[x];
		return x;
	}
	void add(int c){
		S[++n] = c;
		int cur = get_fail(last);
		if(!ne[cur][c]){
			int now = newnode(len[cur] + 2);
			fail[now] = ne[get_fail(fail[cur])][c];
			ne[cur][c] = now;
		}
		last = ne[cur][c];
		cnt[last]++;
	}
	void build() {
		for(int i = p - 1; ~i; --i) cnt[fail[i]] += cnt[i];
	}
	void dfs(int u) {
		int t = u; vi sta;
		while(!col[t] && t > 1) col[t] = 1, ++res, sta.pb(t), t = fail[t];
		if(u > 1) ans += res - 1;
		rep(i, 0, M) if(ne[u][i]) dfs(ne[u][i]);
		for(auto t : sta) col[t] = 0, --res;
	}
}pam;

string s;

void solve() {
	cin >> s;
	pam.ini();
	for(auto c : s) pam.add(c - 'a');
	ans = 0;
	pam.dfs(0);
	pam.dfs(1);
	cout << ans << endl;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int T; cin >> T;
	rep(i, 1, T + 1) cout << "Case #" << i << ": ", solve();
	return 0;
}

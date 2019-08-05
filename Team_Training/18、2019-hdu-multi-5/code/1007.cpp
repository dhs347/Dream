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
#define pw(x) (1ll<<(x))
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()
#define endl "\n"
typedef long long ll;
typedef pair<int, int> pii;
typedef double db;
typedef vector<int> vi;

const int N = 1e5 + 8, P = 998244353;
int f[N], s[N];
int add(int a, int b) {return (a + b) % P;} 

void table(int n) {
	int a[22];
	rep(i, 1, n + 1) a[i] = i;
	map<pii, int> cnt;
	int sum = 0;
	do {
		bool ok = 1;
		rep(i, 2, n + 1) if(abs(a[i] - a[i - 1]) > 2) {
			ok = 0; break;
		}
		if(!ok) continue;
		cnt[mp(a[1], a[n])]++;
		++sum;
	} while(next_permutation(a + 1, a + 1 + n));
	dd(n), de(sum);
	vector<pii> vec;
	int cc = 0;
	for(auto u : cnt) {
		int t = 1 + abs(u.fi.fi - u.fi.se);
		bool ok = 0;
		if (u.fi.fi == 1) t++;
		if (u.fi.se == n) t++;
		if(u.fi.fi < u.fi.se) assert(s[t] == u.se);
	//	if (t == n) assert(s[t + 2] == u.se);
		//rep(i, t, t+3) if (s[i] == u.se) ok =  1;
		/*if (t == n) t += 2;
		else t += (n & 1) ^ (t & 1) ^ 1;
		assert(s[t] == u.se);
		*/
		if (u.fi.fi < u.fi.se && s[t] != u.se) {
			dd(u.fi.fi), dd(u.fi.se), de(n);
			cc++;
		}
		//if (s)
		//*/
		//assert(s[t] == u.se);
		//if (t % 2 == 0) if (s[t] == u.se) ok = 1;
		//if (t & 1) if (s[t + 1] == u.se) ok = 1;
		//if (t & 1) assert(ok == 1);
		//if (t % 2 == 0) assert(ok == 1);
		//vec.pb(mp(t, u.se));  
//		dd(t);
		//dd(u.fi.fi), dd(u.fi.se), '
//		de(u.se);
	}
	//sort(all(vec));
	//for(auto u : vec) dd(u.fi + 1), de(u.se);
//	for(auto u : cnt) if(u.se > 1) cout << u.se << " "; cout << endl;
	de(cc);
	cout << endl;
}

void table() {
	rep(n, 2, 22) table(n);
}

int main() {
//	std::ios::sync_with_stdio(0);
//	std::cin.tie(0);
	f[1] = f[2] = 0; f[3] = 1; s[3] = 1;
	rep(i, 4, N - 3+1) f[i] = s[i-3], s[i] = add(s[i-1], f[i]);
	table();
	return 0;
}

#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); i++)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define de(x) cout << #x << " = " << x << endl
#define dd(x) cout << #x << " = " << x << " " 
#define endl '\n'
#define pw(x) (1ll<<(x))
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;


const int N = 101010;

char s[N], t[N];
int ns[N], nt[N];

void kmp(char *s, int *ns, char *t, int *nt) {
	int lens = strlen(s);
	int lent = strlen(t);
	nt[0] = -1;
	for(int i = 0, j = -1; i < lens; ++i) {
		while(j >= 0 && s[i] != t[j + 1]) j = nt[j];
		if(s[i] == t[j + 1]) ++j;
		ns[i] = j;
		if(j + 1 == lent) j = nt[j];
	}
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int q;
	cin >> s >> q;
	int lens = strlen(s);
	while(q--) {
		cin >> t;
		int lent = strlen(t);
		if(strlen(s) < strlen(t)) {
			kmp(s + 1, nt + 1, s, nt);
			kmp(t, ns, s, nt);
			bool ans = 0;
			rep(i, 0, lent) if(ns[i] == lens - 1) ans = 1;
			if(ans) cout << "my teacher!" << endl;
			else cout << "senior!" << endl;
		} else if(strlen(s) > strlen(t)) {
			kmp(t + 1, nt + 1, t, nt);
			kmp(s, ns, t, nt);
			bool ans = 0;
			rep(i, 0, lens) if(ns[i] == lent - 1) ans = 1;
			if(ans) cout << "my child!" << endl;
			else cout << "oh, child!" << endl;
		} else {
			kmp(t + 1, nt + 1, t, nt);
			kmp(s, ns, t, nt);
			bool ans = 0;
			rep(i, 0, lens) if(ns[i] == lent - 1) ans = 1;
			if(ans) cout << "jntm!" << endl;
			else cout << "friend!" << endl;
		}
	}
	return 0;
}

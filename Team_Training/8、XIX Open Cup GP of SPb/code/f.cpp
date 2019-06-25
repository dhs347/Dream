#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) -1; i >= (a); --i)
#define endl "\n"
#define pw(a) (1ll << (a))
#define all(a) a.begin(), a.end()
#define sz(a) (int)a.size()
#define de(x) cout << #x << " = " << x << endl
#define dd(x) cout << #x << " = " << x << " "
typedef long long ll;
typedef pair<int, int> pii;
typedef double db;
typedef vector<int> vi;

const int N = 101010;

int n, k;
int a[N], b[N], na[N], nb[N];
multiset<int> st;

void kmp(int *s, int *ns, int *t, int *nt, int lens, int lent) {
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
	cin >> n >> k;
	k = n - k + 1;
	rep(i, 1, n + 1) cin >> a[i];
	int l = 1, r = k;
	rep(i, 1, k + 1) st.insert(a[i]);
	rep(i, 1, n - k + 2) {
		b[i] = *st.rbegin();
		st.erase(st.find(a[l]));
		st.insert(a[r + 1]);
		++l, ++r;
	}
	kmp(b + 2, nb + 1, b + 1, nb, n - k, n - k + 1);
	kmp(a + 1, na, b + 1, nb, n, n - k + 1);
	int ans = -1;
	rep(i, 0, n) if(na[i] == n - k) ans = i - (n - k + 1) + 2;
	cout << ans << endl;
	return 0;
}

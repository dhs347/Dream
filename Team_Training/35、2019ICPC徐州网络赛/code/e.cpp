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

const int N = 505050;

#define ls rt << 1
#define rs ls | 1
int n, m, a[N], ans[N];
vi V;

int F(int x) {
	return lower_bound(all(V), x) - V.begin() + 1;
}
int ma[N << 2];
void upd(int p, int c, int l = 1, int r = sz(V), int rt = 1) {
	ma[rt] = max(ma[rt], c);
	if(l == r) return ;
	int mid = l + r >> 1;
	if(p <= mid) upd(p, c, l, mid, ls);
	else upd(p, c, mid + 1, r, rs);
}
int qry(int L, int R, int l = 1, int r = sz(V), int rt = 1) {
	if(L <= l && r <= R) return ma[rt];
	int mid = l + r >> 1, ans = 0;
	if(L <= mid) ans = max(ans, qry(L, R, l, mid, ls));
	if(R > mid) ans = max(ans, qry(L, R, mid + 1, r, rs));
	return ans;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n >> m;
	rep(i, 1, n + 1) cin >> a[i], V.pb(a[i]);
	sort(all(V));
	V.erase(unique(all(V)), V.end());
	per(i, 1, n + 1) {
		int l = F(a[i] + m), r = sz(V);
		int j = qry(l, r);
		if(j) ans[i] = j - i - 1;
		else ans[i] = -1;
		upd(F(a[i]), i);
	}
	rep(i, 1, n + 1) cout << ans[i] << " \n"[i == n];
	return 0;
}

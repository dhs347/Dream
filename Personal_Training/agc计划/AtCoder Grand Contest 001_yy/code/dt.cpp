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

int C = 20, N = 20;

int a[10101010], b[10101010], na, nb;

void gen(int a[], int &n) {
	int tot = N; n = 0;
	while(tot) {
		a[++n] = min(rand() % C + 1, tot);
		tot -= a[n];
	}
}
int pre[10101010];
int find(int x) {
	return pre[x] == x ? x : pre[x] = find(pre[x]);
}
void print(int a[], int &n) {
	cout << n << " ";
	rep(i, 1, n + 1) cout << a[i] << " \n"[i == n];
}
void join(int x, int y) {
	x = find(x), y = find(y);
	pre[x] = y;
}
void gao(int l, int r) {
	for(int i = l, j = r; i < j; ++i, --j) join(i, j);
}
void check() {
	rep(i, 1, N + 1) pre[i] = i;
	int sum = 0;
	rep(i, 1, na + 1) {
		gao(sum + 1, sum + a[i]);
		sum += a[i];
	}
	sum = 0;
	rep(i, 1, nb + 1) {
		gao(sum + 1, sum + b[i]);
		sum += b[i];
	}
	bool ok = 1;
	rep(i, 1, N + 1) if(find(i) != find(1)) return ;
	if(na > 10) {
		print(a, na);
		print(b, nb);
		cout << ok << endl << endl;
	}
}

int main() {
	//std::ios::sync_with_stdio(0);
	//std::cin.tie(0);
	while(1) {
		gen(a, na);
		gen(b, nb);
		check();
	}
	return 0;
}

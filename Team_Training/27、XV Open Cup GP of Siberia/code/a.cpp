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
typedef long long ll;
typedef pair<int, int> pii;
typedef double db;
typedef vector<int> vi;

const int N = 3000, inf = 1e9;

int k, n, m;
int num[1010], pen[1010];
int tmp[1010][11];
int f[11][11][N + 7];
pii pre[11][11][N + 7]; // zuihou nati fashi
int isac[1010][11];
vi ac[1010];
bool inq[11][11][1010];

struct P {
	int num, pen, id, las;
	P(int a = 0, int b = 0, int c = 0, int d = 0) : num(a), pen(b), id(c), las(d) {}
	bool operator < (const P &c) const {
		if(num != c.num) return num < c.num;
		if(pen != c.pen) return pen > c.pen;
		return id > c.id;
	}
};

set<P> A;
set<P> B;

void print() {
	cout << "Champions" << endl;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> k >> n >> m;
	rep(i, 1, m + 1) {
		int t, a, p; string r;
		cin >> t >> a >> p >> r;
		if(isac[a][p]) continue;
		if(r[0] == 'A') {
			isac[a][p] = t;
			if(t >= 240) {
				ac[a].pb(p);
			} else {
				num[a]++;
				pen[a] += tmp[a][p] + t;
			}
		} else {
			tmp[a][p] += 20;
		}
	}
	rep(i, 2, n + 1) reverse(all(ac[i]));
	rep(i, 0, 11) rep(j, 0, 11) rep(k, 0, N + 7) f[i][j][k] = -inf;
	f[num[1]][0][pen[1]] = 0; 
	B.insert(P(num[1], pen[1], 1, 0));
	inq[1][0][pen[1]] = 1;
	rep(i, 2, n + 1) A.insert(P(num[i], pen[i], i));
	while(1) {
		if(sz(A) == 0) {
			print();
			break;
		}
		if(sz(B) == 0) {
			cout << "Losers" << endl;
			break;
		}
		auto a = A.begin();
		auto b = B.begin();
		if(*a < *b) {
			int i = a->id;
			A.erase(a);
			if(sz(ac[i])) {
				int j = ac[i].back(); ac[i].pop_back();
				num[i]++;
				pen[i] += tmp[i][j] + isac[i][j];
				A.insert(P(num[i], pen[i], i));
			}
		} else {
			int i = b->num, j = b->las, p = b->pen;
			rep(i, 1, k + 1) if(!isac[1][i]) {
				for(int j = tmp[1][i] + 240; ; ++j) {
					int t = j + p, c = min(t, N - 1);
					P tt = P(i + 1, c, 1);
				}
			}
		}
	}
	return 0;
}

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
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int N = 1e5 + 7;

int px, py, pz;
int m, p1, p2, pos, n, k, b[10][N], pp[N];
ll sum, ans;
unsigned short c[N];

inline void add(int p) {
	if (p <= 0) return;
	for(; p <= n; p += p & (-p)) c[p]++;
}

inline void del(int p) {
	if (p <= 0) return;
	for(; p <= n; p += p & (-p)) if (c[p]) c[p] = 0;else break;
}

inline int qry(int p) {
	int r = 0;
	for(; p > 0; p -= p & (-p)) r += c[p];
	return r;
}

struct node{
	unsigned short x, y, z;	
} a[N], tmp[N];

inline bool cmp(const node &a, const node &b) {
	if (a.x != b.x) return  a.x < b.x;
	if (a.y != b.y) return a.y < b.y;
	return a.z < b.z;
}

inline bool cmp2(const node &a, const node &b) {
	return a.y < b.y;
}


inline void CDQ(int l, int r) {
	//if (sum >= ans) return;
	//if (l == r) return;
	if (l + 33 >= r) {
		rep(i, l, r+1)
			rep(j, i+1, r+1) {
				sum += (a[i].x < a[j].x && a[i].y < a[j].y && a[i].z < a[j].z);
				sum += (a[i].x > a[j].x && a[i].y > a[j].y && a[i].z > a[j].z);
			}
		sort(a + l, a + r + 1, cmp2);
		return;
	}
	int mid = l + r >> 1;
	CDQ(l, mid);
//	if (sum >= ans) return;
	CDQ(mid + 1, r);
//	if (sum >= ans) return;
	pos = l;
	rep(i, mid+1, r+1) {
		while (pos <= mid && a[pos].y <= a[i].y) {
			add(a[pos].z + 1);
			pos++;
		}
		sum += qry(a[i].z + 1);
	//	if (sum >= ans) return;
	}
	rep(i, l, pos) del(a[i].z + 1);
	if (l == 1 && r == n) return;
	p1 = l; p2 = mid + 1;
	rep(i, l, r+1) {
		if (p1 > mid) tmp[i] = a[p2++];
		else if (p2 > r) tmp[i] = a[p1++];
		else if (a[p1].y  <= a[p2].y) tmp[i] = a[p1++];
		else tmp[i] = a[p2++];
	}
	rep(i, l, r+1) a[i] = tmp[i];
}


int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n; //n = 1 << 16;
	rep(i, 1, 10) {
		//rep(j, 1, n+1) b[i][j] = j;
		//random_shuffle(b[i] + 1, b[i] + n + 1);
		rep(j, 1, n+1) cin >> b[i][j], pp[b[i][j]] = j;
		rep(j, 1, n+1) b[i][j] = pp[j];
	}
	int cnt = 0;
	ans = pw(50);
	rep(x, 1, 10)
		rep(y, x+1, 10)
			rep(z, y+1, 10) {
				rep(i, 1, n+1) {
					a[i].x = b[x][i] - 1;
					a[i].y = b[y][i] - 1;
					a[i].z = b[z][i] - 1;
				}
				sort(a + 1, a + n + 1, cmp);
				CDQ(1, n);
				if (sum < ans) {
					ans = sum;
					px = x; py = y; pz = z;
				}
				sum = 0;
			}
	cout << px << " " << py << " " << pz << endl;
	return 0;
}

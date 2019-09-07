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

int dx[] = {0, 1, 0, -1};
int dy[] = {1, 0, -1, 0};
int ne[4][6];

const int N = 1000 + 3;

int dis[N][N][6];

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	memset(ne, -1, sizeof(ne));
	ne[0][0] = 1, ne[0][1] = 2, ne[0][2] = 3, ne[0][3] = 0; 
	ne[1][0] = 4, ne[1][4] = 2, ne[1][2] = 5, ne[1][5] = 0;
	ne[2][0] = 3, ne[2][3] = 2, ne[2][2] = 1, ne[2][1] = 0;
	ne[3][0] = 5, ne[3][5] = 2, ne[3][2] = 4, ne[3][4] = 0;
	rep(i, 0, 4) rep(j, 0, 6) if(ne[i][j] == -1) ne[i][j] = j;
	memset(dis, 0x3f, sizeof(dis));
	priority_queue<pair<pii, pii> > que;
	que.push(mp(pii(0, 0), pii(0, 0))); dis[0][0][0] = 0;
	while(!que.empty()) {
		auto u = que.top(); que.pop();
		int x = u.se.fi, y = u.se.se, d = u.fi.se;
		rep(i, 0, 4) {
			int nx = x + dx[i], ny = y + dy[i], nd = ne[i][d];
			if(nx < 0 || nx >= N || ny < 0 || ny >= N) continue;
			int t = dis[x][y][d] + 1;
			if(dis[nx][ny][nd] > t) {
				dis[nx][ny][nd] = t;
				que.push(mp(pii(-t, nd), pii(nx, ny)));
			}
		}
	}
	rep(i, 0, N) rep(j, i, N) {
	//rep(i, 0, 20) rep(j, 0, 20) {
		int det = dis[i][j][0] - i - j;
		int x = i % 4, y = j % 4;
		if(det == 2) dd(i), dd(j), dd(dis[i][j][0]), de(det);
		/*
		continue;
		if((!x && !y) || (x == 2 && y == 2)) {
			assert(det == 0);
			//if(det != 0) dd(i), dd(j), de(det);
		}
		else if(x + y == x || x + y == y) {
		//	assert(det == 2);
			if(det != 2) dd(i), dd(j), de(det);
		}
		else {
		//	if(det != 4) dd(i), dd(j), de(det);
		}
		//dd(i), dd(j), de(dis[i][j][0] - i - j);
		*/
	}
	return 0;
}

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
#define pw(c) (1ll<<(c))
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()

typedef vector<int> vi;

const int N = 505;
int pre[N];
int n, cnt, now, u;
vi g[N];
int m;
int find(int x) {
	return x == pre[x] ? x : pre[x] = find(pre[x]);
}
void join(int x, int y) {
	pre[find(x)] = find(y);
}

void add(int u, int v) {
	g[u].pb(v); g[v].pb(u);
	++m;
	join(u, v);
}
void build1() {
	int x = 1, y = 200 / x;
	rep(i, 0, x) rep(j, 0, y - 1) {
		int u = i * y + j, v = u + 1;
		add(u + 1, v + 1);
	}
	rep(i, 0, x - 1) rep(j, 0, y) {
		int u = i * y + j, v = u + y;
		add(u + 1, v + 1);
	}
	n = x * y;
}
int a[N];
void build2() {
	n = 200;
	rep(i, 1, n + 1) a[i] = i;
	swap(a[1], a[n / 2]);
	rep(i, 1, n) add(a[i], a[i + 1]);
}
void build3() {
	int u = 1, n = 200; int p = 2;
	rep(i, 101, n + 1) {
		if(p < 101) add(u, p++);
		add(u, i), u = i;
	}
}
void build4() {
	n = 200;
	rep(i, 3, n - 1) add(2, i), add(n - 1, i);
	add(1, 2);
	add(n - 1, n);
}
void build5() {
	int d = 5, n = 200, k = (n - 1) / 5, p = 2;
	rep(i, 0, 4) {
		int u = 1;
		rep(j, 1, k + 1) {
			add(u, p++);
			u = p - 1;
		}
	}
	int u = 1;
	while(p <= n) add(u, p++), u = p - 1;
}
void build6() {
	int d = 5, n = 200, k = (n - 1) / 5, p = 2;
	rep(i, 0, 4) {
		int st = p, ed = p + k - 1; p = ed + 1;
		add(1, st); add(ed, ed - 1);
		rep(i, st + 1, ed - 1) add(st, i), add(ed - 1, i);
	}
	int u = 1;
	while(p <= n) add(u, p++), u = p - 1;
}
void build7() {
	int d = 5, n = 200, k = (n - 1) / 5, p = 2;
	rep(i, 0, 4) {
		int st = p, ed = p + k - 1; p = ed + 1;
		rep(i, st, ed) add(1, i), add(ed, i);
	}
	int u = 1;
	while(p <= n) add(u, p++), u = p - 1;
}
void build8() {
	n = 200; int t = n;
	rep(i, 2, t) add(1, i);
	int u = 1;
	rep(i, t, n + 1) add(u, i), u = i;
}
void build9() {
	int n = 200, c = (n - 2) / 4, u = 1;
	rep(i, 1, c + 1) {
		add(u, u + 1);
		add(u, u + 2);
		add(u, u + 3);
		add(u + 1, u + 4);
		add(u + 2, u + 4);
		add(u + 3, u + 4);
		u += 4;
	}
	add(u, u + 1); n = u + 1;
}
void build0() {
	int d = 5;
	n = 200; int c = (n - 2) / d, u = 1;
	de(c);
	rep(i, 1, c + 1) {
		rep(j, 1, d) add(u, u + j), add(u + j, u + d);
		u += d;
	}
	de(u);
	add(u, u + 1); n = u + 1;
	de(n);
}
void bud1() {
	n = 200;
	rep(i, 2, n + 1) {
		add(1, i);
		if(i > 2 && i != n) add(i, i - 1);
	}
}
void bud2() {
	int d = 66;
	n = 200; int u = 1, c = (n - 1) / d;
	rep(i, 1, c + 1) {
		rep(j, 0, d) rep(k, j + 1, d) add(u + j, u + k);
		add(u + d - 1, u + d);
		u += d;
	}
	n = u;
}
void print() {
	cout << m << endl;
	rep(i, 1, n + 1) for(auto v : g[i]) if(i < v) cout << i << " " << v << endl;
}
void bud3() {
	n = 200;
	int d = 6, c = n / d, rt = c;
	rep(i, 2, c + 1) add(i - 1, i);
	int p = c + 1;
	rep(i, 1, d) {
		int u = rt;
		rep(i, 1, c + 1) add(u, p++), u = p - 1;
	}
	n = u;
}
int main() {
	std::ios::sync_with_stdio(0);
std::cin.tie(0);
	cin >> n;
	if(n == 3) {
		cout << "2 \n 1 2 \n 2 3 \n" ;
		return 0;
	}
	rep(i, 1, n + 1) pre[i] = i;
	int tn = n;
	bud2();
//	de(n);
	while(n < tn) add(n, n + 1), ++n;//, dd(n - 1) ,de(n);
//	dd(find(1)); de(find(n));
	print();
	return 0;
//	de(sz(g[n]));
	/*
	//int B = 10;
	int m = 100;
	rep(i, 3, m+1) {
		add(i, 1);
		add(2, i);
	}
	rep(i, m+1, n+1) {
		if (i == m) add(1, i);
		else add(i, i-1);
		//if (i % B == 0) add(i, 2);
	}
	*/
	/*rep(i, 101, 201) {
		g[
		}*/
	//de(sz(g[3]));
	srand(time(0));
	now = 1;
	cnt = 0;
	while (1) {
		//de(now);
		u = rand() % sz(g[now]);
		now = g[now][u];
		cnt++;
	//	de(cnt);
		if (now == n) break;
	}
	cout << cnt << endl;
	return 0;
}

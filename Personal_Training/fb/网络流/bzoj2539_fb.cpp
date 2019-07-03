#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define rep(i, a, b) for(int i=(a); i<(b); i++)
#define per(i, a, b) for(int i=(b)-1; i>=(a); i--)
#define sz(a) (int)a.size()
#define de(a) cout << #a << " = " << a << endl
#define dd(a) cout << #a << " = " << a << " "
#define all(a) (a).begin(), (a).end()
#define pw(x) (1ll<<(x))
#define lb(x) ((x) & -(x))
#define endl "\n"
typedef double db;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;
//----

#define x(a) a.x
#define y(a) a.y
typedef double db;
const db eps = 1e-8;
const db pi = acos(-1);

//负数 -1 零  0 正数  1
int sign(db x) {
    return (x > eps) - (x < -eps);
}

struct P {
    db x,y;
    P() {}
    P(db x, db y) {
        this->x = x;
        this->y = y;
    }
    P operator + (const P &c) const {
        return P(x + c.x, y + c.y);
    }
    P operator - (const P &c) const {
        return P(x - c.x, y - c.y);
    }
    P operator * (const db &c) const {
        return P(x * c, y * c);
    }
    P operator / (const db &c) const {
        return P(x / c, y / c);
    }
    bool operator < (const P &c) const {
        int f = sign(x - c.x);
        return f ? f < 0 : sign(y - c.y) < 0;
    }
    bool operator == (const P &c) const {
        return !sign(x - c.x) && !sign(y - c.y);
    }
    bool operator != (const P &c) const {
        return !(*this == c);
    }
    bool operator > (const P &c) const {
        return !(*this == c) && !(*this < c);
    }
};

db norm(P a) {
    return x(a) * x(a) + y(a) * y(a);
}

db dis(P a, P b) {
    return sqrt(norm(a - b));
}

db dot(P a, P b) {
    return x(a) * x(b) + y(a) * y(b);
}

db cross(P a, P b) {
    return x(a) * y(b) - x(b) * y(a);
}

bool onS1(P p, P a, P b) {
    return sign(cross(p - a, b - a)) == 0 && sign(dot(p - a, p - b)) <= 0;
}

const int inf = pw(30);
// [0,n) , init!! , inf modify
template<class U,class V>
struct MCMF{
    static const int N = 6000, M = 201010;
    int h[N], ing[N], pre[N], to[M], ne[M], e, s, t, n;
    U cap[M]; V dis[N], cost[M];
    void ini(int _n = N){ fill(h , h + (n=_n) , -1);e = 0;}
    void liu(int u,int v,U c,V w){ to[e] = v;ne[e] = h[u];cap[e] = c;cost[e] = w;h[u] = e++;}
    void link(int u,int v,U c,V w){ liu(u,v,c,w);liu(v,u,0,-w); }
    bool spfa(){
        queue<int> Q;
        fill(dis, dis+n, inf);
        Q.push(s), ing[s] = 1, dis[s] = 0;
        while(!Q.empty()){
            int c = Q.front(); Q.pop(); ing[c] = 0;
            for(int k = h[c]; ~k; k = ne[k]) if (cap[k] > 0) {
                int v = to[k];
                if(dis[c] + cost[k] < dis[v]){
                    dis[v] = dis[c] + cost[k];
                    pre[v] = k;
                    if(!ing[v]) Q.push(v) , ing[v] = 1;
                }
            }
        }
        //return dis[t] < 0;
        return dis[t] != inf;
    }
    U flow; V mincost;
    pair<U, V> run(int _s,int _t){
        s = _s , t = _t;
        flow = mincost = 0;
        while(spfa()){
            U pl = inf; int p, k;
            for(p = t;p != s;p = to[k^1]) pl = min(pl, cap[k = pre[p]]);
            for(p = t;p != s;p = to[k^1]) cap[k = pre[p]] -= pl, cap[k^1] += pl;
			mincost += pl * dis[t];
            flow += pl;
        }
        return mp(flow, mincost);
    }
};

MCMF<int, int> G;

const int N = 1000;
int d, n, s, t, w, u, v, ok, vis[N][N];
P a[N];
map<string, int> id;
string s1, s2;

void Norm(string &s) {
	rep(i, 0, sz(s)) if (s[i] >= 'A' && s[i] <= 'Z') s[i] += 'a' - 'A'; 
}

int main() {
	freopen("a.in","r",stdin);
	ios::sync_with_stdio(0);
	cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	cin >> d >> n;
	G.ini(n * 2 + 10); s = G.n - 5; t = s + 1;
	rep(i, 1, 2 * n+1) {
		cin >> a[i].x >> a[i].y >> s1;
		Norm(s1);
		assert(!id.count(s1));
		id[s1] = i;
		if (i <= n) G.link(s, i, 1, 0);
		else G.link(i, t, 1, 0);
	}
	int cnt = 0;
	while (cin >> s1) {
		if (s1 == "End") break;
		cin >> s2 >> w;
		cnt++;
		assert(w >= 1);
		Norm(s1);Norm(s2);
		assert(id.count(s1));
		assert(id.count(s2));
		assert(cnt <= 80000);
		u = id[s1]; v = id[s2];
		if (u > v) swap(u, v);
		assert(1 <= u && u <= n && v > n && v <= n * 2);
		vis[u][v] = w;
	}
	rep(u, 1, n+1) rep(v, n+1, n * 2 + 1) {
		vis[u][v] = max(vis[u][v], 1);
		if (sign(dis(a[u], a[v]) - d) <= 0) {
			ok = 1;
			rep(i, 1, 2 * n + 1) if (i != u && i != v && sign(dis(a[i], a[u]) + dis(a[i], a[v]) - dis(a[u], a[v])) == 0) ok = 0;
			if (ok) G.link(u, v, 1, -vis[u][v]);
		} 
	}
	pii ans = G.run(s, t);
	assert(ans.fi == n);
	cout << -ans.se;
	return 0;
}



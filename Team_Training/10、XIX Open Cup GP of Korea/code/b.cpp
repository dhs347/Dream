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
const int P = 1e9 + 7;
//----

const int N = 2555;
int n, m, sx, sy, x, y;
int dx[] = {-1, 0, 1, 0};
int dy[] = {0, 1, 0, -1};
string s[N];

int ID(int i, int j) { return i * m + j;}

bool check(int x, int y) {return x >= 0 && x < n && y >= 0 && y < m && s[x][y] != '#';}
struct TwoSat {
	static const int N = :: N * 2;
	int dfn[N],low[N],id[N],st[N],_st,_,cc,n,mark[N];
	vi g[N];
	void ini(int tot) {
		n=tot*2;
		rep(i,0,tot)g[i<<1].clear(),g[i<<1|1].clear();
	}
	void addedge(int u,int v,int pu,int pv) {
		u=u<<1|pu,v=v<<1|pv;
		g[u].pb(v);
		g[v^1].pb(u^1);
	}
	void dfs(int c,vi g[]) {
		dfn[c]=low[c]=++cc;
		st[_st++]=c;
		for(auto t:g[c]) if(!dfn[t])
				dfs(t,g),low[c]=min(low[c],low[t]);
			else if(!id[t]) low[c]=min(low[c],dfn[t]);
		if(low[c]==dfn[c]) {
			++_;
			do {
				id[st[--_st]]=_;
			} while(st[_st]!=c);
		}
	}
	bool solve() {
		fill_n(dfn,n,cc=0);
		fill_n(low,n,_st=0);
		fill_n(id,n,_=0);
		rep(i,0,n) if(!dfn[i]) dfs(i,g);
		for(int i=0; i<n; i+=2) if(id[i]==id[i+1]) return false;
//else mark[i>>1]=id[i]>id[i+1];
		return true;
	}
} sat;

namespace SCC{
    const int N = 2550;
    int dfn[N],low[N],id[N],st[N],_st,_,cc;
    void dfs(int c,vi g[]){
        dfn[c]=low[c]=++cc;
        st[_st++]=c;
        for(auto t:g[c])
            if(!dfn[t])
                dfs(t,g),low[c]=min(low[c],low[t]);
            else if(!id[t])
                low[c] =min(low[c],dfn[t]);
        if(low[c]==dfn[c]){
            ++_;
            do{id[st[--_st]]=_;}while(st[_st]!=c);
        }
    }
    vi ng[N]; bool vis[N][N];
    void dfs2(int u, vi g[], int r) {
    	vis[r][u] = 1;
		for (auto v : g[u]) 
			if (!vis[r][v]) dfs2(v, g, r);
	}
    
    int solve(int n,vi g[]){
        fill_n(dfn,n,cc=0);
        fill_n(low,n,_st=0);
        fill_n(id,n,_=0);
        rep(i,0,n) if(!dfn[i]) dfs(i,g);
        rep(i,0,n) --id[i];
        fill_n(ng,_,vi());
        rep(i,0,n) for(auto j:g[i]) if(id[i]!=id[j]) ng[id[i]].pb(id[j]);
        rep(i, 0, _) dfs2(i, ng, i);
        rep(i, 0, _) {
			rep(j, i+1, _) if (!vis[i][j] && !vis[j][i]) {
				sat.addedge(i, j, 0, 1); 
				//sat.addedge(j, i, 0, 1);
			}
		}
		int p = id[ID(sx, sy)];
		sat.addedge(p, p, 1, 0);
		rep(j, 0, _) if (!vis[p][j]) sat.addedge(p, j, 0, 1);
        return _;
    }
}

vi g[N];

int main() {
	//freopen("a.in","r",stdin);
	ios::sync_with_stdio(0);
	cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	cin >> n >> m;
	rep(i, 0, n) cin >> s[i];
	rep(i, 0, n) rep(j, 0, m) if (s[i][j] != '#'){
		if (s[i][j] == 'O') sx = i, sy = j;
		rep(k, 0, 4) {
			x = i; y = j;
			while (check(x + dx[k], y + dy[k])) x += dx[k], y += dy[k];
			g[ID(i, j)].pb(ID(x, y));
		}
	}
	sat.ini(n * m);
	SCC :: solve(n * m, g);
	rep(i, 0, n) rep(j, 0, m) if (s[i][j] == '*') {
		sat.addedge(SCC:: id[g[ID(i, j)][0]], SCC:: id[g[ID(i, j)][1]], 1, 0);
	}
	if (sat.solve()) cout << "Yes";else cout << "No";
	return 0;
}



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
#define all(a) a.begin(), a.end()
#define pw(x) (1ll<<(x))
#define endl "\n"
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef double db;

void file_put() {
    freopen("filename.in", "r", stdin);
    freopen("filename.out", "w", stdout);
}

// _ starts from 0

const int N = 1000050;
int rd[N];

namespace SCC{
    int dfn[N],low[N],id[N],st[N],_st,_,cc;
    void dfs(int c,vi g[]){
        dfn[c]=low[c]=++cc;
        st[_st++]=c;
        //for(auto t:g[c])
        rep(kk,0,sz(g[c])) {
            int t=g[c][kk];
            if(!dfn[t])
                dfs(t,g),low[c]=min(low[c],low[t]);
            else if(!id[t])
                low[c] =min(low[c],dfn[t]);
        }
        if(low[c]==dfn[c]){
            ++_;
            do{id[st[--_st]]=_;}while(st[_st]!=c);
        }
    }
    vi ng[N];
    int solve(int n,vi g[]){
        fill_n(dfn,n,cc=0);
        fill_n(low,n,_st=0);
        fill_n(id,n,_=0);
        rep(i,0,n) if(!dfn[i]) dfs(i,g);
        rep(i,0,n) --id[i];
        fill_n(ng,_,vi());
        rep(i,0,n) rep(kk,0,sz(g[i])) {
            int j=g[i][kk];
            if(id[i]!=id[j]) ng[id[j]].pb(id[i]),rd[id[i]]++;
        }
        return _;
    }
}

using namespace SCC;
vi E[N],G[N],H[N]; int n,m,x,y,s,t,tot,S,T,d[N],no[N]; bool v1[N],v2[N]; double ret[N];

namespace Gauss{
	static const int N = 505;
	db a[N][N], x[N];
	bool ok[N];
	int free[N], free_num;
	const db eps = 1e-14;
	int gauss(int equ, int var){
		int k, col, p;
		fill_n(ok, var, 0); free_num = 0;
		fill_n(x, var, 0);
		for(k = col = 0; k < equ && col < var; ++k, ++col){
			p = k;
			rep(i, k+1, equ) if(fabs(a[i][col]) > fabs(a[p][col])) p = i;
			if (p != k) rep(j, k, var+1) swap(a[p][j], a[k][j]);
			if(fabs(a[k][col]) < eps) {k--; continue;}
			rep(i, k+1, equ){
				if(fabs(a[i][col]) < eps) continue;
				db t = a[i][col] / a[k][col];
				rep(j, col, var+1) a[i][j] -= a[k][j] * t;
			}
		}
		rep(i, k, equ) if (fabs(a[i][var]) > eps) return -1;
		if(k < var) return var - k;
		per(i, 0, var) {
			db t = a[i][var];
			rep(j, i+1, var) if (fabs(a[i][j]) > eps) t -= x[j] * a[i][j];
			x[i] = t / a[i][i];
		}
		return 0;
	}
}

void dfs1(int x) {
    v1[x]=1;
    rep(i,0,sz(E[x])) if (!v1[E[x][i]]) dfs1(E[x][i]);
}

void dfs2(int x) {
    v2[x]=1;
    rep(i,0,sz(G[x])) if (!v2[G[x][i]]) dfs2(G[x][i]);
}

inline bool check() {
    dfs1(s),dfs2(t);
    rep(i,0,n) if (v1[i] && !v2[i]) return 0;
    return 1;
}

void calc(int X) {
    vi &G=H[X];
    int m=sz(G);
    rep(i,0,m) no[G[i]]=i;
    rep(i,0,m) rep(j,0,m+1) Gauss::a[i][j]=0;
    rep(i,0,m) {
        int x=G[i]; double p=d[x]?1./d[x]:1;
        Gauss::a[i][i]=1;
        rep(j,0,sz(E[x])) {
            int y=E[x][j];
            if (id[x]==id[y]) Gauss::a[i][no[y]]+=-p; else Gauss::a[i][m]+=p*ret[y]; 
        }
        Gauss::a[i][m]+=(G[i]!=t);
    }
    Gauss::gauss(m,m);
    rep(i,0,m) ret[G[i]]=Gauss::x[i];
    rep(i,0,m) no[G[i]]=0;
}

void dfs(int X) {
    calc(X);
    if (X==S) return;
    rep(i,0,sz(ng[X])) if (!--rd[ng[X][i]]) dfs(ng[X][i]);
}

int main() {
    //file_put();
    
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
    
    cin>>n>>m>>s>>t,s--,t--;
    rep(i,1,m+1) cin>>x>>y,x--,y--,E[x].pb(y),G[y].pb(x),d[x]++;
    if (!check()) {
        cout<<"INF"<<endl;
        return 0;
    }
    solve(n,E),tot=_,S=id[s],T=id[t]; 
    rep(i,0,n) H[id[i]].pb(i);
    E[t].clear();
    dfs(T);
	
	cout << setiosflags(ios::fixed);
	cout << setprecision(3);
	cout << ret[s] << endl;
	
	//rep(i,0,n) de(ret[i]);
	
	return 0;
}


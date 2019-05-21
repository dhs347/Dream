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

#define mem(a,x) memset((a),(x),sizeof(a)) 

void file_put() {
    freopen("filename.in", "r", stdin);
    freopen("filename.out", "w", stdout);
}

const int N=1005,oo=1e9;
int n,m,s,t,x,y,dist[N][N],go[N][N]; double dp[N][N]; bool vis[N][N];
vi V[N];

void bfs(int s) {
    mem(dist[s],0);
    queue<int> Q;
    Q.push(s);
    while (!Q.empty()) {
        int x=Q.front(); Q.pop();
        rep(i,0,sz(V[x])) {
            int y=V[x][i];
            if (y==s || dist[s][y]) continue;
            dist[s][y]=dist[s][x]+1;
            Q.push(y);
        }
    }
}

double dfs(int s,int t) {
    if (vis[s][t]) return dp[s][t];
    if (s==t) {
        vis[s][t]=1;
        return dp[s][t]=0;
    }
    //de(s),de(t);
    int x=go[s][t],y=go[x][t];
    //de(x),de(y);
    if (x==t || y==t) return vis[s][t]=dp[s][t]=1;
    double sum=0;
    rep(i,0,sz(V[t])) {
        int k=V[t][i];
        sum+=dfs(y,k)/(sz(V[t])+1);
    }
    sum+=dfs(y,t)/(sz(V[t])+1); 
    vis[s][t]=1;
    return dp[s][t]=sum+1;
}

int main() {
    //file_put();
    
    std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	
	cin>>n>>m>>s>>t;
	rep(i,1,m+1) cin>>x>>y,V[x].pb(y),V[y].pb(x);
	rep(i,1,n+1) bfs(i);
	rep(i,1,n+1) rep(j,1,n+1) {
	    if (i==j) continue;
	    int t=-1,d=oo;
	    rep(k,0,sz(V[i]))
            if (dist[V[i][k]][j]<d) d=dist[V[i][k]][j],t=V[i][k]; else
            if (dist[V[i][k]][j]==d && V[i][k]<t) t=V[i][k];
	    go[i][j]=t;
    }
	cout << setiosflags(ios::fixed);
	cout << setprecision(3);
    cout<<dfs(s,t)<<endl;
    
	return 0;
}


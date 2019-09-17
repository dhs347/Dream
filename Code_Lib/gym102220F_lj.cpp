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

const int N=2e5+5; 
int T,n,m,dd[N],d[N][6],s[N][6],vis[N][6],x,y; vi V[N]; char p[6],q[6]; queue<pii> Q;

int main() {
	//file_put();
	
	scanf("%d",&T);
	while (T--) {
		scanf("%d%d",&n,&m);
		rep(i,1,n+1) V[i].clear(),dd[i]=0;
		rep(i,1,n+1) rep(j,0,6) d[i][j]=0;
		rep(i,1,m+1) scanf("%d%d",&x,&y),V[y].pb(x),dd[x]++;
		scanf("%s%s",p,q);
		rep(i,1,n+1) rep(j,0,6) 
			if (!(d[i][j]=dd[i])) s[i][j]=-1,vis[i][j]=1,Q.push(mp(i,j));
			else s[i][j]=vis[i][j]=0;
		while (!Q.empty()) {
			pii tt=Q.front(); Q.pop(); 
			int u=tt.fi,v=tt.se,t=(v+5)%6,x=2*(q[t]=='0')-1;
			int w=(x==-1?'A'+'B'-p[t]:p[t]),y=2*(w==p[v])-1;
			if (y==s[u][v]) {
				for (auto i:V[u]) if (!vis[i][t]) 
					s[i][t]=x,vis[i][t]=1,Q.push(mp(i,t));
			} else if (y==-s[u][v]) {
				for (auto i:V[u]) if (!--d[i][t]) 
					s[i][t]=-x,vis[i][t]=1,Q.push(mp(i,t));
			}
		}
		rep(i,1,n+1) printf("%c","ADB"[s[i][0]*(p[0]=='A'?-1:1)+1]);
		printf("\n");
	}
	
	return 0;
}


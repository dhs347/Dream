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
 
const int N=2005,oo=(1<<29);
int n,m,v,e,c[N],d[N],dist[305][305],x,y,w; double p[N],dp[N][N][2],ans=1e30;
 
int main() {
    //file_put();
     
    scanf("%d%d%d%d",&n,&m,&v,&e);
    rep(i,1,n+1) scanf("%d",&c[i]);
    rep(i,1,n+1) scanf("%d",&d[i]);
    rep(i,1,n+1) scanf("%lf",&p[i]);
    rep(i,1,305) rep(j,1,305) dist[i][j]=oo;
    rep(i,0,301) dist[i][i]=0;
    rep(i,1,e+1) {
        scanf("%d%d%d",&x,&y,&w);
        dist[x][y]=dist[y][x]=min(dist[x][y],w);
    }
    rep(k,1,v+1) rep(x,1,v+1) rep(y,1,v+1) {
        if (k==x || k==y || y==x) continue;
        if (dist[x][k]+dist[k][y]<dist[x][y]) dist[x][y]=dist[x][k]+dist[k][y];
    }
    //rep(i,0,v+1) rep(j,0,v+1) printf("%d%c",dist[i][j]," \n"[j==v]);
    rep(i,0,N) rep(j,0,N) rep(k,0,2) dp[i][j][k]=oo;
    dp[0][0][0]=0;
    rep(i,1,n+1) {
        dp[i][0][0]=dp[i-1][0][0]+dist[c[i-1]][c[i]];
        rep(j,1,min(m,i)+1){
            dp[i][j][0]=min(dp[i-1][j][0]+dist[c[i-1]][c[i]],dp[i-1][j][1]+p[i-1]*dist[d[i-1]][c[i]]+(1-p[i-1])*dist[c[i-1]][c[i]]);
            dp[i][j][1]=min(
                dp[i-1][j-1][0]+p[i]*dist[c[i-1]][d[i]]+(1-p[i])*(dist[c[i-1]][c[i]]),
                dp[i-1][j-1][1] + p[i-1]*p[i]*dist[d[i-1]][d[i]]
                                + p[i-1]*(1-p[i])*dist[d[i-1]][c[i]]
                                + (1-p[i-1])*p[i]*dist[c[i-1]][d[i]]
                                + (1-p[i-1])*(1-p[i])*dist[c[i-1]][c[i]]
            );
        }
    }
    ans=dp[n][0][0]; 
    rep(i,0,m+1) rep(k,0,2) ans=min(ans,dp[n][i][k]);
    printf("%.2lf\n",ans);
    //printf("%.2lf\n",dp[1][1][1]);
     
    return 0;
}

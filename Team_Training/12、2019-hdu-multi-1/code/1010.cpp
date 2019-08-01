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
#define mem(a,x) memset(a,x,sizeof(a))

#define rep_it(it,x) for (__typeof((x).begin()) it=(x).begin(); it!=(x).end(); it++)
#define ____ puts("\n_______________\n\n") 
#define debug(x) ____; cout<< #x << " => " << (x) << endl
#define debug_pair(x) cout<<"\n{ "<<(x).fir<<" , "<<(x).sec<<" }\n"
#define debug_arr(x,n) ____; cout<<#x<<":\n"; rep(i,0,n+1) cout<<#x<<"["<<(i)<<"] => "<<x[i]<<endl
#define debug_arr2(x,n,m) ____; cout<<#x<<":\n"; rep(i,0,n+1) rep(j,0,m+1) cout<<#x<<"["<<(i)<<"]["<<(j)<<"]= "<<x[i][j]<<((j==m)?"\n\n":"    ")
#define debug_set(x) ____; cout<<#x<<": \n"; rep_it(it,x) cout<<(*it)<<" "; cout<<endl
#define debug_map(x) ____; cout<<#x<<": \n"; rep_it(it,x) debug_pair(*it)



void file_put() {
    freopen("filename.in", "r", stdin);
    freopen("filename.out", "w", stdout);
}

const int N=105,P=998244353;
int T,n,m,a[N],b[N],pa[N],pb[N]; bool v[N]; ll dp[N][N][N],ans; 

void dfs(int x,int l,int r) {
    if (dp[x][l][r]!=-1) return;
    ll &ret=dp[x][l][r]; ret=0;
    if (l==r) {
        ret=1;
        if (a[x]==b[l]) return;
        if (a[x] && b[l]) ret=0;
        if (a[x] && pb[a[x]] && pb[a[x]]!=l) ret=0;
        if (b[l] && pa[b[l]] && pa[b[l]]!=x) ret=0;
        return;
    }
    if (r+1==l) { ret=1; return; }
    if (r<l) return;
    if (a[x]) {
        if (pb[a[x]]) {
            if (pb[a[x]]<l || pb[a[x]]>r) return;
            dfs(x+1,l,pb[a[x]]-1),dfs(x+1+pb[a[x]]-l,pb[a[x]]+1,r);
            ret+=dp[x+1][l][pb[a[x]]-1]*dp[x+1+pb[a[x]]-l][pb[a[x]]+1][r]%P,ret%=P;
            return;
        }
        int j=l;
        rep(i,l,r+1) {
            if (pa[b[i]]) {
                if (pa[b[i]]<x || pa[b[i]]>x+r-l) return;
                j=max(j,pa[b[i]]-x+l);
            }
            if (b[i]) continue;
            if (i<j) continue;
            dfs(x+1,l,i-1),dfs(x+1+i-l,i+1,r);
            ret+=dp[x+1][l][i-1]*dp[x+1+i-l][i+1][r]%P,ret%=P; 
        }
        return;
    }
    int j=l;
    rep(i,l,r+1) {
        if (pa[b[i]]) {
            if (pa[b[i]]<x || pa[b[i]]>x+r-l) return;
            j=max(j,pa[b[i]]-x+l);
        }
        if (i<j) continue;
        dfs(x+1,l,i-1),dfs(x+1+i-l,i+1,r);
        ret+=dp[x+1][l][i-1]*dp[x+1+i-l][i+1][r]%P,ret%=P; 
    }
}

int main() {
//    file_put();
    
    scanf("%d",&T);
    while (T--) {
        scanf("%d",&n),mem(pa,0),mem(pb,0),mem(v,0),mem(dp,-1),m=0;
        rep(i,1,n+1) scanf("%d",&a[i]),v[a[i]]=1,pa[a[i]]=(a[i]>0)*i;
        rep(i,1,n+1) scanf("%d",&b[i]),v[b[i]]=1,pb[b[i]]=(b[i]>0)*i;
        dfs(1,1,n),ans=dp[1][1][n];
        rep(i,1,n+1) m+=!v[i];
        rep(i,1,m+1) ans=ans*i%P;
        printf("%lld\n",ans);
    } 
    
	return 0;
}


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

const int N=1005,P=1e9+7;
int n,m,cnt_r=0,cnt_v=0,cnt_hh=0,cnt_vv=0; ll k,a,b,c; char s[N][N];

ll Pow(ll x,ll k) {
    ll ret=1;
    for (; k; k>>=1,x=x*x%P) if (k&1) ret=ret*x%P;
    return ret;
}

int main() {
//    file_put();
    
    scanf("%d%d%lld",&n,&m,&k);
    if (k==0) return 0*printf("1\n");
    rep(i,1,n+1) scanf("%s",s[i]+1);
    rep(i,1,n+1) cnt_r+=(s[i][1]=='#' && s[i][m]=='#');
    rep(i,1,m+1) cnt_v+=(s[1][i]=='#' && s[n][i]=='#');
    rep(i,1,n+1) rep(j,1,m) cnt_hh+=(s[i][j]=='#' && s[i][j+1]=='#');
    rep(i,1,m+1) rep(j,1,n) cnt_vv+=(s[j][i]=='#' && s[j+1][i]=='#');
    rep(i,1,n+1) rep(j,1,m+1) a+=(s[i][j]=='#'); 
    if (cnt_r && cnt_v) return 0*printf("1\n");
    if (cnt_r) b=cnt_hh,c=cnt_r; else b=cnt_vv,c=cnt_v;
    if (!cnt_r && !cnt_v) return 0*printf("%lld\n",Pow(a,k-1));
//    assert(a!=c);
//    if (a!=c) {
        ll t=b*Pow(a-c,P-2)%P;
        ll ans=Pow(a,k-1)*(1-t)%P;
        ans+=t*Pow(c,k-1)%P; ans%=P; 
        return 0*printf("%lld\n",(ans+P)%P);
        assert(0);
//    }
//    ll ans=Pow(c,k-1);
//    ans*=(1-b*Pow(c,P-2)%P*(k-1)%P)%P; ans%=P;
//    printf("%lld\n",(ans+P)%P); 
    
	return 0;
}


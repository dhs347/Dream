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

const int N=1e6+5;
int a[N],pre[N],suf[N],nxt[N],v[N],T,n,m,num;

int G() { while (v[num]) num++; v[num]=-1; return num; }

void D(int l,int r) { suf[pre[l]]=suf[r],pre[suf[r]]=pre[l]; }

void solve(int l,int r) {
    for (int i=l; i<=r; i=suf[i])
        while (nxt[i]) {
            solve(suf[i],pre[nxt[i]]),D(suf[i],nxt[i]);
            nxt[i]=nxt[nxt[i]];
        }
    int s=0,cnt=0,rr=a[pre[l]];
    for (int i=l; i<=r; i=suf[i]) cnt+=a[i]>0,s++; s=s+1>>1;
    for (int i=l; i<=r; i=suf[i]) if (!a[i] && cnt<s) cnt++,a[i]=G();
    for (int i=l; suf[i]<=r; i=suf[i]) {
        while (i>l && suf[i]<=r && !a[pre[i]] && a[i] && a[suf[i]])
            a[pre[i]]=a[suf[i]],D(i,suf[i]),i=pre[pre[i]];
        while (i>=l && suf[suf[i]]<=r && a[i] && a[suf[i]] && !a[suf[suf[i]]])
            a[suf[suf[i]]]=a[i],D(suf[i],suf[suf[i]]),i=pre[i];
    }
    for (int i=l; i<=r; i=suf[i]) if (!a[i]) a[i]=rr;
}

int main() {
//    file_put();
    
    scanf("%d",&T);
    while (T--) {
        scanf("%d",&n),m=2*n-1,num=1;
        rep(i,0,m+3) pre[i]=suf[i]=nxt[i]=v[i]=0;
        rep(i,1,m+1) scanf("%d",&a[i]); a[1]=a[m]=1;
        rep(i,1,m+1) if (a[i]==-1) a[i]=0;
        per(i,1,m+1) if (a[i]) nxt[i]=v[a[i]],v[a[i]]=i;
        rep(i,0,m+1) pre[i]=i-1,suf[i]=i+1;
        solve(1,m);
        rep(i,1,m+1) printf("%d%c",a[i]," \n"[i==m]);
    }
    
	return 0;
}


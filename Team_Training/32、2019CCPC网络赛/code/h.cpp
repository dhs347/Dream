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

const int N=1e5+5;
int n,a[N],T,num=0,x,k; ll ans=0;

bool cmp(int x,int y) {
    return x>y;
}

priority_queue<int> Q;

int main() {
//    file_put();
    
    scanf("%d",&T);
    while (T--) {
        scanf("%d%d",&n,&k),num=0,ans=0,x=1e9+100;
        rep(i,1,n+1) scanf("%d",&a[i]);
        sort(a+1,a+n+1,cmp);
        while (!Q.empty()) Q.pop();
        rep(i,1,n+1) {
            ans+=a[i];
            if (Q.empty()) {
                ans+=k;
                Q.push(a[i]);
                continue;
            }
            int x=Q.top(); Q.pop();
            if (x>=k) {
                Q.push(a[i]);
                if (x>k) Q.push(x-k);
                continue;
            } else {
                ans+=k-x;
                Q.push(a[i]);
                continue;
            }
        } 
//        ans+=(ll)(n-min(num,n))*k;
//        ans+=min(x,k);
        printf("%lld\n",ans);
    }
    
    return 0;
}

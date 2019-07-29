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

const int N=1000005;

const int M=32;
struct LB{
    ll a[M]; int id[M];
    void Clear() { memset(a,0,sizeof(a)); }
    void Copy(const LB&L) {
        rep(i,0,M) a[i]=L.a[i],id[i]=L.id[i];
    }
    void Ins(LB &L,ll x,int no) {
        Copy(L);
        for (int i=M-1; ~i && x; --i)
            if (x>>i&1) {
                if (!a[i]) a[i]=x,id[i]=no; else
                    if (no>id[i]) swap(a[i],x),swap(id[i],no);
                x^=a[i];
            }
    }
    ll Qry(int l,ll x=0) {
        per(i,0,M) if (id[i]>=l) x=max(x,x^a[i]); return x;
    }
} B[N];

int n,T,m,op,x,y,last;

int main() {
//    file_put();
    
    scanf("%d",&T);
    while (T--) {
        last=0;
        scanf("%d%d",&n,&m);
        rep(i,1,n+1) scanf("%d",&x),B[i].Ins(B[i-1],x,i);
        while (m--) {
            scanf("%d%d",&op,&x);
            if (op) {
                ++n;
                B[n].Ins(B[n-1],x^last,n);
                continue;
            }
            scanf("%d",&y);
            y=(y^last)%n+1,x=(x^last)%n+1;
            if (x>y) swap(x,y); 
            printf("%d\n",last=B[y].Qry(x));
        }
    }
    
	return 0;
}


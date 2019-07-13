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
 
int mul(int x,int y,int p) {
    return (ll)x*y%p; 
}
 
int add(int x,int y,int p) {
    x+=y;
    if (x>=p) x-=p;
    if (x<0) x+=p;
}
 
const int N=100005;
int a[N],s[N],tot,n,m,k,x,g,gk[N],no[N];
int _p=1004535809;
 
ll Pow(ll x,ll k,ll p) {
    ll ret=1;
    for (; k; k>>=1,x=x*x%p) if (k&1) ret=ret*x%p;
    return ret; 
}
 
struct Euler{
    vector<ll> c;
    inline bool check_g(ll g, ll p) {
        rep(i,0,sz(c))
            if (Pow(g, c[i], p) == 1)
                return 0;
        return 1;
    }
    inline ll getRoot(ll p) {
        c.clear();
        ll tmp=p-1,g;
        for (ll k=2; k*k<=tmp; ++k)
            if (tmp % k == 0) {
                c.pb(k);
                while (tmp % k == 0) tmp /= k;
            }
        if (tmp != 1) c.pb(tmp);
        rep(i,0,sz(c)) c[i] = (p-1) / c[i];
        for (g=1; !check_g(g,p); ++g);
        return g;
    }
} E;
 
ll Pow(ll x,ll k) { ll ans=1; for (;k;k>>=1,x=x*x%_p) if (k&1) (ans*=x)%=_p; return ans; } 
 
template <class V>
struct FT{
    static const int N=1<<14; V w[2][N*2+5],rev[N*2+5],tmp; V B[N*2+5];
    void Init() {
        V w0=Pow(3,(_p-1)/N),m; w[0][0]=w[1][0]=1;
        rep(i,1,N) w[0][i]=w[1][N-i]=(ll)w[0][i-1]*w0%_p;
        for (m=0; (1<<m)!=N; m++);
        rep(i,1,N) rev[i]=(rev[i>>1]>>1)|(i&1)<<m-1;
    }
    void FFT(V A[],int op){
        rep(i,0,N)
            if (i<rev[i]) swap(A[i],A[rev[i]]);
        for (int i=1; i<N; i<<=1)
            for (int j=0,t=N/(i<<1); j<N; j+=i<<1)
                for (int k=j,l=0; k<j+i; k++,l+=t) {
                    V x=A[k],y=(ll)w[op][l]*A[k+i]%_p;
                    A[k]=(x+y)%_p,A[k+i]=(x-y+_p)%_p;
                }
         
        if (op) { tmp=Pow(N,_p-2); rep(i,0,N) A[i]=1ll*A[i]*tmp%_p; }
    }
    void Solve(V A[],V _B[],V C[]) {
        rep(i,0,N) B[i]=_B[i];
        FFT(A,0); FFT(B,0); 
        rep(i,0,N) C[i]=(ll)A[i]*B[i]%_p; FFT(C,1);
        rep(i,m-1,N) (C[i%(m-1)]+=C[i])%=_p,C[i]=0;
         
    }
    void Pinfang(V A[],V C[]) {
        FFT(A,0); 
        rep(i,0,N) C[i]=(ll)A[i]*A[i]%_p; FFT(C,1);
        rep(i,m-1,N) (C[i%(m-1)]+=C[i])%=_p,C[i]=0; 
    }
};
 
FT<int> T;
 
int ret[N];
 
void Pow(int a[],int k) {
    for (;k;k>>=1,T.Pinfang(a,a))
        if (k&1) T.Solve(ret,a,ret);
}
 
int main() {
//    file_put();
     
    scanf("%d%d%d%d",&n,&m,&x,&tot);
    gk[0]=1,g=E.getRoot(m);
    rep(i,1,m-1) gk[i]=mul(gk[i-1],g,m),no[gk[i]]=i;
    rep(i,1,tot+1) {
        scanf("%d",&s[i]);
        if (s[i]) a[no[s[i]]]++;
    }
    x=no[x],ret[0]=1;
    T.Init();
    Pow(a,n);
    printf("%d\n",ret[x]);
     
    return 0;
}

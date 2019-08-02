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
typedef vector<ll> vi;
typedef double db;
#define mem(a,x) memset(a,x,sizeof(a))
  
void file_put() {
    freopen("filename.in", "r", stdin);
    freopen("filename.out", "w", stdout);
}
  
#define ____ puts("\n_______________\n\n")
#define debug(x) ____; cout<< #x << " => " << (x) << endl
#define debug_pair(x) cout<<"\n{ "<<(x).fir<<" , "<<(x).sec<<" }\n"
#define debug_arr(x,n) ____; cout<<#x<<":\n"; rep(i,0,n+1) cout<<#x<<"["<<(i)<<"] => "<<x[i]<<endl
#define debug_arr2(x,n,m) ____; cout<<#x<<":\n"; rep(i,0,n+1) rep(j,0,m+1) cout<<#x<<"["<<(i)<<"]["<<(j)<<"]= "<<x[i][j]<<((j==m)?"\n\n":"    ")
#define debug_set(x) ____; cout<<#x<<": \n"; rep_it(it,x) cout<<(*it)<<" "; cout<<endl
#define debug_map(x) ____; cout<<#x<<": \n"; rep_it(it,x) debug_pair(*it)
  

const int M=33;
ll tmp[M];
struct LB{
    ll a[M]; 
    LB() { mem(a,0); }
    void Clear() { mem(a,0); }
    void Copy(LB &A) { rep(i,0,M) a[i]=A.a[i]; }
    bool I(ll x,ll &y) {
        y=x;
        for(int i=M-1; ~i && x; --i) if (x>>i&1)
            if (a[i]) x^=a[i],y^=tmp[i]; else { a[i]=x,tmp[i]=y; return 1; }
        return 0;
    }
    bool Q(ll x) {
        for(int i=M-1; ~i && x; --i) if (x>>i&1)
            if (a[i]) x^=a[i]; else return 0;
        return 1;
    }
    friend void Intersect(LB &A,LB &B,LB &C) {
        LB AA; ll y,z; AA.Copy(A),C.Clear(); mem(tmp,0);
        per(i,0,M) if (B.a[i]) if (!AA.I(B.a[i],y)) C.I(y,z);
    }
    void build () {
        per(i,0,M) per(j,0,i) a[i]=min(a[i],a[i]^a[j]);
    }
    void print() { debug_arr(a,M-1); }
};
 
const int N=50005;
LB B[N<<2]; vi V[N]; ll y;
 
void push_up(int t) {
    Merge(B[t<<1],B[t<<1|1],B[t]);
}
 
void build(int t,int l,int r) {
    if (l==r) {
        for (auto x: V[l]) B[t].I(x,y);
        return;
    }
    int mid=l+r>>1;
    build(t<<1,l,mid),build(t<<1|1,mid+1,r);
    push_up(t);
}
 
bool query(int t,int l,int r,int L,int R,ll x) {
    if (L<=l && r<=R) return B[t].Q(x);
    int mid=l+r>>1; bool ret=1;
    if (L<=mid) ret&=query(t<<1,l,mid,L,R,x);
    if (R>mid) ret&=query(t<<1|1,mid+1,r,L,R,x);
    return ret;
}
 
int n,m,k,l,r; ll x;
 
int main() {
//    file_put();
      
    scanf("%d%d",&n,&m);
    rep(i,1,n+1) {
        scanf("%d",&k);
        rep(j,1,k+1) scanf("%lld",&x),V[i].pb(x);
    }
    build(1,1,n);
    rep(i,1,m+1) {
        scanf("%d%d%lld",&l,&r,&x);
        if (query(1,1,n,l,r,x)) printf("YES\n"); else printf("NO\n");
    }
      
    return 0;
}

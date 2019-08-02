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

vi v={
    0,0,0,0,0,0,0,1,0,0,1,1,1,1,
    1,0,1,1,0,1,0,1,0,0,1,0,1,0,
    0,0,1,1,0,1,0,1,1,0,0,0,1,0,
    0,1,0,0,0,1,0,0,1,1,0,0,1,0,
    0,0,0,0,0,0,0,1
};

set<ll> S;
char s[20005];

const int M=1600,len=60;
void init() {
    ll K=1,B=0,k=214013,b=2531011,p=(1ll<<29)-1,x=0;
    rep(i,0,M) K*=k,B*=k,B+=b,K&=p,B&=p;
    for (ll i=0; i<=p; i+=M) {
        ll ret=0,t=x;
        rep(j,0,len+1) {
            ret|=(ll)(t>>28&1)<<j;
            t=t*k+b,t&=p; 
        }
        S.insert(ret);
        x=x*K+B,x&=p;
    }
}

bool check0() {
    int L=strlen(s);
    for (int i=0; i+len<L; i++) {
        ll ret=0;
        rep(j,0,len+1) ret|=(ll)(s[i+j]=='1')<<j;
        if (S.count(ret)) return 1;
    } 
    return 0;
}

bool check2() {
    int now=v.size(),L=strlen(s);
    rep(i,now,L) {
        ll t=(s[i]=='1');
        rep(j,0,sz(v)) if (v[j]) t^=(s[i-j-1]=='1');
        if (t) return 0;
    } 
    return 1;
}

int T;

int main() {
//    file_put();
    
    scanf("%d",&T);
    init();
    while (T--) {
        scanf("%s",s);
        if (check0()) {
            printf("0\n");
            continue;
        }
        if (check2()) {
            printf("2\n");
            continue;
        } 
        printf("1\n");
    }
    
	return 0;
}


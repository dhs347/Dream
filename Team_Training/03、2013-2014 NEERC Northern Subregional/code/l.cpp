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
typedef long double ld;

typedef valarray<ld> va;

struct ttype{
	int z,op; va v{0,0};
	ttype(int z=0,int op=0,va v={0,0}):z(z),op(op),v(v) { }
};

ld x0,z0,x,z,dx,dz,ans=0; vector<ttype> E; int n; va X[2];

bool operator < (const ttype &a,const ttype &b) {
	return a.z>b.z;
}

ld work(int op) {
	//cin>>n>>x0>>z0;
	scanf("%d%Lf%Lf",&n,&x0,&z0);
	ld mz=z0;
	rep(i,1,n) {
		scanf("%Lf%Lf",&x,&z);
        mz=max(mz,z);
		dx=x-x0,dz=z-z0;
		if (z!=z0) {
			auto t=va{dx/dz,x0-dx/dz*z0};
			E.pb(ttype(z,op,t));
			E.pb(ttype(z0,op,-t));
		}
		z0=z,x0=x;
	}
	return mz;
}

void file_put() {
    freopen("lonely.in", "r", stdin);
    freopen("lonely.out", "w", stdout);
}

int main() {
	//std::ios::sync_with_stdio(false);
	//std::cin.tie(0);
	file_put();
	
	if (work(0)!=work(1)) {
		cout<<"Invalid plan"<<endl;
		return 0;
	}
	sort(all(E)),X[0]=X[1]={0,0};
	for (int i=0; i+1<E.size(); ++i) {
		z=E[i].z,z0=E[i+1].z,X[E[i].op]+=E[i].v;
		ld a=(ld)X[0][0]*X[1][0],b=(ld)X[0][0]*X[1][1]+(ld)X[0][1]*X[1][0],c=(ld)X[0][1]*X[1][1];
		ans+=a/3*(z*z*z-z0*z0*z0)+b/2*(z*z-z0*z0)+c*(z-z0);
	}
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(12);
	//cout<<ans<<endl;
	printf("%.12Lf\n",ans);
	
	return 0;
}

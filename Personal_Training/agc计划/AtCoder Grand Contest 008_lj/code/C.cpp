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

int a[8],b[8]; ll ret=0;

int main() {
//	file_put();
	
	rep(i,1,8) scanf("%d",&a[i]),b[i]=a[i];
	ret=a[2]*2;
	ret+=((ll)a[1]/2+a[4]/2+a[5]/2)*4;
	a[1]&=1,a[4]&=1,a[5]&=1;
	if (a[1]+a[4]+a[5]==2) {
		if (!a[1] && b[1]) ret+=2;
		if (!a[4] && b[4]) ret+=2;
		if (!a[5] && b[5]) ret+=2;
	}
	if (a[1]+a[4]+a[5]==3) ret+=6;
	printf("%lld\n",ret>>1);
	
	return 0;
}


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

const int N=2e5+5;
stack <int> S; char s[N]; int n,ans=0;

int main() {
//	file_put();
	
	scanf("%s",s),n=strlen(s);
	rep(i,0,n) if (s[i]=='S') S.push(1); else if (!S.empty() && S.top()==1) S.pop(),ans+=2; else S.push(0);
	printf("%d\n",n-ans); 
	
	return 0;
}


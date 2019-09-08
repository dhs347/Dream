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

const int N = 1010101;

char s[N], t[N];
int ns[N], nt[N], ans = 1;

void exkmp(char *s,int *z,char *t,int *p){
    int lens = strlen(s);
    int lent = strlen(t);
    p[0]=0;
    for(int i=0,x=0,y=0;i<lens;++i){
        z[i] = i <= y ? min(y-i,p[i-x]) : 0;
        while(i + z[i] < lens && z[i] < lent && s[i + z[i]] == t[z[i]]) ++z[i];
        if(y <= i + z[i]) x = i, y = i + z[i];
    }
}
void Exkmp(){
    scanf("%s%s",s,t);
    exkmp(t+1,nt+1,t,nt);
    exkmp(s,ns,t,nt);
}

void solve(int ns[], int nt[], int lenl, int lenr) {
	rep(i, 1, lenr + 1) {
		int res = i + ns[i];
		if(lenl >= i && ns[lenl + lenr + 1 - i] == i) {
			res += i + nt[i];
		} else {
			res += nt[lenl + lenr + 1 - i];
		}
		ans = max(ans, res / i);
	}
}

void solve(int l, int r) {
	if(l == r) return ;
	int mid = l + r >> 1;
	solve(l, mid), solve(mid + 1, r);
	
	int m = 0; rep(i, mid + 1, r + 1) t[m++] = s[i];
	t[m++] = '$'; rep(i, l, mid + 1) t[m++] = s[i]; t[m] = '\0';
	exkmp(t + 1, ns + 1, t, ns);
	
	reverse(t, t + m);
	exkmp(t + 1, nt + 1, t, nt);
	int x = mid - l + 1, y = r - mid;
	solve(ns, nt, x, y);
	solve(nt, ns, y, x);
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	cin >> s;
	solve(0, strlen(s) - 1);
	cout << ans << endl;
	return 0;
}


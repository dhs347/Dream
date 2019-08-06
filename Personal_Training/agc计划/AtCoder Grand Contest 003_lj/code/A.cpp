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

map<char,int> M; int n;
char st[10005];

int main() {
//    file_put();
    
    scanf("%s",st),n=strlen(st);
    rep(i,0,n) M[st[i]]++;
    if (M.count('W') && !M.count('E')) return 0*printf("No\n");
    if (M.count('E') && !M.count('W')) return 0*printf("No\n");
    if (M.count('N') && !M.count('S')) return 0*printf("No\n");
    if (M.count('S') && !M.count('N')) return 0*printf("No\n");
    printf("Yes\n");
    
	return 0;
}


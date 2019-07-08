#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define endl "\n"
#define pw(x) (1ll << (x))
#define all(a) a.begin(), a.end()
#define sz(a) (int)a.size()
#define dd(x) cout << #x << " = " << x << " "
#define de(x) cout << #x << " = " << x << endl
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;
int n;
void print(int v) {
	rep(i, 0, n) cout << (v >> i & 1); cout << endl;
}
/*
int a1[] = {2, 0, 1};
int a2[] = {3, 0, 1, 3};
int a3[] = {5, 0, 2, 3, 7, 5};
int a4[] = {8, 0, 1, 5, 7, 6, 14, 10, 11};
int a5[] = {14, 0, 16, 24, 28, 30, 22, 6, 7, 5, 13, 9, 11, 27, 19};
int a6[] = {27, 0, 32, 48, 56, 60, 44, 12, 14, 10, 42, 43, 41, 9, 25, 29, 31, 63, 55, 53, 37, 5, 7, 3, 19, 18, 22, 20};
*/
int a[][30] = {
{2, 0, 1}, 
{3, 0, 1, 3}, 
{5, 0, 2, 3, 7, 5}, 
{8, 0, 1, 5, 7, 6, 14, 10, 11}, 
{14, 0, 16, 24, 28, 30, 22, 6, 7, 5, 13, 9, 11, 27, 19},
{27, 0, 32, 48, 56, 60, 44, 12, 14, 10, 42, 43, 41, 9, 25, 29, 31, 63, 55, 53, 37, 5, 7, 3, 19, 18, 22, 20}};

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n;
	int m = n - 1;
	cout << a[m][0] << endl;
	rep(i, 1, a[m][0] + 1) print(a[m][i]);
	/*
	if(n == 1) {
	} else if(n == 2) {
	} else if(n == 3) {
	} else if(n == 4) {
	} else if(n == 5) {
	} else {
	}
	*/
	return 0;
}

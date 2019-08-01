#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <string>
#include <algorithm>

using namespace std;

const int maxn = 105;

long long mod = 998244353;

int n, m, t;

long long f[maxn][maxn][maxn];

int a[maxn];
int b[maxn];
int pa[maxn];
int pb[maxn];
bool vis[maxn];

int read(){
	int x;
	scanf("%d", &x);
	return x;
}

int dfs(int x, int l, int r){
	if(f[x][l][r] != -1)return 0;
	f[x][l][r] = 0;
	if(l == r){
		f[x][l][r] = 1;
		if(a[x] != b[l]){
			if(a[x] and b[l]){
				f[x][l][r] = 0;
			}else if(a[x] and pb[a[x]] and pb[a[x]] != l){
				f[x][l][r] = 0;
			}else if(b[l] and pa[b[l]] and pa[b[l]] != x){
				f[x][l][r] = 0;
			}
		}
		return 0;
	}
	
	if(r + 1 == l)f[x][l][r] = 1;
	if(r < l)return 0;
	
	if(a[x]){
		if(pb[a[x]]){
			if(pb[a[x]] < l or pb[a[x]] > r){
				f[x][l][r] = 0;
			}else{
				dfs(x + 1, l, pb[a[x]] - 1);
				dfs(x + pb[a[x]] - l + 1, pb[a[x]] + 1, r);
				f[x][l][r] = f[x + 1][l][pb[a[x]] - 1] * f[x + pb[a[x]] - l + 1][pb[a[x]] + 1][r] % mod;
			}
			return 0;
		}
		
		int maxx = l;
		
		for(int i=l;i<=r;i++){
			if(pa[b[i]]){
				if(pa[b[i]] < x or pa[b[i]] > x + r - l)break;
				maxx = max(maxx, l + pa[b[i]] - x);
			}
			if(b[i])continue;
			if(i < maxx)continue;
			dfs(x + 1, l, i - 1);
			dfs(x + i - l + 1, i + 1, r);
			f[x][l][r] = (f[x][l][r] + f[x + 1][l][i - 1] * f[x + i - l + 1][i + 1][r]) % mod;
		}
		return 0;
	}
	
	int maxx = l;
		
	for(int i=l;i<=r;i++){
		if(pa[b[i]]){
			if(pa[b[i]] < x or pa[b[i]] > x + r - l)break;
			maxx = max(maxx, l + pa[b[i]] - x);
		}
		if(i < maxx)continue;
		dfs(x + 1, l, i - 1);
		dfs(x + i - l + 1, i + 1, r);
		f[x][l][r] = (f[x][l][r] + f[x + 1][l][i - 1] * f[x + i - l + 1][i + 1][r]) % mod;
	}
	
	return 0;
}

int main(){
	int i, j;
	long long ans = 0;
	int T;std::cin>>T;
	while(T--) {
    	scanf("%d", &n);
    	long long cnt=0;
    	memset(pa,0,sizeof(pa));
    	memset(pb,0,sizeof(pb));
    	memset(vis,0,sizeof(vis));
    	for(i=1;i<=n;i++){
    		a[i] = read();
    		if(a[i])pa[a[i]] = i;
    		vis[a[i]] = true;
    	}
    	
    	for(i=1;i<=n;i++){
    		b[i] = read();
    		if(b[i])pb[b[i]] = i;
    		vis[b[i]] = true;
    	}
    	
    	memset(f, -1, sizeof(f));
    	
    	dfs(1, 1, n);
    	ans = f[1][1][n];
    	
    	for(i=1;i<=n;i++){
    		if(!vis[i])cnt++;
    	}
    	
    	for(i=1;i<=cnt;i++){
    		ans = ans * i % mod;
    	}
    	
    	printf("%lld\n", ans);
	}
	return 0;
}

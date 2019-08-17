#pragma GCC optimize(3)
#include<bits/stdc++.h>
using namespace std;
const char s1[]="COFFEE",s2[]="CHICKEN";
long long Len[10000];
__int128_t AAA;
int n;
char DFS(int x,long long k){
	if (x==1){
		return s1[k-1];
	}
	if (x==2){
		return s2[k-1];
	}
	if (Len[x-2]>=k) return DFS(x-2,k);
	else return DFS(x-1,k-Len[x-2]);
}
void print(int x,long long k){
	if (x<n && k>Len[x]) return;
	x=min(x,n-1);
	putchar(DFS(x,k));
}
int main(){
	AAA=1111111;
	Len[1]=6;
	Len[2]=7;
	for (n=3;Len[n-1]<=1000000000010;++n)
		Len[n]=Len[n-1]+Len[n-2];
	int T; scanf("%d",&T);
	while (T--){
		int x; long long k;
		scanf("%d%lld",&x,&k);
		for (long long w=k;w<=k+9;++w)
			print(x,w);
		puts("");
	}
}

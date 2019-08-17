#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define div first
#define rem second
using namespace std;
using LLL=__int128_t;
using PLLL=pair<LLL,LLL>;
using VPLLL=vector<PLLL>;
const int maxn=111;
VPLLL s; int n; long long m;
LLL exgcd(LLL a,LLL b,LLL &x,LLL &y){
	if (b==0) return x=1,y=0,a;
	LLL t=exgcd(b,a%b,y,x);
	y-=a/b*x;
	return t;
}
void merge(PLLL a,PLLL b,PLLL &re){
	LLL x,y,g=exgcd(a.div,b.div,x,y);
	if ((a.rem-b.rem)%g!=0) assert(false);
	LLL m=a.div/g*b.div;
	x=-x%m*((a.rem-b.rem)/g)%m;
	re={m,((x*a.div+a.rem)%m+m)%m};
}
LLL CRT(VPLLL s){
	PLLL re={1,0};
	for (auto i:s){
		merge(re,i,re);
		if (re.first+re.second>m) break;
	}
	return re.rem;
}
int main(){
	scanf("%d%lld",&n,&m);
	for (int i=1;i<=n;++i){
		int x,y;
		scanf("%d%d",&x,&y);
		s.emplace_back(x,y);
	}
	for (int i=0;i<n;++i) for (int j=i+1;j<n;++j){
		LLL G=__gcd(s[i].div,s[j].div);
		if ((s[i].rem-s[j].rem)%G!=0){
			puts("he was definitely lying");
			return 0;
		}
	}
	
	
	LLL ans=CRT(s);
	bool ok=0;
	if (ans<=m){
		ok=1;
		for (int i=0;i<n;++i)
			if (ans%s[i].div!=s[i].rem) ok=0;
	}
	if (ok) printf("%lld\n",(long long)ans);
	else puts("he was probably lying");
}

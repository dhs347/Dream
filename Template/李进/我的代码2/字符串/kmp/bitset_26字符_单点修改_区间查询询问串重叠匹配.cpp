bitset<N> B[26],ans,all;
int n,T,op,l,r,m;
char s[N],t[N];

int main() {
    scanf("%s",s+1),n=strlen(s+1);
    rep(i,1,n) B[s[i]-'a'][i]=1,all[i]=1;
    scanf("%d",&T);
    while (T--) {
    	scanf("%d",&op);
    	if (op==1) {
    		scanf("%d%s",&l,t);
    		B[s[l]-'a'][l]=0,B[t[0]-'a'][l]=1,s[l]=t[0];
		}
		if (op==2) {
			scanf("%d%d%s",&l,&r,t),m=strlen(t),r=r-m+1;
			ans=all;
			rep(i,0,m-1) ans&=B[t[i]-'a']>>i;
			ans>>=l,ans<<=N-(r-l+1);
			printf("%d\n",ans.count());
		}
	}
	
    return 0;
}

//6s,256MB,询问串长度之和<=10^5,|s|<=10^5,该程序跑2s

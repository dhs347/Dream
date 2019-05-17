void kmp_pre(char st[],int m,int nxt[]) {
	int i=0,j=nxt[0]=-1;
	while (i<m) {
		while (j!=-1 && st[i]!=st[j]) j=nxt[j];
		nxt[++i]=++j;
	}
}

int f[N],g[N],nxt[N],n,m,tt;
char s[N],t[N];

bool check(int k) {
	rep(i,0,m-1) if (s[k-i]!=t[m-1-i] && s[k-i]!='?') return 0;
	return 1;
}

int main() {
    scanf("%s%s",s,t);
    n=strlen(s),m=strlen(t);
    if (m>n) return 0*printf("0\n");
    kmp_pre(t,m,nxt);
    rep(i,m-1,n-1) {
    	if (check(i)) {
    		f[i]=(i==m-1)?0:g[i-m],tt=max(1,2*m-i-1);
    		for (int j=m; nxt[j]>=tt; j=nxt[j]) f[i]=max(f[i],f[i-m+nxt[j]]);
    		f[i]++;
		}
		g[i]=max(g[i-1],f[i]);
	}
	printf("%d\n",g[n-1]);
	
    return 0;
}


//codeforces 808G

void kmp_pre(char st[],int m,int nxt[]) {
	int i=0,j=nxt[0]=-1;
	while (i<m) {
		while (j!=-1 && st[i]!=st[j]) j=nxt[j];
		nxt[++i]=++j;
	}
}

int kmp_count(char st[],int m,char s[],int n,int nxt[]) {
	int i=0,j=0,ans=0;
	while(i<n) {
		while(j!=-1 && s[i]!=st[j])j=nxt[j]; i++,j++;
		if(j>=m) { ans++; j=nxt[j]; }
	}
	return ans;
}

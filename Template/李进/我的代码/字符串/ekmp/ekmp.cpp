void ekmp_pre(char st[],int m,int nxt[]) {
	nxt[0]=m; int j=0,k=1;
	while(j+1<m && st[j]==st[j+1])j++; nxt[1]=j;
	for(int i=2; i<m; i++) {
		int p=nxt[k]+k-1,L=nxt[i-k];
		if(i+L<p+1) nxt[i]=L; else {
			j=max(0,p-i+1);
			while(i+j<m && st[i+j]==st[j])j++;
			nxt[i]=j,k=i;
		}
	}
}

void ekmp(char st[],int m,char s[],int n,int nxt[],int ext[]) {
	int j=0,k=0;
	while(j<n && j<m && st[j]==s[j])j++;
	ext[0]=j;
	for(int i=1; i<n; i++) {
		int p=ext[k]+k-1,L=nxt[i-k];
		if(i+L<p+1) ext[i]=L; else {
			j=max(0,p-i+1);
			while (i+j<n && j<m && s[i+j]==st[j]) j++;
			ext[i]=j,k=i;
		}
	}
} 

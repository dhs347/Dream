struct qtype{ int l,r,id; };
int n,q,B,a[N],b[N],cnt=0,tot=0,num[N],s[N],l=1,r=0,now=0,ans[N],t;
map <int,int> M; qtype C[N],Q[N];
inline bool cmp(const qtype &p,const qtype &q) {
	return p.l/B<q.l/B || p.l/B==q.l/B && p.r/B<q.r/B || p.l/B==q.l/B && p.r/B==q.r/B && p.id<q.id;
}
inline void I(int x,int y=1) { s[num[x]]--,s[num[x]+=y]++; }
inline void U(int x,int y) { if (l<=x && x<=r) I(a[x],-1),I(y,1); a[x]=y; }

int main() {
    scanf("%d%d",&n,&q),B=ceil(pow(n,2.0/3));
    rep(i,1,n) scanf("%d",&a[i]),b[i]=a[i]=(M[a[i]]?M[a[i]]:M[a[i]]=++cnt);
    rep(i,1,q) {
    	scanf("%d%d%d",&C[i].id,&C[i].l,&C[i].r);
    	if (C[i].id==1) Q[++tot]=qtype{C[i].l,C[i].r,i}; else 
			C[i].r=(M[C[i].r]?M[C[i].r]:M[C[i].r]=++cnt);
	}
	sort(Q+1,Q+tot+1,cmp);
	rep(i,1,tot) {
		while (r<Q[i].r) I(a[++r]); while (l>Q[i].l) I(a[--l]);
		while (l<Q[i].l) I(a[l++],-1); while (r>Q[i].r) I(a[r--],-1);
		if (now>Q[i].id) { rep(j,1,n) U(j,b[j]); now=0; }
		while (now<Q[i].id) if (C[++now].id==2) U(C[now].l,C[now].r);
		t=1; while (s[t]) ++t; ans[Q[i].id]=t;
	}
	rep(i,1,q) if (ans[i]) printf("%d\n",ans[i]);
	
    return 0;
}

/*

题目：CF_940F
单点修改，动态求区间每个数i出现次数的数组c[i]的mex
注意所有数为正，c[]下标从0开始，所以答案必不为0
分块大小B=n^(2/3),排序依据:(l/B,r/B,t),t为修改的操作序号，查询为0
时间复杂度：O(n^(5/3))

*/

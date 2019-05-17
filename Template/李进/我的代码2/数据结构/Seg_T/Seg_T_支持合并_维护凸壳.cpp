struct Seg_T {
	static const int L=-100000,R=100000,N=4001005; ll K[N],B[N]; int cnt,ls[N],rs[N];
	void Init() { cnt=0; } 
	int new_node(ll k=0,ll b=0) { K[++cnt]=k,B[cnt]=b,ls[cnt]=0,rs[cnt]=0; return cnt; }
	void I(int &t,int l,int r,ll k,ll b) {
		if (!t) { t=new_node(k,b); return; }
		if (k*l+b<K[t]*l+B[t]) swap(K[t],k),swap(B[t],b);
		if (l==r) return; int mid=(l+r)/2;
		if (k*mid+b<K[t]*mid+B[t]) swap(K[t],k),swap(B[t],b),I(ls[t],l,mid,k,b); else
		if (k*r+b<K[t]*r+B[t]) I(rs[t],mid+1,r,k,b);
	}
	void M(int &t1,int t2,int l,int r) {
		if (!t1 || !t2) { t1+=t2; return; } int mid=(l+r)/2;
		M(ls[t1],ls[t2],l,mid),M(rs[t1],rs[t2],mid+1,r),I(t1,l,r,K[t2],B[t2]);
	}
	ll Q(int t,int l,int r,ll x) {
		if (!t) return 1e18; ll ans=K[t]*x+B[t]; 
		if (l==r) return ans; int mid=(l+r)/2;
		if (x<=mid) return min(ans,Q(ls[t],l,mid,x)); return min(ans,Q(rs[t],mid+1,r,x));
	}
};

Seg_T T; int rt[N];
int n,a[N],b[N],x,y; vector <int> V[N]; ll ans[N];

void dfs(int x,int p) {
	rep_it(it,V[x]) {
		int y=*it; if (y==p) continue;
		dfs(y,x),T.M(rt[x],rt[y],T.L,T.R);
	}
	ans[x]=rt[x]?T.Q(rt[x],T.L,T.R,a[x]):0;
	T.I(rt[x],T.L,T.R,b[x],ans[x]);
}

int main() {
    //file_put();
	
	scanf("%d",&n),T.Init();
	rep(i,1,n) scanf("%d",&a[i]);
	rep(i,1,n) scanf("%d",&b[i]);
	rep(i,1,n-1) scanf("%d%d",&x,&y),V[x].pb(y),V[y].pb(x);
	dfs(1,0);
	rep(i,1,n) printf("%I64d%c",ans[i]," \n"[i==n]); printf("\n"); 
	
    return 0;
}



/*

【题意】codeforces 932F
给一棵树，节点带双权a,b，从x到y一步代价a[x]*b[y]
求每个节点到任意叶子的最小代价(可负)

【算法】dp[i]=min{dp[j]+a[i]*b[j]},j为i的子孙
子树内一点j可表示一直线y=b[j]*x+dp[j],子树构成直线空间
欲使a[i]带入空间内某直线得到最小纵坐标，线段树维护上凸壳
线段树上一节点代表区间[l,r]的一段凸壳，可看成由左右子节点代表的凸壳的并
再并上自己的信息(本节点相当于一条附加直线，标记永久化)
凸壳的合并，可以任意合并，先递归左右子节点合并，然后本身标记合并
关键在于维护凸壳，添加一条直线l，与线段树上此段凸壳的标记直线比较
swap使得待插入直线为左端点带入纵坐标大者，从斜率为-oo到+oo依次考虑带插入直线的情况
可分为三种：中心点小于标记，右端点小于标记，两端点均大
思想上注意凸壳的本质是由无序直线并成，所以带永久化标记的一段凸壳插入一条新的直线
本质上等价于交换标记和待插入直线，新凸壳插入原标记直线，凸壳的本质显示出维护的灵活性

【注意点】
1.此基本模板，维护上凸壳（自变量带入要求纵坐标最小），因此询问空树应该返回+oo
2.注意此类合并式线段树，每个函数都应该讨论空树情况
3.注意总范围[L,R]如有负的，mid里面最好不要用>>1
4.禁用宏定义min,max
5.注意N为线段树节点数目，空间要开够


*/
struct D{ int x,y,len; }; struct C{ int c,len; };
struct D{ int x,y,len; }; struct C{ int c,len; };
typedef vector<pair<D,C> > VPDC;
struct Tree{
	static const int N=100005; vi V[N]; bool v[N]; int n,f[N],len,now;
	void Init(int _n) { n=_n; rep(i,0,n+1) V[i].clear(); mem(v,0),mem(f,0); }
	void I(int x,int y) { V[x].pb(y),V[y].pb(x); }
	void dfs(int x,int p,int d,int op) {
		if (op) f[x]=p; else v[x]=1;
		if (d>=len) len=d,now=x;
		for (auto y:V[x]) if (y!=p) dfs(y,x,d+1,op);
	}
	C find_center() {
		int x=now,k=(len+1)>>1,kk=k;
		while (k--) x=f[x]; return C{x,kk};
	}
	VPDC solve() {
		VPDC ans; int xx,yy;
		rep(x,1,n+1) if (!v[x]) {
			len=0,dfs(now=x,0,0,0),xx=now;
			dfs(now,0,0,1),yy=now,ans.pb(mp(D{xx,yy,len},find_center()));
		}
		return ans;
	}
};


/*
*
* 森林中求每棵树的中心编号，并且构造出一条直径
*
* 直径是指最长链，中心是指以此为根，树高最小
*
* 注：
*
* 1. 注意记得初始化 T.Init(n) ,里面带清空
*
* 2.D 是直径结构体， x 和 y 是端点， len 是直径长度
*
* 3.C 是中心结构体， c 是中心点编号， len 是以中心 c 为根，该子树树高 ( 根深度是 0) ；此树高 = 直径长 /2 上取整
*
* 4. 用户调用 solve() ，返回一个 VPDC 表示所有子树中心和直径的信息集合，该 vector 的 size 是森林中树的个数
*
* 5. 该代码中， dfs 里 len 表示当前最长路长度， now 为最远走到的结点编号；
*
* f[] 用于从最远点回溯寻找中心，回溯时打印途径结点，可以构造完整直径路径
*
*/

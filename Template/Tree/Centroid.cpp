// id starts from 1
namespace Centriod {
    const int N = ::N;
    bool vis[N];
	int sz[N];
    void dfssz(int c,int fa,int Sz,int &rt){
        sz[c] = 1;
        for(auto t : g[c]) if(!vis[t]&&t!=fa) dfssz(t,c,Sz,rt) , sz[c]+=sz[t];
        if(!rt && sz[c]*2>Sz) rt=c;
    }
    void dfs(int c){
        int rt=0;dfssz(c,0,0,rt);dfssz(c,0,sz[c],rt=0);
        vis[rt] = true;
        /*
         * 注意计算以 rt 为起点的路径、只包含 rt 的路径
		 * 注意 v != vis[rt] 
		 */
		// 点分树的写法：先把点分树建出来，再像点分治那样维护
        for(auto t : g[rt]) if(!vis[t]) dfs(t);
    }
};

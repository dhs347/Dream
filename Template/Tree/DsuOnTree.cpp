// id starts with 1
namespace QuerySubtree{
    static const int N = ::N;
    int sz[N] , wson[N] , par[N];
    void dfs(int c,int fa,vi g[]){
        sz[c]=1;par[c]=fa;int &s=wson[c]=0;
        for(auto t:g[c]) if(t!=fa)
            dfs(t,c,g),sz[c]+=sz[t],(sz[t]>=sz[s])&&(s=t);
    }
  	vi nd;
    void solve(int c,int fa,bool iswson,vi g[]){
        for(auto t : g[c]) if(t != wson[c] && t != fa) solve(t , c , false , g);
        if(wson[c]) solve(wson[c] , c , true , g);
        for(auto t : g[c]) if(t != wson[c] && t != fa) {
            // 将该子树的信息加入
        }
      	// 将当前节点的信息加入
      	// 查询
        if(!iswson) {
        	// 删除整棵子树的信息 nd.clear()
        }
    }
    void solve(vi g[]){
        dfs(1,0,g);
        solve(1,0,false,g); // 如果输入是单组数据，改成 true 可以优化
    }
}

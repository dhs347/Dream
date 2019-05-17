#2-SAT
//时间最优
const int max_node = 10000;
const int max_edge = 10000;
struct Edge
{
    int from, to, ne;
}ed[max_edge];    // 原图
int head[max_node], es;
vector<int> G[max_node];    // 缩点后新图
int in[max_node];    // 新图block的入度 
int low[max_node], dfn[max_node];    // 通过子女节点所能到达的最低深度优先数  深度优先数
int dfs_clock;    // 时间戳
int block[max_node], block_cnt;   // block[i]表示i属于哪个block  block_cnt是block计数器
stack<int> S;    // 存储当前block的点
bool instack[max_node];    // 判断点是否在栈里面
int color[max_node];    // 染色
int fp[max_node];    // 建立对应block编号的映射
int print[max_node],pr;    // 输出可行解

void init(){
    pr=0;
    es = 0;
    memset(head, -1, sizeof(head)); 
}
void addedge(int from, int to){
    ed[es].from = from;
    ed[es].to = to;
    ed[es].ne = head[from];
    head[from] = es++;
} 
void getMap(){    // 建图

} 
void tarjan(int u, int fa){    // 求block
    int v;
    low[u] = dfn[u] = ++dfs_clock;
    S.push(u);
    instack[u] = true;
    for(int i = head[u]; i != -1; i = ed[i].ne){
        v = ed[i].to;
        if(!dfn[v]){
            tarjan(v, u);
            low[u] = min(low[u], low[v]);
        }
        else if(instack[v])low[u] = min(low[u], dfn[v]);
    }
    if(low[u] == dfn[u]){
        block_cnt++;
        while(true){
            v = S.top(); S.pop();
            instack[v] = false;
            block[v] = block_cnt;
            if(v == u)break;
        }
    }
}
void find_cut(int l, int r){
    memset(low, 0, sizeof(low));
    memset(dfn, 0, sizeof(dfn));
    memset(block, 0, sizeof(block));
    memset(instack, false, sizeof(instack));
    dfs_clock = block_cnt = 0;
    for(int i = l; i <= r; i++)
    if(!dfn[i])tarjan(i, -1);
}
void suodian(){    // 缩点 + 反向建图
    for(int i = 1; i <= block_cnt; i++)G[i].clear(), in[i] = 0;
    for(int i = 0; i < es; i++){
        int u = block[ed[i].from];
        int v = block[ed[i].to];
        if(u != v)G[v].push_back(u), in[u]++;    // 反向建图
    } 
}
void toposort(){    // 拓扑排序 + 染色
    queue<int> Q;
    memset(color, 0, sizeof(color));
    for(int i = 1; i <= block_cnt; i++)if(in[i] == 0) Q.push(i);
    while(!Q.empty()){
        int u = Q.front();
        Q.pop();
        if(color[u] == 0){    // 没有颜色
            color[u] = 1;    // 染色
            color[fp[u]] = 2;
        }
        for(int i = 0; i < G[u].size(); i++){
            int v = G[u][i];
            if(--in[v] == 0)Q.push(v);    // 入度减一
        }
    }
}
bool solve(int ns){
    memset(fp, 0, sizeof(fp));
    for(int i = 1; i <= ns; i++){
        if(block[2*i] == block[2*i + 1]){
            return false;
        }
        else{
            fp[block[2*i]] = block[2*i + 1];
            fp[block[2*i + 1]] = block[2*i];
        }
    }
    suodian();    // 缩点
    toposort();    // 拓扑排序 + 染色
    for(int i = 1; i <= ns; i++){
        if(color[block[2*i]] == 1){
            print[pr++] = i;
        }
    }
    return true;
}

int n;
int main()
{
    while(~scanf("%d",&n))
    {
        init();//初始化
        getMap();//建图
        find_cut(1, 2*n);//找block
        solve(n);//判断是否存在可行解 或者 输出一组可行解
    }
    return 0;
}

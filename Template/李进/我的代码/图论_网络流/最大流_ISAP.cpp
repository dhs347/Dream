#网络流 ISAP

const int max_node = 200;
const int max_edge = 6009;
int n;    // 点数
int s;    // 源点
int t;    // 汇点
int pre[max_node];    // 可增广路上的上一条弧的编号
int cnt[max_node];    // 和 t 的最短距离等于 i 的节点数量
int cur[max_node];    // 当前弧下标
int dis[max_node];    // 残量网络中节点 i 到汇点 t 的最短距离
bool vis[max_node];

// 建第 i 条边时, 2*i为正向边, 2*i^1为反向边, 反向边的 cap 为 0
// 无向图两条边的 cap 相同
struct Edge{
    int from;
    int to;
    int flow;
    int cap;
    int ne;
}ed[max_edge*2];
int es;
int head[max_node];

void add(int from, int to, int cap){
    ed[es].from = from;
    ed[es].to = to;
    ed[es].flow = 0;
    ed[es].cap = cap;
    ed[es].ne = head[from];
    head[from] = es++;
}

// 预处理, 反向 BFS 构造 dis 数组
bool bfs()
{
    memset(vis, 0, sizeof(vis));
    queue<int> Q;
    Q.push(t);
    vis[t] = 1;
    dis[t] = 0;
    while(!Q.empty()){
        int u = Q.front();
        Q.pop();
        for(int i = head[u]; i != -1; i = ed[i].ne){
            int from = ed[i^1].from;
            int cap = ed[i^1].cap;
            int flow = ed[i^1].flow;
            if(!vis[from] && cap > flow){
                vis[from] = true;
                dis[from] = dis[u] + 1;
                Q.push(from);
            }
        }
    }
    return vis[s];
}

// 增广
int augment()
{
    int u = t, df = INF;
    // 从汇点到源点通过 pre 追踪增广路径, df 为一路上最小的残量
    while(u != s){
        df = min(df, ed[pre[u]].cap - ed[pre[u]].flow);
        u = ed[pre[u]].from;
    }
    u = t;
    // 从汇点到源点更新流量
    while(u != s){
        ed[pre[u]].flow += df;
        ed[pre[u]^1].flow -= df;
        u = ed[pre[u]].from;
    }
    return df;
}

int max_flow()
{
    int mflow = 0;
    bfs();
    memset(cnt, 0, sizeof(cnt));
    for(int i = 0; i < n; i++){
        cnt[dis[i]]++;
        cur[i]=head[i];
    }
    int u = s;
    while(dis[s] < n){
        if (u == t){
            mflow += augment();
            u = s;
        }
        bool tag = false;
        for(int i = cur[u]; i != -1; i = ed[i].ne){
            int to = ed[i].to;
            int cap = ed[i].cap;
            int flow = ed[i].flow;
            if(cap > flow && dis[u] == dis[to] + 1){
                tag = true;
                pre[to] = i;
                cur[u] = i;
                u = to;
                break;
            }
        }
        // retreat
        if(!tag){
            int mi = n - 1;
            for(int i = head[u]; i != -1; i = ed[i].ne){
                int to = ed[i].to;
                int cap = ed[i].cap;
                int flow = ed[i].flow;
                if(cap > flow){
                    mi = min(mi, dis[to]);
                }
            }
            if(--cnt[dis[u]] == 0)break;    // gap 优化
            dis[u] = mi + 1;
            cnt[dis[u]]++;
            cur[u] = head[u];
            if(u != s)u = ed[pre[u]].from;
        }
    }
    return mflow;
}

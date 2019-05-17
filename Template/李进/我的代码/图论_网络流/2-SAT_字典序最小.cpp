#2-SAT

// 最小字典序
// 注意 max_node max_edge 要修改
const int max_node 100000
const int max_edge 100000
// 注意n是拆点后的大小 即 n <<= 1 N为点数(注意要翻倍) M为边数 i&1=0为i真 i&1=1为i假
struct Edge{
    int to, ne;
}ed[max_edge];
int head[max_node], es;
void addedge(int from, int to){
    ed[es].to = to;
    ed[es].ne = head[from];
    head[from] = es++;
}

bool mark[max_node];    // 最小字典序可行解, i = 2, i += 2
int stk[max_node], top;
void init(){
    es = 0;
    memset(head, -1, sizeof(head));
    memset(mark, 0, sizeof(mark));
}

bool dfs(int x){
    if(mark[x^1])return false;    // 一定是拆点的点先判断
    if(mark[x])return true;
    mark[x] = true;
    stk[top++] = x;
    for(int i = head[x]; i != -1; i = ed[i].ne){
        if(!dfs(ed[i].to))return false;
    }
    return true;
}

bool solve(int n){
    for(int i = 0; i < n; i+=2){
        if(!mark[i] && !mark[i^1]){
            top = 0;
            if(!dfs(i)){ 
                while(top)mark[stk[--top]] = false;
                if(!dfs(i^1))return false;
            }
        }
    }
    return true;
}

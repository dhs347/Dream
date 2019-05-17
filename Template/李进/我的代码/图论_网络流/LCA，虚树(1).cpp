const int N=1000;
const int M=1000;
struct edge{
    int v, w, next;
}edge[2*M];
int es;    //es=0
int head[N];    //mms(head, -1)
int deep[N];    //mms(deep, 1)
int dis[N];    //mms(dis, 0)
int root[N][20];    //mms(root, -1)
int order[N];    //记录每个点的访问次序
int ind = 0;

//LCA

void dfs(int u){
    order[s] = ++ind;
    for(int i = head[u]; i != -1; i = edge.next){
        int v = edge[i].v;
        if(v == root[u][0])continue;
        deep[v] = deep[u] + 1;
        dis[v] = dis[u] + edge[i].w;
        root[to][0] = u;
        dfs(v);
    }
}

void init(){
    for(int j = 1; (1<<j) <= n; j++){
        for(int i = 1; i <= n; i++){
            if(root[i][j-1] != -1)root[i][j] = root[root[i][j-1]][j-1];
        }
    }
}

int lca(int a, int b){
    if(deep[a] > deep[b])swap(a, b);    //让b在下面
    int f = deep[b] - deep[a];    //f是高度差
    for(int i = 0; (1<<i) <= f; i++)
        if(((1<<i)) & f)
            b = deep[b][i]; 
    if(a != b){
        //从最大的祖先开始，判断a，b的祖先是否相同
        for(int i = ((int)log2(n)); i >= 0; i--){
            //如果不相同，a和b同时向上移动2^j
            if(root[a][i] != root[b][i]){
                a = root[a][i];
                b = root[b][i];
            }
        }
        a = root[a][0];
    }
    return a;
}

//虚树

int stk[N], top;
//标示虚树上的点是否是无用点
int mark[N];
vector<int> tree[N];    //存边
vector<int> treew[N];    //存权
void tree_add(int u, int v, int w){
    tree[u].push_back(v);
    tree[v].push_back(u);
    treew[u].push_back(w);
    treew[v].push_back(w);
}

//使用前lca初始化
//返回虚树根节点,虚树的边默认为原树上两点的距离

//传入按dfs序数组，以及长度(要自己写按dfs排序的数组)
int build_vtree(int vp[], int vn){
    if(vn == 0)return -1;
    top = 0;
    stk[top++] = vp[0];
    tree[vp[0]].clear();
    treew[vp[0]].clear();
    mark[vp[0]] = 1;
    for(int i = 1; i < vn; i++){
        int v = vp[i];
        int plca = lca(stk[top-1], v);    //最近公共祖先
        if(plca == stk[top-1]);    //不处理
        else{
            int pos = top-1;
            while(pos >= 0 && deep[stk[pos]] > deep[plca]){
                pos--;
            }
            pos++;
            for(int j = pos; j < top-1; j++){
                tree_add(stk[j], stk[j+1], deep[stk[j+1]] - deep[stk[j]]);
            }
            int prepos = stk[pos];
            if(pos == 0){
                tree[plca].clear();
                treew[plca].clear();
                stk[0] = plca,top=1;
                mark[plca] = 0;
            }
            else if(stk[pos-1] != plca){
                tree[plca].clear();
                treew[plca].clear();
                stk[pos] = plca;
                top = pos + 1;
                mark[plca] = 0;
            }
            else top = pos;
            tree_add(prepos, plca, deep[prepos] - deep[plca]);
        }
        tree[v].clear();
        treew[v].clear();
        stk[top++] = v;
        mark[v] = 1;
    }
    for(int i = 0; i < top - 1; i++){
        tree_add(stk[i], stk[i+1], deep[stk[i+1]] - deep[stk[i]]);
    }
    return vp[0];
}

//////////////--先排序，再建虚树--//////////////////////
struct vnode{
    int order, id;
}vg[N];
int vcmp(vnode t1, vnode t2){
    return t1.order < t2.order;
}
//传入未排序的数组，以及长度
int vsort(int vp[], int vn){
    for(int i = 0; i < vn; i++){
        vg[i].id = vp[i];
        vg[i].order = order[vp[i]];
    }
    sort(vg, vg + vn, vcmp);
    for(int i = 0; i < vn; i++)vp[i] = vg[i].id;
    return build_vtree(vp, vn);
}
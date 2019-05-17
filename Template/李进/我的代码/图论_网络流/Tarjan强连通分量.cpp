struct edge{
    int v,w,next;
    //是否为桥
    bool sign;
}edge[1000];
int es;
int head[1000]; 
int dfn[1001],low[1001],vis[1001],stk[1001],color[1001];
int dfs_num,ttop,col_num;
void Tarjan(int x){
    dfn[x]=++dfs_num;
    low[x]=dfs_num;
    //是否在栈中
    vis[x]=true;
    stk[++ttop]=x;
    for(int i=head[x];i!=-1;i=edge[i].next){
        int temp=edge[i].v;
        if(!dfn[temp]){
            Tarjan(temp);
            low[x]=min(low[x],low[temp]);
            if(dfn[x]<low[temp]){
                //为割桥
                edge[i].sign=1;
            }
        }
        else if (vis[temp])low[x]=min(low[x],dfn[temp]);
    }
    //构成强连通分量
    if(dfn[x]==low[x]){
        vis[x]=false;
        //染色
        color[x]=++col_num;
        //清空
        while(stk[ttop]!=x){
            color[stk[ttop]]=col_num;
            vis[stk[ttop--]]=false;
        }
        ttop--;
    }
}
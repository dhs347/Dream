vi G[505];
int check[505];
int matching[505];
int num_left;
queue<int> Q;
int pre[505];
int Hungarian(){
    int ans = 0;
    memset(matching,-1,sizeof(matching));
    memset(check, -1, sizeof(check));
    for(int i=1;i<=num_left;++i){
        if(matching[i]==-1){
            while(!Q.empty())Q.pop();
            Q.push(i);
            //设i为路径起点
            pre[i]=-1;
            //尚未找到增广路
            bool flag=false;
            while(!Q.empty()&&!flag){
                int u=Q.front();
                for(int ix=0;ix<G[u].size()&&!flag;++ix){
                    int v=G[u][ix];
                    if(check[v]!=i){
                        check[v]=i;
                        Q.push(matching[v]);
                        //此点为匹配点
                        if(matching[v]>=0){
                            pre[matching[v]]=u;
                        }
                        //找到未匹配点，交替路变为增广路
                        else{
                            flag=true;
                            int d=u,e=v;
                            while(d!=-1){
                                int t=matching[d];
                                matching[d]=e;
                                matching[e]=d;
                                d=pre[d];
                                e=t;
                            }
                        }
                    }
                }
                Q.pop();
            }
            if(matching[i]!=-1)++ans;
        }
    }
    return ans;
}
# 最小割

int ed[502][502];
int N,M;
bool combine[502];
int minC=INF;

void search(int &s,int &t){
    bool vis[502];
    int w[502];
    memset(vis,0,sizeof(vis));
    memset(w,0,sizeof(w));
    int tmpj=1000;
    for(int i=0;i<N;i++){
        int max=-INF;
        for(int j=0;j<N;j++){
            if(!vis[j]&&!combine[j]&&max<w[j]){
                max=w[j];
                tmpj=j;
            }
        }
        if(t==tmpj){minC=w[t];return;}
        vis[tmpj]=1;
        s=t,t=tmpj;
        for(int j=0;j<N;j++){
            if(!vis[j]&&!combine[j])
                w[j]+=ed[t][j];
        }
    }
    minC=w[t];
}

int mincut(){
    int ans=INF;
    int s,t;
    memset(combine,0,sizeof(combine));
    for(int i=0;i<N-1;i++){
        s=t=-1;
        search(s,t);
        combine[t]=true;
        ans=ans>minC?minC:ans;
        for(int j=0;j<N;j++){
            ed[s][j]+=ed[t][j];
            ed[j][s]+=ed[j][t];
        }
    }
    return ans;
}
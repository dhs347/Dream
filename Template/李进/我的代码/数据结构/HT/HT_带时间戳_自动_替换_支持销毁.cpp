const int HT_M=1001005;
struct HT{//时间戳hash值计数
    int q[HT_M],now[HT_M],t; HT(){ mem(now,0); t=0; }
    void init(){ t++; }
    void I(int x) { if (now[x]==t) q[x]++; else q[x]=1,now[x]=t; }
    int Q(int y) { if (now[y]!=t) return 0; else return q[y]; }
};

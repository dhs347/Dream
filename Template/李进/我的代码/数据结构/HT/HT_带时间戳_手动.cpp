const int HT_M=1001005;
struct HT{//时间戳hash求最小值(维护取同一值的下标最值)，s[x]为x的权函数
    int q[HT_M],now[HT_M]; int *s;
    void init(int *_s){ mem(q,0); mem(now,0); s=_s; }
    void I(int x,int t) { if (now[s[x]]==t) q[s[x]]=min(q[s[x]],x); else q[s[x]]=x,now[s[x]]=t; }
    int Q(int y,int t) { if (now[y]!=t) return -1; else return q[y]; }
};

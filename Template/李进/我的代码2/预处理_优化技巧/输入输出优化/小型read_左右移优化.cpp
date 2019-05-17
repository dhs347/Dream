template<typename T> inline void read(R T &x){
    static int ch; static bool flag;
    for(flag=false, ch=getchar(); ch<'0'||ch>'9'; ch=getchar()) flag |= ch=='-';
    for(x=0; ch>='0'&&ch<='9'; ch=getchar()) x = (x<<1) + (x<<3) + ch - '0';
    x = flag ? -x : x;
}

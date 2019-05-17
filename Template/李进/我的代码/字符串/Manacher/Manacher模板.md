- Manacher
  - 模板
  - Mp[i]表示以i为中心的最长回文串长度/2+1。
  - rep(i,0,2*n+2) ans=max(ans,Mp[i]-1);
```
struct Manacher {
    int Ma[N*2],Mp[N*2],ans,POS=0,l;
    void  manacher(char s[]) {
        int slen=strlen(s);
        l=0;
        Ma[l++]='$';
        Ma[l++]='#';
        rep(i,0,slen) {
            Ma[l++]=s[i];
            Ma[l++]='#';
        }
        Ma[l]=0;
        int mx=0,id=0;
        rep(i,0,l) {
            Mp[i]=mx>i?min(Mp[2*id-i],mx-i):1;
            while(Ma[i+Mp[i]]==Ma[i-Mp[i]]) ++Mp[i];
            if(i+Mp[i]>mx) {
                mx=i+Mp[i];
                id=i;
            }
        }
    }
    int get_len() {//ans为最长回文串长度
        ans=0;
        rep(i,0,l) {
            if(Mp[i]-1>ans) {
                ans=Mp[i]-1;
                POS=i;
            }
        }
    }
    void print(char s[]) {//输出第一个最长的回文串
        int st=(POS-ans)/2,ed=st+ans;
        rep(i,st,ed) printf("%c",s[i]);
        puts("");
    }
};
```
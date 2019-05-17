```
struct Trie {
    static const int N=100055,M=26;
    int nxt[N][M],fail[N],ed[N],rt,L;
    void init() {
        L=0;
        rt=newnode();
    }
    int newnode() {
        ed[L]=0;
        fill_n(nxt[L],M,-1);
        return L++;
    }
    void insert(char s[]) {
        int p=rt;
        int n=strlen(s);
        for(int i=0;i<n;++i) {
            int c=s[i]-'a';
            if(nxt[p][c]==-1) nxt[p][c]=newnode();
            p=nxt[p][c];
        }
        //...
    }
    void build() {
        queue<int> q;
        fail[rt]=rt;
        rep(i,0,M) {
            if(nxt[rt][i]==-1) nxt[rt][i]=rt;
            else {
                fail[nxt[rt][i]]=rt;
                q.push(nxt[rt][i]);
            }
        }

        while(!q.empty()) {
            int p=q.front();q.pop();
            rep(i,0,M) {
                if(nxt[p][i]==-1) nxt[p][i]=nxt[fail[p]][i];
                else fail[nxt[p][i]]=nxt[fail[p]][i],q.push(nxt[p][i]);
            }
        }
    }
    void qry(char s[]) {
        int p=rt;
        int n=strlen(s);
        for(int i=0;i<n;++i) {
            int c=s[i]-'a';
            p=nxt[p][c];
            int tmp=p;
            while(tmp!=rt) {
                //...
                tmp=fail[tmp];
            }
        }

    }
}tr;
```
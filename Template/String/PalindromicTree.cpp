// [0,p) , 0(even) and 1(odd) is virtual , init!!
struct Palindromic_Tree {
	static const int N = ::N , M = 26;
	int ne[N][M] , fail[N] , len[N] , S[N] , last , n , p, cnt[N], las[N];
	int newnode(int l){
		fill(ne[p] , ne[p] + M , 0);
		len[p] = l;
		las[p] = n;
		cnt[p] = 0;
		return p++;
	}
	void ini(){
		p = 0;newnode(0);newnode(-1);
		S[n = last = 0] = -1;
		fail[0] = 1;
	}
	int get_fail(int x){
		while(S[n - len[x] - 1] != S[n]) x = fail[x];
		return x;
	}
	void add(int c){
		S[++n] = c;
		int cur = get_fail(last);
		if(!ne[cur][c]){
			int now = newnode(len[cur] + 2);
			fail[now] = ne[get_fail(fail[cur])][c];
			ne[cur][c] = now;
		}
		last = ne[cur][c];
		cnt[last]++;
	}
	void build() {
		for(int i = p - 1; ~i; --i) cnt[fail[i]] += cnt[i];
	}
}pam;

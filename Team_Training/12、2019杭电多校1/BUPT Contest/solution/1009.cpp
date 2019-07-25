#include <bits/stdc++.h>
using namespace std;
#define rep(i, j, k) for (int i = int(j); i <= int(k); ++ i)
#define dwn(i, j, k) for (int i = int(j); i >= int(k); -- i)
const int N = 1e5 + 7; 
char s[N], s1[N];
int k, n, cnt[N][26], l[26], r[26], used[26];
vector<int> g[26];
int main() {
	while(~scanf("%s%d", s, &k)) {
	    memset(used,0,sizeof(used));
    	rep(i, 0, 25) scanf("%d%d", l + i, r + i);
    	n = strlen(s);
    	memset(cnt[n],0,sizeof(cnt[n]));
    	for(int i=0;i<26;++i)
    	    g[i].clear();
    	dwn(i, n - 1, 0) rep(j, 0, 25) cnt[i][j] = cnt[i + 1][j] + (s[i] == 'a' + j);
    	rep(i, 0, n - 1) g[s[i] - 'a'].push_back(i);
    	// for (int i: g[0]) cout << i << " "; cout << endl;
    	// for (int i: g[1]) cout << i << " ";cout << endl;
    	vector<int>::iterator head[26];
    	rep(i, 0, 25) head[i] = g[i].begin();
    	int last = -1;
    	rep(i, 0, k - 1) {
    		bool f1 = 0;
    		rep(j, 0, 25) {
    			if (used[j] == r[j]) continue;
    			while (head[j] != g[j].end() && (*head[j]) <= last) head[j] ++;
    			if (head[j] == g[j].end()) continue;
    			used[j] ++;
    			bool flag = 1;
    			int pos = *head[j], sum = 0;
    
    			rep(t, 0, 25) {
    				if (cnt[pos + 1][t] + used[t] < l[t]) flag = 0;
    				sum += max(l[t] - used[t], 0);
    			}
    			if (sum > k - i - 1) flag = 0;
    			sum = 0;
    			rep(t, 0, 25) {
    				sum += min(cnt[pos + 1][t], r[t] - used[t]);
    			}
    			if (sum < k - i - 1) flag = 0;
    			// cout << i << " " << j << " " << flag << endl;
    			if (!flag) used[j] --;
    			else {
    				s1[i] = 'a' + j;
    				f1 = 1;
    				last = pos;
    				break;
    			}
    		}
    		if (!f1) {
    			printf("-1\n");
    			goto end;
    		}
    	}
    	/*int cc[26];
    	rep(i, 0, 25) cc[i] = 0;
    	rep(i, 0, k - 1) cc[s1[i] - 'a'] ++;
    	rep(i, 0, 25) {
    		if (cc[i] < l[i] || cc[i] > r[i]) {
    			cout << i << endl;
    			cout << cc[i] << " " << l[i] << " " << r[i] << endl;
    		}
    	}*/
    	s1[k]=0;
    	printf("%s\n", s1);
    	end:;
	}
	return 0;
}

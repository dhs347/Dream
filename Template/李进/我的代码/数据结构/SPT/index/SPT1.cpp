# include <iostream>
# include <sstream>
# include <cstdio>
# include <cstdlib>
# include <algorithm>
# include <string>
# include <cstring>
# include <cmath>
# include <stack>
# include <queue>
# include <vector>
# include <list>
# include <map>
# include <set>
# include <deque>
# include <iterator>
# include <functional>
# include <bitset>
# include <climits>
# include <ctime>

using namespace std;

const int MAXN = 10010;
const int INF = 0x3f3f3f3f;

int a[MAXN],n,q;

struct SPT{
	#define Key_value c[c[root][1]][0]
	int p[MAXN],c[MAXN][2],key[MAXN],size[MAXN];
	int root,tot1;
	int sum[MAXN],rev[MAXN],same[MAXN];
	int lx[MAXN],rx[MAXN],mx[MAXN];
	int s[MAXN],tot2;//内存池和容量

	//debug部分**********************************

	void Travel(int x){
		if(x){
			Travel(c[x][0]);
			printf("结点： %2d: 左儿子 %2d 右儿子 %2d 父结点 %2d size= %2d\n",x,c[x][0],c[x][1],p[x],size[x]);
			Travel(c[x][1]);
		}
	}

	void debug(){
		printf("root:%d\n",root);
		Travel(root);
	}
	//以上是debug部分**************************************

	void NewNode(int &r,int f,int k){
		if(tot2) r = s[tot2--]; else r = ++tot1;
		p[r] = f;
		c[r][0] = c[r][1] = rev[r] = same[r] = 0;
		key[r] = sum[r] = lx[r] = rx[r] = mx[r] = k;
		size[r] = 1;
	}

	void Update_Rev(int r){
		if(!r)return;
		swap(c[r][0],c[r][1]); swap(lx[r],rx[r]);
		rev[r] ^= 1;
	}

	void Update_Same(int r,int v){
		if(!r)return;
		key[r] = v; sum[r] = v*size[r];
		lx[r] = rx[r] = mx[r] = max(v,v*size[r]);
		same[r] = 1;
	}

	void push_up(int r){
		int lson = c[r][0], rson = c[r][1];
		size[r] = size[lson] + size[rson] + 1;
		sum[r] = sum[lson] + sum[rson] + key[r];
		lx[r] = max(lx[lson],sum[lson] + key[r] + max(0,lx[rson]));
		rx[r] = max(rx[rson],sum[rson] + key[r] + max(0,rx[lson]));
		mx[r] = max(0,rx[lson]) + key[r] + max(0,lx[rson]);
		mx[r] = max(mx[r],max(mx[lson],mx[rson]));
	}

	void push_down(int r){
		if(same[r]){
			Update_Same(c[r][0],key[r]);
			Update_Same(c[r][1],key[r]);
			same[r] = 0;
		}
		if(rev[r]){
			Update_Rev(c[r][0]) ;
			Update_Rev(c[r][1]);
			rev[r] = 0;
		}
	}

	void Build(int &x,int l,int r,int f){
		if(l > r)return;
		int m = (l+r) >> 1;
		NewNode(x,f,a[m]);
		Build(c[x][0],l,m-1,x);
		Build(c[x][1],m+1,r,x);
		push_up(x);
	}

	void Init(){
		root = tot1 = tot2 = 0;
		c[root][0] = c[root][1] = size[root] = p[root] = 0;
		same[root] = rev[root] = sum[root] = key[root] = 0;
		lx[root] = rx[root] = mx[root] = -INF;
		NewNode(root,0,-1);
		NewNode(c[root][1],root,-1);
		for(int i = 0;i < n;i++) scanf("%d",&a[i]);
		Build(Key_value,0,n-1,c[root][1]);
		push_up(c[root][1]);
		push_up(root);
	}

	void Rotate(int x,int kind){
		int y = p[x];
		push_down(y);
		push_down(x);
		c[y][!kind] = c[x][kind];
		p[c[x][kind]] = y;
		if(p[y]) c[p[y]][c[p[y]][1]==y] = x;
		p[x] = p[y];
		c[x][kind] = y;
		p[y] = x;
		push_up(y);
	}

	void Splay(int r,int g){
		push_down(r);
		while(p[r] != g){
			if(p[p[r]] == g){
				push_down(p[r]);
				push_down(r);
				Rotate(r,c[p[r]][0] == r);
			}
			else{
				push_down(p[p[r]]);
				push_down(p[r]);
				push_down(r);
				int y = p[r];
				int kind = c[p[y]][0]==y;
				if(c[y][kind] == r){
					Rotate(r,!kind);
					Rotate(r,kind);
				}
				else{
					Rotate(y,kind);
					Rotate(r,kind);
				}
			}
		}
		push_up(r);
		if(g == 0) root = r;
	}

	int Get_kth(int r,int k){
		push_down(r);
		int t = size[c[r][0]] + 1;
		if(t == k)return r;
		if(t > k)return Get_kth(c[r][0],k);
		return Get_kth(c[r][1],k-t);
	}
		
	void Insert(int pos,int tot){
		for(int i = 0;i < tot;i++)scanf("%d",&a[i]);
		Splay(Get_kth(root,pos+1),0);
		Splay(Get_kth(root,pos+2),root);
		Build(Key_value,0,tot-1,c[root][1]);
		push_up(c[root][1]);
		push_up(root);
	}

	void erase(int r){
		if(!r)return;
		s[++tot2] = r;
		erase(c[r][0]);
		erase(c[r][1]);
	}

	void Delete(int pos,int tot){
		Splay(Get_kth(root,pos),0);
		Splay(Get_kth(root,pos+tot+1),root);
		erase(Key_value);
		p[Key_value] = 0;
		Key_value = 0;
		push_up(c[root][1]);
		push_up(root);
	}

	void Change_Same(int pos,int tot,int d){
		Splay(Get_kth(root,pos),0);
		Splay(Get_kth(root,pos+tot+1),root);
		Update_Same(Key_value,d);
		push_up(c[root][1]);
		push_up(root);
	}
	
	void Reverse(int pos,int tot){
		Splay(Get_kth(root,pos),0);
		Splay(Get_kth(root,pos+tot+1),root);
		Update_Rev(Key_value);
		push_up(c[root][1]);
		push_up(root);
	}

	int Get_Sum(int pos,int tot){
		Splay(Get_kth(root,pos),0);
		Splay(Get_kth(root,pos+tot+1),root);
		return sum[Key_value];
	}

	int Get_MaxSum(int pos,int tot){
		Splay(Get_kth(root,pos),0);
		Splay(Get_kth(root,pos+tot+1),root);
		return mx[Key_value];
	}

	void Print(int r){
		if(!r)return;
		push_down(r);
		Print(c[r][0]);
		printf("%d ",key[r]);
		Print(c[r][1]);
	}
};

void file_put(){
  freopen("filename.in","r",stdin);
  freopen("filename.out","w",stdout);
}


int main(){
	file_put();

	SPT T;
	while(scanf("%d%d",&n,&q) == 2)
	{
		T.Init();
		char op[20];
		int x,y,z;
		while(q--){
			scanf("%s",op);
			if(strcmp(op,"INSERT") == 0){
				scanf("%d%d",&x,&y);
				T.Insert(x,y);
			}
			else if(strcmp(op,"DELETE") == 0){
				scanf("%d%d",&x,&y);
				T.Delete(x,y);
			}
			else if(strcmp(op,"CHANGE-SAME") == 0){
				scanf("%d%d%d",&x,&y,&z);
				T.Change_Same(x,y,z);
			}
			else if(strcmp(op,"REVERSE") == 0){
				scanf("%d%d",&x,&y);
				T.Reverse(x,y);
			}
			else if(strcmp(op,"GET-SUM") == 0){
				scanf("%d%d",&x,&y);
				printf("%d\n",T.Get_Sum(x,y));
			}
			else if(strcmp(op,"MAX-SUM") == 0){
				scanf("%d%d",&x,&y);
				printf("%d\n",T.Get_MaxSum(x,y));
			}
			else if(strcmp(op,"PRINT") == 0){
				T.Print(T.root);
				printf("\n");
			}
		}
	}
	
	return 0;
}

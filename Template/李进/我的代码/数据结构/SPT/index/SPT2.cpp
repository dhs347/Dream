#include<iostream>
#include<cstdio>
#include<cstring>
#define LL long long
using namespace std;
const int MAXN = 333333;
#define m_set(ptr,v,type,size) memset(ptr,v,sizeof(type) * size)
#define loop(begin,end) for(int i=begin;i<end;i++)
#define debug	puts("here!")
class SplayTree
{
	#define l(x) (ch[x][0])
	#define r(x) (ch[x][1])
	#define mid(x,y)	((x+y)>>1)
	public:
		int ch[MAXN][2],pre[MAXN];
		int sz[MAXN],val[MAXN],rev[MAXN],a[MAXN];
		int root,tot;
		
		/**************/
		
		int mx[MAXN];
		
		/**************/ 
		
		LL sum[MAXN],add[MAXN];
		
		/**************/
		
		void init()
		{
			m_set(ch,0,int,MAXN*2);
			m_set(pre,0,int,MAXN);
			m_set(sz,0,int,MAXN);
			m_set(val,0,int,MAXN);
			m_set(rev,0,int,MAXN);
			
			/*************/
			m_set(mx,-1,int,MAXN);
			/*************/
			root = tot = 0;
		}
		
		void read(int n)		//0 1 2 3 .... n 0
		{
			a[1] = a[n+2] = -1;
//			loop(2,n+2){
//				a[i] = i - 1;
//			}	

			/*************/
			for(int i=2;i<=n+1;i++)
			{
				scanf("%d",&a[i]);
			}
			/*************/
		}
		
		void push_up(int rt)
		{
			sz[rt] = sz[l(rt)] + sz[r(rt)] + 1;
			/*************/
			mx[rt] = max(max(mx[l(rt)],mx[r(rt)]),val[rt]);
			/*************/
			sum[rt] = sum[l(rt)] + sum[r(rt)] + val[rt];
		} 
		
		void push_down(int rt)
		{
//			if(rt&&rev[rt])
//			{
//				swap(l(rt),r(rt));
//				if(l(rt))	rev[l(rt)] ^= 1;
//				if(r(rt))	rev[r(rt)] ^= 1;
//				rev[rt] = 0;
//			}
		
			if(add[rt])
			{
				if(l(rt))
				{
					val[l(rt)] += add[rt];
					add[l(rt)] += add[rt];
					sum[l(rt)] += add[rt] * sz[l(rt)];
				}
				if(r(rt))
				{
					val[r(rt)] += add[rt];
					add[r(rt)] += add[rt];
					sum[r(rt)] += add[rt] * sz[r(rt)]; 
				}
				add[rt] = 0;
			}			
		}
			
		void swap(int &x,int &y)
		{
			int tmp = x;
			x = y;
			y = tmp;
		}
		
	
		void rotate(int x,int f)	//将x旋转到其直接父节点 右旋 左旋 
		{
			int y  = pre[x];
			push_down(x);
			push_down(y);
			ch[y][!f] = ch[x][f];
			if(ch[y][!f])	pre[ch[y][!f]] = y;
			push_up(y);
			if(pre[y])	ch[pre[y]][r(pre[y])==y]= x;
			pre[x] = pre[y];
			ch[x][f] = y;
			pre[y] = x;
		}
		
		void splay(int x,int goal)	//将x旋转到以goal节点为父节点 
		{
			push_down(x);
			while(pre[x]!=goal)
			{
				int y = pre[x] , z = pre[pre[x]]; 
				if(z==goal)
				{
					rotate(x,l(y)==x);
				}
				else
				{
					int f = (l(z) == y);
					if(ch[y][!f] == x)
					{
						rotate(y,f);
						rotate(x,f);
					}
					else
					{
						rotate(x,!f);
						rotate(x,f);
					}
				}
			} 
			push_up(x);
			if(goal==0)	root = x;
		}
		
		void rotateTo(int k,int goal)
		{
			int x = root;
			while(true)
			{
				push_down(x);
				int tmp = sz[l(x)] + 1;
				if(k==tmp)	break;
				else if(k<tmp)	x = l(x);
				else
				{
					k -= tmp;
					x = r(x);
				}
			}
			splay(x,goal);
		}
		
		void buildTree(int l,int r,int &rt,int f)
		{
			if(l>r)	return;
			int m = mid(l,r);
			rt = ++tot;
			val[rt] = a[m];
			pre[rt] = f;
			buildTree(l,m-1,l(rt),rt);
			buildTree(m+1,r,r(rt),rt);
			push_up(rt);
		}
		
		void rangeCut(int l,int r,int goal)
		{
			rotateTo(l-1,0);
			rotateTo(r+1,root);
			push_down(r(root));
			int x = l(r(root));	//x子树代表[l,r]区间
			//截取 
			l(r(root)) = 0;	
			pre[x] = 0; 
			push_up(r(root));
			push_up(root);
			rotateTo(goal,0);
			rotateTo(goal+1,root);
			push_down(r(root));
			l(r(root)) = x;
			pre[x] = r(root);
			push_up(r(root));
			push_up(root); 
		}
		
		void rangeFlip(int l,int r)
		{
			rotateTo(l-1,0);
			rotateTo(r+1,root);
			push_down(r(root));
			int x = l(r(root));
			rev[x] ^= 1;		
		}
		
		void dfs(int rt,int &size)
		{
			if(!rt)	return;
			push_down(rt);
			dfs(l(rt),size);
			a[size++] = val[rt];
			dfs(r(rt),size);
		} 
		
		
		/********************/
		int query(int l,int r)
		{
			rotateTo(l-1,0);
			rotateTo(r+1,root);
			return mx[l(r(root))];
		} 
		
		void update(int pos,int c)
		{
			rotateTo(pos,0);
			val[root] = c;
			push_up(root);
		}
		
		LL querySum(int l,int r)
		{
			rotateTo(l-1,0);
			rotateTo(r+1,root);
			return sum[l(r(root))];
		} 
		
		void updateInterval(int l,int r,int c)
		{
			rotateTo(l-1,0);
			rotateTo(r+1,root);
			val[l(r(root))] += c;
			sum[l(r(root))] += c * sz[l(r(root))];
			add[l(r(root))] += c;
		}
		
}spt;

//int main()
//{
//	int n,m;
//	while(~scanf("%d%d",&n,&m) && (n>=0 || m>=0))
//	{
//		spt.init();
//		spt.read(n); 
//		spt.buildTree(1,n+2,spt.root,0);
//		char op[5];
//		int a,b,c;
//		while(m--)
//		{
//			scanf("%s%d%d",op,&a,&b);
//			if(op[0]=='C')
//			{
//				scanf("%d",&c);
//				spt.rangeCut(a+1,b+1,c+1);	//因为哨兵0 多加1
//			}
//			else
//			{
//				spt.rangeFlip(a+1,b+1);
//			}
//		}
//		n = 0;
//		spt.dfs(spt.root,n);	//中序遍历即为序列结果 
//		loop(1,n-1)
//		{
//			if(i!=1)	printf(" ");
//			printf("%d",spt.a[i]);
//		}
//		printf("\n");
//	}
//	return 0;
//}





//int main()
//{
//	int n,m;
//	while(scanf("%d%d",&n,&m) == 2)
//	{
//		spt.init();
//		spt.read(n);
//		spt.buildTree(1,n+2,spt.root,0);
//		char op[2];
//		int a,b;
//		while(m--)
//		{
//			scanf("%s%d%d",op,&a,&b);
//			if(op[0]=='Q')
//			{
//				printf("%d\n",spt.query(a+1,b+1));
//			}
//			else
//			{
//				spt.update(a+1,b);
//			}
//		}
//	}
//	return 0;
//} 



int main()
{
	int n,m;
	while(~scanf("%d%d",&n,&m))
	{
		spt.init();
		spt.read(n);
		spt.buildTree(1,n+2,spt.root,0);
		char op[2];
		int a,b,c;
		while(m--)
		{
			scanf("%s%d%d",op,&a,&b);
			if(op[0] == 'Q')
			{
				printf("%I64d\n",spt.querySum(a+1,b+1));
			}
			else
			{
				scanf("%d",&c);
				spt.updateInterval(a+1,b+1,c);
			}
		}
	}
	return 0;
}


/*
_http://acm.hdu.edu.cn/showproblem.php?pid=3487_
1.区间切割 区间翻转      
原序列:	1、2、3 ……n 
rangeCut(a,b,c)	将[ath,bth]剪切掉 然后黏贴到新序列的第cth后面 
rangeFlip(a,b)	翻转[ath,bth] 



_http://acm.hdu.edu.cn/showproblem.php?pid=1754_
2.单点更新 区间询问最值 	
query(a,b)	询问[a,b]最大值
update(a,c)	更新学生a的成绩为c 



_http://poj.org/problem?id=3468_
3.区间更新 区间求和
querySum(l,r)	询问[l,r]的和 
updateInterval(l,r,c)	区间[l,r]的值+c 

*/ 
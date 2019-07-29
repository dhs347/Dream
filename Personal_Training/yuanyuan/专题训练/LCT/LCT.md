# LCT

start time: 2019/4/8 15:33

end time: 2019/4/13 14:56

中途有一天忙别的事去了

## 参考资料

**概念：**  《SPOJ375 QTREE 解法的一些研究》 —— 杨哲

​               http://www.cnblogs.com/flashhu/p/8324551.html

**泛做：**   https://www.cnblogs.com/flashhu/p/9498517.html

**进阶：** 《浅谈动态树的相关问题及简单拓展》 —— 黄志翱

## 泛做

**洛谷P3203 [HNOI2010]弹飞绵羊**

建一个虚节点，这样就可以快速知道每个点的根是什么

**洛谷P1501 [国家集训队]Tree II**

gao函数需要改一下

**洛谷P2486 [SDOI2011]染色**

区间标记需要注意细节

**洛谷P4332 [SHOI2014]三叉神经树**

寻找信息可以二分去找

因为这题信息也就四种，所以也可以直接维护信息为i(0~3)的最深的点是哪个，就不用二分了

**洛谷P2147 [SDOI2008]Cave 洞穴勘测**

模板题

**洛谷P3950 部落冲突**

模板题

**洛谷P2542 [AHOI2005]航线规划**

LCT维护的一般是点的信息，如果要维护边的信息，可以把边也当成一个点

**BZOJ4998 星球联盟**

LCT维护边双

**BZOJ2959 长跑**

LCT维护边双缩点，常数比较大

**BZOJ2594 [Wc2006]水管局长数据加强版**

离散化之后只需要比较标号即可

**UOJ274温暖会指引我们前行**

和上一题差不多

**洛谷P4234 最小差值生成树**

枚举边权最大值，用LCT求MST

**洛谷P2387 [NOI2014]魔法森林**

枚举ai的最大值，用LCT维护bi最大值最小的生成树

**洛谷P4219 [BJOI2014]大融合**

维护子树信息模板题

**洛谷U19464 山村游历(Wander)**

转化成[这个题解](http://www.cnblogs.com/flashhu/p/8423974.html)的图就很好理解了。

**洛谷P2173 [ZJOI2012]网络**

每个点拆成C种颜色。由性质2得知每个颜色都是一棵树。

**hdoj4677 Query on Graph**

定义一条边的权值为它最小的端点标号，枚举出现的最大的点，维护最大瓶颈树，查询的时候只需要知道有多少边权值在 [l, r] 范围

## 维护树直径

https://blog.csdn.net/lvzelong2014/article/details/85605142

http://xxccxcxc.top/post/268/

```c++
int lmx[N], rmx[N], mxs[N], sum[N], a[N]; 
multiset<int> chain[N], path[N];
void Up(int p) {
	sum[p] = sum[ls] + sum[rs] + a[p]; // a[p] 是点权， sum[p] 表示当前链长
	LL cha = max(0LL, fir(Chain[p])); // 从 p 沿虚儿子走的最远距离
	LL L = max(cha, rmx[ls]) + a[p]; // 从 p 沿父亲走的最远距离
	LL R = max(cha, lmx[rs]) + a[p]; // 从 p 沿实儿子走的最远距离
	lmx[p] = max(lmx[ls], sum[ls] + R); // 从链顶出发的最远距离
	rmx[p] = max(rmx[rs], sum[rs] + L); // 从链底出发的最远距离
	mxs[p] = max(mxs[ls], mxs[rs]); // mxs[p] 表示链 p 及链 p 所有虚子树的最大答案 
	Re(mxs[p], fir(Path[p])); // 虚子树中的最大答案
	Re(mxs[p], rmx[ls] + R); // 经过 p 父边的答案
	Re(mxs[p], lmx[rs] + L); // 经过 u 向下实边的答案
	Re(mxs[p], cha + sec(Chain[p]) + a[p]); // 虚子树中到根路径最长的两条拼起来
	Re(mxs[p], cha + a[p]); // 虚子树中到根路径最长的一条和 p 自己组成路径
}
void Access(int u) {
	for(int p = u, pr = 0; p; pr = p, p = fa[p]) {
		Splay(p);
      	 // 虚子树变动时，更新保存虚子树答案和虚子树到根路径的 set 
		if(pr) Era(Chain[u], lmx[v]), Era(Path[u], mxs[v]);
		if(rs) Chain[u].insert(lmx[rs]), Path[u].insert(mxs[rs]); 
		rs = pr; 
		Up(p);		
	}
	Splay(u);
}
```

##TBD

结合了其他知识点的题目、LCT维护树直径类似问题

http://uoj.ac/problem/207

https://loj.ac/problem/558

https://loj.ac/problem/2289

https://www.luogu.org/problemnew/show/P3703

https://www.luogu.org/problemnew/show/P3613

https://www.luogu.org/problemnew/show/P3348

https://www.luogu.org/problemnew/show/P4338

https://www.luogu.org/problemnew/show/SP2939

https://www.luogu.org/problemnew/show/SP16549

https://www.luogu.org/problemnew/show/SP16580

http://www.lydsy.com/JudgeOnline/problem.php?id=4025

http://www.lydsy.com/JudgeOnline/problem.php?id=2759

http://www.lydsy.com/JudgeOnline/problem.php?id=3914

http://www.lydsy.com/JudgeOnline/problem.php?id=4012
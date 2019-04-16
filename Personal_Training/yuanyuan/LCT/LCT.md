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
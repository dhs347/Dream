- [x] 斯坦纳树 1.00

  O 1.https://www.lydsy.com/JudgeOnline/problem.php?id=2595

  O 2.https://www.lydsy.com/JudgeOnline/problem.php?id=3205

  ​	关键在建图，以及因为边权为1可以用多源bfs 

  O 3.https://www.lydsy.com/JudgeOnline/problem.php?id=4774

  O 4.https://www.lydsy.com/JudgeOnline/problem.php?id=5180

  ​	如果图比较大且为正权，用dijstra 

  O 5.https://www.lydsy.com/JudgeOnline/problem.php?id=4006

  ​	只要一些点对之间联通，做完斯坦纳树后再dp一遍 

  O 6.https://codeforces.com/problemset/problem/152/E

  ​	要会记录方案

  O 7.http://acm.zju.edu.cn/onlinejudge/showProblem.do?problemCode=3613

  ​	要注意如果一个点是两类关键点，设dp初值时状态要合起来

  O 8.http://acm.hdu.edu.cn/showproblem.php?pid=3832

  ​	如果关键点小于等于3其实可以分别跑最短路枚举中间点算，不用斯坦纳树

  O 9.http://acm.hdu.edu.cn/showproblem.php?pid=3311

  ​	点边都有代价，联通快中的点只要有一个付出代价就行，建超级源的技巧 ，向所有点连边权为点权的边

  O 10.http://acm.hdu.edu.cn/showproblem.php?pid=4085

  O http://acm.hdu.edu.cn/showproblem.php?pid=6060 非斯坦树题

- [x] 基环树 1.00

  O 1.http://codeforces.com/problemset/problem/875/F

  ​	求最大生成基环树，把二分图一边度都为2的点当成边是个套路 

  O 2.https://www.lydsy.com/JudgeOnline/problem.php?id=1040

  ​	求基环树带权最大点独立集，注意自环和二元环时的重边 

  O 3.https://www.lydsy.com/JudgeOnline/problem.php?id=3242

  ​	求边上一点到基环树最远点距离最小，可以转化成基环树断一条环边使直径最小

  ​	分类讨论，处理选的两点在断掉一边和分在两边的情况 

  O 4.https://www.lydsy.com/JudgeOnline/problem.php?id=1791

  ​	求基环树的直径

  O 5.https://www.lydsy.com/JudgeOnline/problem.php?id=2791

  ​	类似于基环树上求lca，分类讨论，注意自环 

  O 6.https://www.lydsy.com/JudgeOnline/problem.php?id=2878

  ​	求基环树上任意起点走的路径长度期望，比较复杂的dp，以及常见的树上换根套路，环比较小，环上可以暴力做

  O 7.https://www.lydsy.com/JudgeOnline/problem.php?id=1116

  ​	判断图是否有子图是基环树，水题，可以认为边权为1求最大生成基环树

  8.http://acm.hdu.edu.cn/showproblem.php?pid=6370

  9.http://acm.hdu.edu.cn/showproblem.php?pid=6403

  10.http://acm.hdu.edu.cn/showproblem.php?pid=5304

  11.http://acm.hdu.edu.cn/showproblem.php?pid=6393

  12.http://acm.hdu.edu.cn/showproblem.php?pid=5967

  13.https://agc008.contest.atcoder.jp/tasks/agc008_e

- [x] 概率dp 2.00

  O 1.http://acm.hdu.edu.cn/showproblem.php?pid=4809

  ​	偏树形dp，和概率关系比较小，树上每个点可分给三个人，每个人消耗他有的奇数联通块数减偶数联通块数的代价，记录i的联通块奇偶性和已有的差值，与儿子转移一下

  O 2.http://codeforces.com/gym/101655  (C题)

  ​	暴力记忆化转移 

  O 3.https://www.lydsy.com/JudgeOnline/problem.php?id=5340

  ​	概率的形式可以用多项式表示，以及多项式除两项多项式可以O(n)做到

  O 4.https://www.lydsy.com/JudgeOnline/problem.php?id=2688

  ​	树上删边的sg函数结论，然后以sg值为状态转移概率，用到二叉树计数

  O 5.https://www.lydsy.com/JudgeOnline/problem.php?id=3450

  ​	维护连续1平方的期望，知道了期望可以通过维护差值来转移

  O 6.https://www.lydsy.com/JudgeOnline/problem.php?id=4844

  ​	列出dp方程，优化一下计数方式即可

  O 7.https://www.lydsy.com/JudgeOnline/problem.php?id=4318

  ​	维护连续1立方的期望，和之前差不多，多维护一项平方的期望

  O 8.https://www.lydsy.com/JudgeOnline/problem.php?id=1426

  ​	收集n个物品，每次随机买，每买一次价格贵1，问期望多少钱买齐

  ​	状态要建立成有i个物品且还没买过东西，这样可以和前面无关，然后化简转移方程

  ？9.https://www.lydsy.com/JudgeOnline/problem.php?id=4820

  O 10.https://www.lydsy.com/JudgeOnline/problem.php?id=5004

  ​	概率空间有限，其实就是组合计数，dp转移一下，但是题面写有精度判断，但bzoj是直接比较，被坑了不少时间

  O 11.https://www.lydsy.com/JudgeOnline/problem.php?id=3029

  ​	简单的概率dp，设计dp状态转移一下，一些小技巧，增加偏移量和滚动数组

  O 12.https://www.lydsy.com/JudgeOnline/problem.php?id=2554

  ​	有一堆有颜色的小球，每次选两个出来，把后面变前面颜色，问期望多少次变一样，先转化成只考虑两种颜色，然后要求条件概率下的期望，其相邻两项转移系数是不同的，以及一个套路，求与左右相邻两项有关的递推式的方法

  O 13.https://www.lydsy.com/JudgeOnline/problem.php?id=3270

  ​	状态图上随机游走，有一些终结态，求停在每个状态的概率，算是通用套路，设经过期望次数，去建立方程，高斯消元

  O 14.https://www.lydsy.com/JudgeOnline/problem.php?id=2201

  ​	一个环上每个点随机颜色，问连续颜色长度乘积的期望，枚举第一个长度断环，dp求一下第二个和最后一个颜色和第一个不同的期望

  O 15.https://www.lydsy.com/JudgeOnline/problem.php?id=4008

  ​	只考虑第一张卡牌，发现期望只和它发布发动有关，和在哪一轮发动无关，所以以此建立状态记忆化转移

  O 16.https://www.lydsy.com/JudgeOnline/problem.php?id=3566

  ​	树上概率dp加上换根技巧，以及换根的时候要注意运算是否可逆

  O 17.https://www.lydsy.com/JudgeOnline/problem.php?id=2337

  ​	异或拆位后建图建立方程组高斯消元

  O 18.https://www.lydsy.com/JudgeOnline/problem.php?id=3143

  ​	计算随机游走的过程中每条边经过的期望次数

  O 19.https://www.lydsy.com/JudgeOnline/problem.php?id=3191

  ​	简单题，表示一下状态转移，就是环上的下标转移要计算清楚

  O 20.https://www.lydsy.com/JudgeOnline/problem.php?id=5292

  ​	求出转移方程，发现第i项之和i+1和与它小的项有关系，这样接近与上三角，可以用高斯消元在O(n^2)解决

  21.https://www.lydsy.com/JudgeOnline/problem.php?id=5461

  22.https://www.lydsy.com/JudgeOnline/problem.php?id=4720

  23.https://www.lydsy.com/JudgeOnline/problem.php?id=4944

  24.https://www.lydsy.com/JudgeOnline/problem.php?id=1415

  25.https://www.lydsy.com/JudgeOnline/problem.php?id=2676

  26.https://www.lydsy.com/JudgeOnline/problem.php?id=3811

  27.https://www.lydsy.com/JudgeOnline/problem.php?id=2707

  28.https://www.lydsy.com/JudgeOnline/problem.php?id=1076

  29.http://codeforces.com/problemset/problem/696/B

  O 30.https://www.lydsy.com/JudgeOnline/problem.php?id=1444

  ​	建AC自动机，变量定义为经过每个状态的期望次数，建立方程组高斯消元。

- [x] min-max容斥/最值反演 1.00

  O 1.http://acm.hdu.edu.cn/showproblem.php?pid=4336

  ​	发现集合中的元素即使不是独立的好像也可以使用

  O 2.https://www.lydsy.com/JudgeOnline/problem.php?id=4036

  ​	min-max容斥并取反后发现要求子集和，可以用高维前缀和或者fwt

  O 3.https://www.luogu.org/problemnew/show/P4707

  ​	应用kthmax转换后发现就是对于容斥集合计数dp的套路，但是这样复杂度还是不够，因为k比较小，发现这个公式的系数其实是可以关于k递推的，于是就优化了复杂度，可以做了

  O 4.http://acm.hdu.edu.cn/showproblem.php?pid=4624

  ​	min-max容斥后转为dp求相同区间数的集合方案数，这题要高精度，比较坑

  O 5.https://www.lydsy.com/JudgeOnline/problem.php?id=4833

     这题套路很多，首先看出递推式后要发现有两项gcd等于下标gcd那一项的性质，然后是min-max容斥在整数上使用就是lcm-gcd容斥，然后还要构造一个h函数使
  $$
  f(n) = \prod_{d|n} h(d)
  $$
  改为计算每个h的贡献，发现指数被消成1了，就只要计算出h即可

  O 6.https://loj.ac/problem/2542

  ​	计算树上随机游走经过给定集合所有点期望次数，min-max容斥后要求第一次经过一个集合的点期望次数，虽然可以高斯消元，但复杂度不行，如果结构是树的话其实可以求每个点期望还要走多少次，然后把f[i]表示成只和f[fa[i]]以及常数b[i]有关,就可以O(n)实现了

- [x] 高维前缀和 0.50

  O 1.http://codeforces.com/contest/449/problem/D

  ​	问一堆数有多少种方案and起来是0，用容斥转化为求有结果不为0的方案数，然后这个要用高维前缀和来处理有多少数字可选。	

  X 2.http://codeforces.com/problemset/problem/799/F

  ​	求所有和给定区间是不交或交长度是奇数的区间和，应该有数据结构的做法，不过有做法是用随机数加xor搞过去，和高维前缀和没什么关系，只是有不少前缀和而已

  O 3.https://www.lydsy.com/JudgeOnline/problem.php?id=5092

  ​	符合前缀性质的都可以这样做，可以维护前缀min，这样可以知道固定几位的那种数字最早什么时候出现。

- [ ] 树形dp 2.00

  1.http://codeforces.com/contest/766/problem/E

  2.http://codeforces.com/problemset/problem/868/E

  3.http://codeforces.com/problemset/problem/935/E

  4.http://codeforces.com/problemset/problem/960/E

  5.http://codeforces.com/problemset/problem/963/B

  6.http://codeforces.com/problemset/problem/1065/F

  7.http://codeforces.com/problemset/problem/1092/F

  注：树上换根，计算全局贡献

  8.http://codeforces.com/problemset/problem/1097/G

  注：经典且稍复杂的树上合并式背包，需容斥

  9.http://acm.hdu.edu.cn/showproblem.php?pid=6060

  O 10.http://codeforces.com/problemset/problem/1059/E

  ​	这题用贪心比较容易做，每次从叶子把向上最长能覆盖的都盖了，并查集维护被覆盖的点就行了，看了一下题解dp的做法，主要是一个点向下的链可以用从它开始欧拉序的前缀表示，然后比较麻烦，还需要线段树维护限制和答案，每次暴力删除已经不符合的点，因为这次不符合之后也不会再符合

  O 11.http://codeforces.com/problemset/problem/429/C

  ​	给你树上每个点的size，问树是否存在，正解应该是把叶子和非叶子分开状压，一棵树其实应该有多种子树选择方案，我直接贪心加背包选了一种，因为n比较小，可能反例不太有，这样做就可以过

  O 12.http://codeforces.com/problemset/problem/629/E

  ​	问树上两点加一条边成环平均长度，就是树上换根计数

  O 13.http://codeforces.com/problemset/problem/86/C

  ​	问能被一些字符串覆盖的母串有多少种，发现ac自动机一直理解错了，到了一个点要把它fail链上的点都算上贡献

  O 14.http://codeforces.com/problemset/problem/1146/F

  ​	感觉不错的树dp题，问你有多少种叶子划分使其相同集合叶子联通且没有交，要记录三个量，i的子树答案，i是已经被用的数量，i是被虚占用的数量，然后转移要推清楚，我一开始转移搞错了，花了很多时间。

  O 15.http://codeforces.com/problemset/problem/708/C

  ​	问每个点在能换一条边的情况下能否是重心，用树上换根技巧维护每一个点为根时子树中最大的小于n/2的子树size。

  O 16.http://codeforces.com/problemset/problem/490/F

  ​	问你树上所有路径中的最长上升子序列多长，维护向上向下两条链实现

  O 17.http://codeforces.com/problemset/problem/965/E

  ​	建完字典树后就变成树上有一些1，每个1可以往上移，但是每个位子至多一个1，要深度和最小，每次选最深的一个1，找到它向上第一个不为1的位置放过去，可以用并查集实现

  O 18.http://codeforces.com/problemset/problem/804/D

  ​	询问森林中两棵树连一条边期望直径，主要是复杂度上是有分块思想，一次询问的复杂度是较小树的size，那么大于sqrt(n)的点对最多只用n个，所以复杂度是O(nsqrt(n)log(n))

  O 19.http://codeforces.com/problemset/problem/1109/D

  ​	边权范围1-m，问有多少棵无根树a到b的距离是m，有一个prufer序列的结论，详细学了一下prufer序列，记在了它相关的结论中

  O 20.http://codeforces.com/problemset/problem/1032/F

  ​	问一棵树有多少种方法删一个点集使剩下的图最大匹配使唯一的，定义三种状态，i和儿子没边且没匹配，i和儿子有边且没匹配，i和儿子有边且匹配了，然后推一下转移式，然后发现一般转移如果是选儿子的子集，可以用乘法分配律合起来乘

  O 21.http://codeforces.com/problemset/problem/1132/G

  ​	给一个数组，每一位往后面第一个比他大的连边，问所有长度为k区间中最长链是多少，在dfs序上用线段树处理一下就行

  O 22.http://codeforces.com/problemset/problem/123/E

  ​	推出指定根后每个点期望怎么算后套上树上换根即可

  O 23.http://codeforces.com/problemset/problem/643/E

  ​	发现只有对一个点深度不超过一定值的点才对答案有影响，所以加点更新和算期望可以只算一部分，复杂度就对了。

- [ ] 分治 3.00

  O 1.https://www.lydsy.com/JudgeOnline/problem.php?id=4449

  ​	给一个多边形的三角剖分，询问亮点最短路，用分治每次选一条边尽可能把两边点集分成一样大，然后裂成两个图，然后询问如果在两边肯定会结果选的边的一个端点，分别去bfs即可

  O 2.https://www.lydsy.com/JudgeOnline/problem.php?id=2001

  ​	动态最小生成树，离线有分治做法，考虑如果有m条边权值不确定，图可以同过reduction和contraction操作缩减到O(m)，这样对询问序列去分治即可，这个过程和在二叉树上dfs差不多，所以直接求出下一层的边集并覆盖是没有问题的。

  O 3.https://www.lydsy.com/JudgeOnline/problem.php?id=3897

  ​	应用贪心思想，每次可以抠掉最大值那个点，然后分别到两边去做，由于要查询区间最大值，所以是O(nlogn)的，可能有O(n)的做法。

  O 4.https://www.lydsy.com/JudgeOnline/problem.php?id=2287

  ​	其实直接对背包做逆操作就可以了，但是像这种去掉一个点算剩下贡献可以用分治去实现。

  5.https://www.lydsy.com/JudgeOnline/problem.php?id=2961

  O 6.https://www.lydsy.com/JudgeOnline/problem.php?id=4979

  ​	对于全局查询有多少对区间符合一个限制，这个限制和区间端点和区间最值之类有关可以分治转成双指针维护

  O 7.https://www.lydsy.com/JudgeOnline/problem.php?id=3745

  ​	求所有区间长度乘区间最大值最小值的和，分治后转为枚举一边另一边分类讨论求和

  O 8.https://www.lydsy.com/JudgeOnline/problem.php?id=3181

  ​	不太算分治，就是对数据范围分类用不同的做法

- [x] 分治fft 2.00

  O1.https://www.lydsy.com/JudgeOnline/problem.php?id=5342

  ​	一个和自己卷积有关的递推式，可以用分治fft，但是麻烦一点，要分类讨论，还有就是这个递推式的推导过程感觉有问题，不过这种结构析合树应该还是有点用的。

  O2.https://www.lydsy.com/JudgeOnline/problem.php?id=4836

  ​	对权值去分治，然后分类讨论，分别做和卷积和差卷积

  O3.https://www.lydsy.com/JudgeOnline/problem.php?id=3456

  ​	求带标号联通图数量，那个递推式可以写成卷积形式，用分治fft优化

  O4.https://www.lydsy.com/JudgeOnline/problem.php?id=4555

  ​	bell数的一个变形，考虑求和式的组合意义，然后根据这个推出递推式，然后用分治fft去计算，但是这种递推式也可以用多项式求逆去做，还没有学。

  O5.https://www.lydsy.com/JudgeOnline/problem.php?id=4332

  ​	求多项式等比数列和的第m项系数，可以用递归除2去做。

- [ ] 状压dp 2.00

  O 1. http://acm.hdu.edu.cn/showproblem.php?pid=2820

  ​	求相邻差值小于等于k(k<=4)的排列数量，一种枚举排列的方法 	

  O 2. http://acm.hdu.edu.cn/showproblem.php?pid=1072

  ​	问有多少数字排列整除d，对余数装压

  O 3.  http://acm.hdu.edu.cn/showproblem.php?pid=1087

  ​	问N*N棋盘放k个国王有几种方案，需要先预处理两层之间的转移，不然复杂度不够

  O 4.  http://acm.hdu.edu.cn/showproblem.php?pid=1879

  ​	状压dp计数，状压dp要注意预处理转移，减少复杂度 

  O 5.  http://acm.hdu.edu.cn/showproblem.php?pid=2064

  ​	两堆数，每次可以合并两个，问最少几次可以两堆一样, 转移分步的思想要注意，可以减少复杂度 

  O 6.  http://acm.hdu.edu.cn/showproblem.php?pid=3717

  ​	n个物品放入m个包里，最少要几个包，状态为用了哪些物品，考虑状态之间的有序性，逐个插入物品

- [ ] 背包问题 0.50

- [ ] 构造 1.00

- [ ] 二分图匹配 2.00

- [ ] 整体二分 1.00

- [ ] 网络流 5.00

- [ ] 贪心 2.00

- [ ] 线性代数 1.00

- [ ] 最优比率生成树/最优比率环/01规划 0.50

- [ ] 虚树 1.00

- [ ] fft/ntt/fwt/fst等/生成函数与各种卷积 2.00

- [ ] 2-sat 2.00

- [ ] 高维偏序问题 1.00

- [ ] dancing_links及其他搜索优化 1.00

- [ ] 几类积性函数的求和方法/杜教筛/min25筛法等 2.00

- [ ] 普通dp及其优化 4.00

- [ ] 图论 4.00

- [ ] 组合数学与概率论 2.00

- [ ] 差分约束 1.00

- [ ] 动态树 1.00

- [ ] 长链剖分 1.00

- [ ] 点分治 1.00

- [ ] 笛卡尔树 1.00

- [ ] kd-tree 1.00

- [ ] 连分数 0.50

- [ ] 线段树模拟费用流 1.00

- [ ] 最小树形图 1.00

- [ ] 数论 1.00

- [ ] simpson积分法 0.50

- [ ] 数据结构 1.00

- [ ] 传递闭包 0.50

- [ ] 容斥原理以及各种反演 3.00

- [ ] 动态点分治 1.00

- [ ] 树上莫队 1.00

- [ ] 边分治 0.50

- [ ] 线性规划及其对偶 0.50

- [ ] 分块与树上分块 1.00

- [ ] 瓶颈路 0.50

- [ ] 度限制最小生成树 1.00

- [ ] 博弈 1.00

- [ ] 支配树 1.00

- [ ] 类欧几里得算法 0.50

- [ ] 动态凸包 1.00

- [ ] 仙人掌 1.00

- [ ] 稳定婚姻系统 0.50
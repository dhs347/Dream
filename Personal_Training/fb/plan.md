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

- [ ] 概率dp 2.00

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

  14.https://www.lydsy.com/JudgeOnline/problem.php?id=2201

  15.https://www.lydsy.com/JudgeOnline/problem.php?id=4008

  16.https://www.lydsy.com/JudgeOnline/problem.php?id=3566

  17.https://www.lydsy.com/JudgeOnline/problem.php?id=2337

  18.https://www.lydsy.com/JudgeOnline/problem.php?id=3143

  19.https://www.lydsy.com/JudgeOnline/problem.php?id=3191

  20.https://www.lydsy.com/JudgeOnline/problem.php?id=5292

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

- [ ] (min,+)卷积/最值反演/min-max容斥 1.00

- [ ] 高维前缀和 0.50

- [ ] 树形dp 2.00

- [ ] kd-tree 1.00

- [ ] 分治fft 2.00

- [ ] 状压dp 2.00

  O 1. http://acm.hdu.edu.cn/showproblem.php?pid=2820

  ​	求相邻差值小于等于k(k<=4)的排列数量，一种枚举排列的方法 	

- [ ] 组合数学与概率论 2.00

- [ ] 构造 1.00

- [ ] 二分图匹配 2.00

- [ ] 整体二分 1.00

- [ ] 网络流 5.00

- [ ] 贪心 2.00

- [ ] 高维偏序问题 1.00

- [ ] 最优比率生成树/最优比率环/01规划 0.50

- [ ] 虚树 1.00

- [ ] fft/ntt/fwt/fst等/生成函数与各种卷积 2.00

- [ ] 2-sat 2.00

- [ ] dancing_links及其他搜索优化 1.00

- [ ] 几类积性函数的求和方法/杜教筛/min25筛法等 2.00

- [ ] 普通dp及其优化 4.00

- [ ] 图论 4.00

- [ ] 笛卡尔树 1.00

- [ ] 差分约束 1.00

- [ ] 动态树 1.00

- [ ] 长链剖分 1.00

- [ ] 点分治 1.00

- [ ] 线性代数 1.00

- [ ] 背包问题 0.50

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

- [ ] 分治 3.00

- [ ] 瓶颈路 0.50

- [ ] 度限制最小生成树 1.00

- [ ] 博弈 1.00

- [ ] 支配树 1.00

- [ ] 类欧几里得算法 0.50

- [ ] 动态凸包 1.00

- [ ] 仙人掌 1.00

- [ ] 稳定婚姻系统 0.50
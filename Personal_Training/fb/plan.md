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

- [ ] 分治fft 2.00

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

- [x] 状压dp 2.00

  O 1. http://acm.hdu.edu.cn/showproblem.php?pid=2820

  ​	求相邻差值小于等于k(k<=4)的排列数量，一种枚举排列的方法，考虑有序插入数字，那么已有的数字可以表示成一些段，转移主要有合并，连接，新增一段，还要注意考虑边界状态。	

  O 2.https://www.lydsy.com/JudgeOnline/problem.php?id=1072

  ​	问有多少数字排列整除d，对余数装压

  O 3.https://www.lydsy.com/JudgeOnline/problem.php?id=1087

  ​	问N*N棋盘放k个国王有几种方案，需要先预处理两层之间的转移，不然复杂度不够

  O 4.https://www.lydsy.com/JudgeOnline/problem.php?id=1879

  ​	状压dp计数，状压dp要注意预处理转移，减少复杂度 

  O 5.https://www.lydsy.com/JudgeOnline/problem.php?id=2064

  ​	两堆数，每次可以合并两个，问最少几次可以两堆一样, 转移分步的思想要注意，可以减少复杂度 

  O 6.https://www.lydsy.com/JudgeOnline/problem.php?id=3717

  ​	n个物品放入m个包里，最少要几个包，状态为用了哪些物品，考虑状态之间的有序性，逐个插入物品

  O 7.https://www.lydsy.com/JudgeOnline/problem.php?id=3812

  ​	n点m边强连通子图计数，首先要会n点m边DAG计数，然后把枚举出度为零的点集容斥改为枚举缩点后出度为零的点集容斥

  O 8.https://www.lydsy.com/JudgeOnline/problem.php?id=4057

  ​	简单的状态表示和转移

  O 9.https://www.lydsy.com/JudgeOnline/problem.php?id=4145

  ​	状态为已经有哪些物品，分步转移优化

  O 10.https://www.lydsy.com/JudgeOnline/problem.php?id=4455

  ​	给n个点的图和树，给树不重复标号，树上边要在图中出现。用容斥来保证标号不重复，有重复标号等价于有标号没用到

  O 11.https://www.lydsy.com/JudgeOnline/problem.php?id=4565

  ​	一个01串可选k个合并为一个，得到对应2^k种权值中一个，求最大价值，区间dp，主要把合并过程看成一棵树，枚举后缀为0或1以及前缀的状态合并 

  12.https://www.lydsy.com/JudgeOnline/problem.php?id=4600

  O 13.http://acm.hdu.edu.cn/showproblem.php?pid=1074

  ​	简单题

  O 14.http://acm.hdu.edu.cn/showproblem.php?pid=3920

  ​	每次给固定选一个再枚举一个转移，复杂度低一些

  O 15.http://acm.hdu.edu.cn/showproblem.php?pid=4049

  ​	层之间的有序性要考虑清楚，最好写成分层的形式

  O 16.http://acm.hdu.edu.cn/showproblem.php?pid=4997

  ​	求边双联通子图个数, 需要容斥计算联通子图，不联通子图，单联通子图个数

  O 17.http://acm.hdu.edu.cn/showproblem.php?pid=5067

  ​	TSP问题

  O 18.http://acm.hdu.edu.cn/showproblem.php?pid=5094

  ​	bfs过程中对每个点开个状态来表示

- [ ] 背包问题 0.50

  O 1.http://codeforces.com/problemset/problem/868/E

  ​	树上抓人问题总结：决策就是每次不往来的方向走，除非其他方向全为空，以及不往空的方向走，dp的时候边界要特别注意，同时还套了一个给每个子树分配权值计算最大消耗是多少的子dp，只是这个过程有点像背包。

  2.http://codeforces.com/problemset/problem/920/D

  3.http://codeforces.com/problemset/problem/946/D

  O 4.https://www.lydsy.com/JudgeOnline/problem.php?id=1042

  ​	问多重背包构成n的方案数，如果种类很少可以容斥

  O 5.https://www.lydsy.com/JudgeOnline/problem.php?id=4247

  ​	消耗有正有负的背包，需要把增加容量的物品放在前面

  O 6.https://www.lydsy.com/JudgeOnline/problem.php?id=2287

  ​	背包求逆

  O 7.https://www.lydsy.com/JudgeOnline/problem.php?id=5215

  ​	背包结果乘个组合数，有个细节就是0个球分配到0个箱子要是1，不能用那个公式

  O 8.https://www.lydsy.com/JudgeOnline/problem.php?id=4753

  ​	0-1分数规划加上树上依赖型背包，就是暴力枚举子树合并即可，这个复杂度是O(n ^ 2)的，如果是size和K取min，那么复杂度是O(n * K)

  O 9.https://www.lydsy.com/JudgeOnline/problem.php?id=1065

  ​	比较好的树上背包问题，首先要解那个二元方程算出贡献式，之后要枚举环大小变成树上问题，然后要多记一维记录u到根的距离，注意两种转移式要严格注意下标，只有距离大于1才有切割的转移，不能合在一起写，不然会错乱。

  O 10.https://www.lydsy.com/JudgeOnline/problem.php?id=5390

  ​	本质上还是一种分步优化，每次只加一颗糖或一盒糖，不用再枚举糖数量了。

  11.https://www.lydsy.com/JudgeOnline/problem.php?id=2914

  O 12.http://codeforces.com/problemset/problem/868/E

  ​	很特殊的背包，如果容量为1 - i，设前缀容量为V，可以在枚举的时候只枚举到[V - (i - 1) ^ 2, V], 设x表示减的数，表示最优方案不会在前面丢掉x以上且后边取了x以上。

- [ ] 网络流 5.00

  【1】最大流（最小割）（重点）

  指定题目：

  1.http://www.lydsy.com/JudgeOnline/problem.php?id=2229

  2.http://www.lydsy.com/JudgeOnline/problem.php?id=1001

  3.http://www.lydsy.com/JudgeOnline/problem.php?id=1797

  4.http://www.lydsy.com/JudgeOnline/problem.php?id=2561

  5.http://codeforces.com/problemset/problem/813/D

  6.http://codeforces.com/problemset/problem/818/G

  7.http://codeforces.com/problemset/problem/802/C

  8.http://codeforces.com/problemset/problem/1082/G

  O 9.http://www.lydsy.com/JudgeOnline/problem.php?id=2039

  ​	一个图种要选一些点，点有花费，i,j一起选有贡献2 * Ei,j，不一起选有贡献-Ei,j，要转化成最小割模型，一般的套路是先算全部的价值减掉最小割，要去构造边权使割能代表每一种方案。好像有一种建图方法叫二元关系建图，只考虑存在两个点，然后推广。

  O 10.http://www.lydsy.com/JudgeOnline/problem.php?id=1189

  ​	把每个终点按时间展开成多个点，其他点按最短时间向终点连，然后每次按时间把终点向汇连一条流量为1的边，以及和上一次终点连接，看什么时候最大流等于点数。

  O 11.http://www.lydsy.com/JudgeOnline/problem.php?id=2150

  ​	最小不相交路径覆盖

  【2】费用流/带负权环（重点）

  指定题目：

  1.http://www.lydsy.com/JudgeOnline/problem.php?id=1877

  2.http://www.lydsy.com/JudgeOnline/problem.php?id=2668

  3.http://www.lydsy.com/JudgeOnline/problem.php?id=2597

  O 4.http://www.lydsy.com/JudgeOnline/problem.php?id=1834

  ​	费用流有每一次增广路长度不降的性质

  O 5.http://www.lydsy.com/JudgeOnline/problem.php?id=2539

  ​	数据有问题，有重边，以最后一次为准，二分图最大权匹配，可用费用流实现

  【网络流综合】

  建模阅读：https://wenku.baidu.com/view/a22336727fd5360cba1adb83.html
  《最小割模型在信息学竞赛中的应用》

  http://blog.csdn.net/qq_35649707/article/details/77482691

  1.http://www.lydsy.com/JudgeOnline/problem.php?id=4514

  2.http://www.lydsy.com/JudgeOnline/problem.php?id=1433

  3.http://www.lydsy.com/JudgeOnline/problem.php?id=1934

  4.http://www.lydsy.com/JudgeOnline/problem.php?id=1854

  5.http://www.lydsy.com/JudgeOnline/problem.php?id=1834

  6.http://www.lydsy.com/JudgeOnline/problem.php?id=1927

  7.http://www.lydsy.com/JudgeOnline/problem.php?id=2673

  8.http://www.lydsy.com/JudgeOnline/problem.php?id=3876

  9.http://www.lydsy.com/JudgeOnline/problem.php?id=3698

  10.http://www.lydsy.com/JudgeOnline/problem.php?id=2502

  11.http://www.lydsy.com/JudgeOnline/problem.php?id=2055

  12.http://poj.org/problem?id=2396

  13.http://acm.zju.edu.cn/onlinejudge/showProblem.do?problemCode=3229

  14.http://acm.zju.edu.cn/onlinejudge/showProblem.do?problemCode=2314

  15.http://www.lydsy.com/JudgeOnline/problem.php?id=2406

  16.http://www.lydsy.com/JudgeOnline/problem.php?id=3280

  O 17.http://www.lydsy.com/JudgeOnline/problem.php?id=3112

  ​	可以对偶完直接单纯形做，或者用前缀和变量代换，保证每一列刚好一个+1，-1，转费用流做。

  18.http://www.lydsy.com/JudgeOnline/problem.php?id=1917

  19.http://www.lydsy.com/JudgeOnline/problem.php?id=3218（此题有论文，好像是16或17年的）

  http://blog.csdn.net/outer_form/article/details/50847581

  20.http://www.lydsy.com/JudgeOnline/problem.php?id=1570

  21.http://www.lydsy.com/JudgeOnline/problem.php?id=3532

  22.http://www.lydsy.com/JudgeOnline/problem.php?id=3158

  O 23.http://www.lydsy.com/JudgeOnline/problem.php?id=2561

  ​	无向图确定两点为源汇的最小割

  24.http://www.lydsy.com/JudgeOnline/problem.php?id=1877

  25.http://www.lydsy.com/JudgeOnline/problem.php?id=1412

  26.http://www.lydsy.com/JudgeOnline/problem.php?id=3993

  27.https://vjudge.net/contest/189299#problem/C

  28.http://www.lydsy.com/JudgeOnline/problem.php?id=1070

  29.http://www.lydsy.com/JudgeOnline/problem.php?id=1458

  30.http://www.lydsy.com/JudgeOnline/problem.php?id=4823

  31.http://www.lydsy.com/JudgeOnline/problem.php?id=1822

  32.http://www.lydsy.com/JudgeOnline/problem.php?id=3681

  O 33.http://www.lydsy.com/JudgeOnline/problem.php?id=1497

  ​	最大权闭合子图，用最小割做，二元关系建图也可以

  34.http://www.lydsy.com/JudgeOnline/problem.php?id=1266

  35.http://www.lydsy.com/JudgeOnline/problem.php?id=1823

  36.http://www.lydsy.com/JudgeOnline/problem.php?id=1823

  37.http://www.lydsy.com/JudgeOnline/problem.php?id=1324

  38.http://www.lydsy.com/JudgeOnline/problem.php?id=2095

  39.http://acm.split.hdu.edu.cn/showproblem.php?pid=4807

  40.https://vjudge.net/contest/189689#problem/I

  41.http://hzwer.com/5844.html

  42.http://hzwer.com/5842.html

  43.http://hzwer.com/1955.html

  44.http://hzwer.com/1758.html

  45.http://www.lydsy.com/JudgeOnline/problem.php?id=3308

  O 46.http://www.lydsy.com/JudgeOnline/problem.php?id=3996

  ​	也是看作每个变量有取和不取两种，求出所有和后减去最小割，发现建图用二元关系建确实比较好想。

  47.http://www.lydsy.com/JudgeOnline/problem.php?id=3272

  O 48.http://www.lydsy.com/JudgeOnline/problem.php?id=3931

  ​	点上带流量限制，可以拆点去做

  49.http://www.lydsy.com/JudgeOnline/problem.php?id=1797

  50.http://www.lydsy.com/JudgeOnline/problem.php?id=3894

  51.http://www.lydsy.com/JudgeOnline/problem.php?id=1283

  52.http://www.lydsy.com/JudgeOnline/problem.php?id=3144

  53.http://www.lydsy.com/JudgeOnline/problem.php?id=2756

  54.http://www.lydsy.com/JudgeOnline/problem.php?id=2400

  55.http://www.lydsy.com/JudgeOnline/problem.php?id=1149

  56.http://www.lydsy.com/JudgeOnline/problem.php?id=2718

  57.http://www.lydsy.com/JudgeOnline/problem.php?id=2895

  58.http://www.lydsy.com/JudgeOnline/problem.php?id=1565

  59.http://www.lydsy.com/JudgeOnline/problem.php?id=2007

  60.http://www.lydsy.com/JudgeOnline/problem.php?id=2893

  61.http://www.lydsy.com/JudgeOnline/problem.php?id=2929

  62.http://www.lydsy.com/JudgeOnline/problem.php?id=1520

  63.http://www.lydsy.com/JudgeOnline/problem.php?id=2324

  64.http://www.lydsy.com/JudgeOnline/problem.php?id=3396

  65.http://www.lydsy.com/JudgeOnline/problem.php?id=3504

  66.http://www.lydsy.com/JudgeOnline/problem.php?id=1532

  67.http://www.lydsy.com/JudgeOnline/problem.php?id=1930

  68.http://www.lydsy.com/JudgeOnline/problem.php?id=2661

  69.http://www.lydsy.com/JudgeOnline/problem.php?id=1061

  70.http://www.lydsy.com/JudgeOnline/problem.php?id=1711

  O 71.http://www.lydsy.com/JudgeOnline/problem.php?id=2879

  ​	类似排队问题的贡献转为每个点是乘1到x，然后贪心地想乘的数字是从小到大有序的，所以每次增量更新这个图。

  72.http://www.lydsy.com/JudgeOnline/problem.php?id=3275

  73.http://www.lydsy.com/JudgeOnline/problem.php?id=2768

  74.http://www.lydsy.com/JudgeOnline/problem.php?id=2245

  75.http://www.lydsy.com/JudgeOnline/problem.php?id=1391

  76.http://www.lydsy.com/JudgeOnline/problem.php?id=2127

  77.http://www.lydsy.com/JudgeOnline/problem.php?id=2132

  78.http://www.lydsy.com/JudgeOnline/problem.php?id=3171

  79.http://www.lydsy.com/JudgeOnline/problem.php?id=2424

  80.http://www.lydsy.com/JudgeOnline/problem.php?id=1221

  81.http://www.lydsy.com/JudgeOnline/problem.php?id=1305

  O 82.http://www.lydsy.com/JudgeOnline/problem.php?id=1066

  ​	点上带限制的最大流

  83.http://poj.org/problem?id=1637

  84.http://hihocoder.com/problemset/problem/1393

  85.http://hihocoder.com/problemset/problem/1394

  86.http://hihocoder.com/problemset/problem/1398

  87.http://www.51nod.com/onlineJudge/questionCode.html#!problemId=1325

  88.http://acm.split.hdu.edu.cn/showproblem.php?pid=3879

  89.http://acm.split.hdu.edu.cn/showproblem.php?pid=3871

  90.https://nanti.jisuanke.com/t/15549

  91.http://acm.split.hdu.edu.cn/showproblem.php?pid=5772

  92.http://acm.split.hdu.edu.cn/showproblem.php?pid=4888

  93.http://acm.split.hdu.edu.cn/showproblem.php?pid=6214

  94.http://acm.split.hdu.edu.cn/showproblem.php?pid=1569

  95.http://www.lydsy.com/JudgeOnline/problem.php?id=4873

  96.http://www.lydsy.com/JudgeOnline/problem.php?id=3232

  97.http://www.lydsy.com/JudgeOnline/problem.php?id=5037

  98.http://www.lydsy.com/JudgeOnline/problem.php?id=3438

  99.http://www.lydsy.com/JudgeOnline/problem.php?id=3041

  100.http://poj.org/problem?id=2125

  101.http://acm.split.hdu.edu.cn/showproblem.php?pid=1530

  102.http://acm.split.hdu.edu.cn/showproblem.php?pid=3585

  103.http://acm.split.hdu.edu.cn/showproblem.php?pid=5277

  104.http://acm.split.hdu.edu.cn/showproblem.php?pid=5458

  105.http://acm.split.hdu.edu.cn/showproblem.php?pid=5556

  106.http://poj.org/problem?id=2400

  107.http://poj.org/problem?id=3281

  108.http://poj.org/problem?id=3469

  109.http://poj.org/problem?id=2195

  110.http://acm.zju.edu.cn/onlinejudge/showProblem.do?problemCode=2071

  111.http://acm.zju.edu.cn/onlinejudge/showProblem.do?problemCode=2760

  112.https://cn.vjudge.net/problem/SGU-242

  113.http://poj.org/problem?id=1149

  114.http://poj.org/problem?id=3498

  115.http://poj.org/problem?id=2391

  116.http://poj.org/problem?id=2112

  117.http://poj.org/problem?id=2455

  118.http://poj.org/problem?id=1698

  119.http://poj.org/problem?id=1459

  120.http://poj.org/problem?id=1087

  121.http://acm.zju.edu.cn/onlinejudge/showProblem.do?problemCode=3976

  122.https://cn.vjudge.net/problem/SGU-438

  123.http://acm.zju.edu.cn/onlinejudge/showProblem.do?problemCode=2071

  124.http://acm.zju.edu.cn/onlinejudge/showProblem.do?problemCode=2532

  125.http://poj.org/problem?id=1815

  126.http://poj.org/problem?id=3204

  127.http://acm.zju.edu.cn/onlinejudge/showProblem.do?problemCode=2587

  128.http://poj.org/problem?id=1966

  129.http://www.spoj.com/problems/OPTM/

  130.http://acm.zju.edu.cn/onlinejudge/showProblem.do?problemCode=2676

  131.http://poj.org/problem?id=3155

  132.http://acm.zju.edu.cn/onlinejudge/showProblem.do?problemCode=3241

  133.http://acm.hdu.edu.cn/showproblem.php?pid=3157

  134.https://cn.vjudge.net/problem/SGU-176

  135.http://poj.org/problem?id=2175

  136.http://poj.org/problem?id=3422

  137.http://poj.org/problem?id=2516

  138.http://poj.org/problem?id=2699

  139.http://poj.org/problem?id=3084

  140.http://poj.org/problem?id=3189

  141.http://poj.org/problem?id=3308

  142.http://codeforces.com/problemset/problem/884/F

  143.http://codeforces.com/problemset/problem/877/F

  144.http://codeforces.com/problemset/problem/818/G

  145.http://codeforces.com/gym/101564   （D题）

  146.http://codeforces.com/gym/101981/attachments I题




  【网络流复习·强化】

  1.http://codeforces.com/problemset/problem/808/F

  2.http://codeforces.com/problemset/problem/818/G

  3.http://codeforces.com/problemset/problem/813/D

  4.http://codeforces.com/problemset/problem/802/O

  5.http://codeforces.com/problemset/problem/793/G

  6.http://codeforces.com/problemset/problem/786/E

  7.http://codeforces.com/problemset/problem/736/E

  8.http://codeforces.com/problemset/problem/739/E

  9.http://codeforces.com/problemset/problem/730/I

  10.http://codeforces.com/problemset/problem/727/D

  11.http://codeforces.com/problemset/problem/724/E

  12.http://codeforces.com/problemset/problem/723/E

  13.http://codeforces.com/problemset/problem/717/G

  14.http://codeforces.com/problemset/problem/708/D

  15.http://codeforces.com/problemset/problem/704/D

  16.http://codeforces.com/problemset/problem/720/B

  17.http://codeforces.com/problemset/problem/653/D

  18.http://codeforces.com/problemset/problem/628/F

  19.http://codeforces.com/problemset/problem/611/H

  20.http://codeforces.com/problemset/problem/589/F

  21.http://codeforces.com/problemset/problem/546/E

  22.http://codeforces.com/problemset/problem/498/C

  23.http://codeforces.com/problemset/problem/491/C

  24.http://codeforces.com/problemset/problem/78/E

  25.http://uoj.ac/problem/77

  26.http://uoj.ac/problem/132

  27.http://uoj.ac/problem/85

  28.http://codeforces.com/problemset/problem/863/F


- [ ] simpson积分法 0.50

- [x] 最小割树 0.50

  O 1.https://www.luogu.org/problem/P3329

  O 2.https://www.luogu.org/problem/P4123

  O 3.https://www.luogu.org/problem/P4897

  ​	模板题，主要就是最小割只有n-1种，以及可以通过递归建出一个特殊的最小割树，有两点间最小割为树上路径最小值的性质	

- [x] 2-sat 2.00

  O 1.http://www.lydsy.com/JudgeOnline/problem.php?id=1997

  ​	判断一个环上连一些边能不能平面嵌入，每条边有可以在内部和外部两种，处理出之间的限制看2-sat有没有解即可

  O 2.https://www.lydsy.com/JudgeOnline/problem.php?id=2199

  ​	2-sat有两种解法，一种是缩点后求任意解，另一种是直接暴力dfs，可以确定字典序最小解，一个元素是不是必选之类的问题。

  O 3.http://www.lydsy.com/JudgeOnline/problem.php?id=1823

  O 4.http://poj.org/problem?id=3683

  O 5.http://poj.org/problem?id=3207

  O 6.http://www.lydsy.com/JudgeOnline/problem.php?id=4945

  O 7.https://www.lydsy.com/JudgeOnline/problem.php?id=4078

  ​	把图中点分成两个集合，使两个集合内的最大距离相加最小，枚举大的集合限制，有奇偶环优化，即不行的边不能构成基环，以及构成偶环的最小边不会是限制，用并查集维护，判断方案是否可行用2-sat。

  O 8.http://opentrains.snarknews.info/~ejudge/team.cgi?contest_id=010435 B

  首先建到达关系的图，缩完点后发现一个物品会被取到至少要访问到横线或竖线中一个，就是在新的DAG途中的两个点，题目转化为固定起点，判断在DAG中是否存在路径可以经过所有限制中至少一个，用2-sat建图求解。然后这个对普通应该图也是可行的，只是复杂度是O(n^2)的。

  9.http://codeforces.com/problemset/problem/780/D

  10.http://codeforces.com/problemset/problem/776/D

  11.http://codeforces.com/problemset/problem/587/D

  12.http://codeforces.com/problemset/problem/568/C

  13.http://codeforces.com/problemset/problem/538/H

  14.http://codeforces.com/problemset/problem/538/H

  15.http://codeforces.com/problemset/problem/228/E

  16.http://codeforces.com/problemset/problem/27/D

  17.http://codeforces.com/problemset/problem/193/A

  18.https://arc069.contest.atcoder.jp/tasks/arc069_d

- [ ] min25筛法 2.00

- [ ] dancing_links及其他搜索优化 1.00

- [ ] 长链剖分 1.00

- [ ] 线段树模拟费用流 1.00

- [ ] 最小树形图 1.00

- [ ] 容斥原理以及各种反演 1.00

- [ ] 稳定婚姻系统 0.50

- [x] 支配树 1.00

  1.https://www.luogu.org/problem/P2597

  ​	多建一个超级源，求支配树上size

- [ ] 瓶颈路 0.50

- [ ] 类欧几里得算法 0.50

- [ ] 线性代数 1.00

- [ ] 最优比率生成树/最优比率环/01规划 0.50

- [x] 高维偏序问题 1.00

- [ ] 普通dp及其优化 4.00

- [x] 图论 4.00

- [ ] 差分约束 1.00

- [ ] kd-tree 1.00

- [x] 线性规划及其对偶 0.50

- [ ] 度限制最小生成树 1.00

- [ ] 连分数 0.50

- [ ] 整体二分 1.00

- [ ] 构造 1.00

- [ ] 二分图匹配 2.00
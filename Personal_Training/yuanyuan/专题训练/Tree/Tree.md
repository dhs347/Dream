# Tree

2019/4/26 18:51 ~ 2019/4/30 18:40

2019/5/14 18:40 ~ 2019/5/16 18:51

2019/6/5 10:28 ~ 2019/6/10 20:16

2019/6/15 20:37 ~ 

## 记录

|  专题  | LCA  | 点分治  | 树链剖分 |  虚树  | 树直径  | 长链剖分 | 基环树  | dfs序 | 点分树  | LCT  | 括号序  |
| :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: |
|  题量  |  2   |  10  |  5   |  4   |  1   |  3   |  1   |  2   |  3   |  2   |  1   |

### LCA

`5` `20190426` `bzoj1146` `树状数组套主席树` 

将树上路径拆分成链的容斥之后，修改一个点的值会影响这个点的子树。

`2` `20190515` `bzoj3626` `LCA` `树链剖分` `思维`

主要的就是LCA的部分，比较考验思维

### 点分治

`1` `20190427` `bzoj1316` `点分治`

点分治裸题

`1` `20190427` `bzoj2152` `点分治`

点分治裸题

`1` `20190427` `bzoj2599` `点分治`

点分治裸题

`1` `20190427` `bzoj3365` `点分治`

点分治裸题

`2` `20190427` `bzoj1468` `点分治`

统计长度小等于 k 的路径数量。这题没给路径边权范围。

如果给了路径边权范围可以统计的时候用线段树维护小等于 c 的链数量，这样复杂度是 $nlog^2n$

如果容斥可以用双指针排序之后计数，复杂度一样，但是可以无视路径边权范围，比较好写。

`4` `20190427` `bzoj1758` `点分治` `单调队列` `实现`

二分答案，现在就是要找不带权长度在 [L, R] ，带权长度最长的路径长度是多少。

可以用线段树维护，复杂度是 $nlog^3n$

如果使用单调队列，需要先将子树按照深度排序。复杂度是 $nlog^2n$

`4` `20190514` `bzoj3451` `点分治` `概率` `FFT`

输出的四舍五入是骗人的，直接.4f就行。

`2` `20190516` `bzoj3697` `点分治`

`3` `20190605` `bzoj3784` `点分治` `思维`

解法一：二分下界。可以先把sort过的数组存起来优化复杂度。

解法二：转化成 `bzoj2006` 做。

解法二会好写点。

`3` `20190606` `bzoj4016` `点分治` `最短路径树`

### 树链剖分

`1` `20190427` `bzoj2243` `树链剖分`

树链剖分裸题

`3` `20190514` `bzoj3083` `树链剖分`

路径修改，子树查询

换根

`5` `20190515` `bzoj3531` `树链剖分`

给定树，每个点有个有序对(a, b)

1、修改某点的a

2、修改某点的b

3、求路径(u, v)上有序对第一维是a的b之和

4、求路径(u, v)上有序对第一维是a的b最大

**解法一：**

树剖，线段树上每个节点开一个map。每次修改只会修改log个map。

**解法二：**

树剖，建【宗教个数】棵线段树。动态开点。

**总结：**

1、需要处理最大值，最大值没有可减性

2、宗教个数很多

3、操作数不多

→ 一般使用数据结构优化，树路径问题，使用树剖

`2` `20190515` `bzoj3626` `LCA` `树链剖分` `思维`

主要的就是LCA的部分，比较考验思维

`1` `20190610` `bzoj4034` `树链剖分` `dfs序` `括号序` `线段树`

https://www.cnblogs.com/skylee03/p/8066974.html#commentform

树剖做法比其他两个多了log，但是比较通用。其他两个暂时还不知道有啥用。

### 虚树

`1` `20190427` `bzoj2286` `虚树` `树dp`

`2` `20190515` `bzoj3611` `虚树` `树dp`

树dp调了一会儿

`2` `20190605` `bzoj3879` `虚树` `SAM` `后缀树`

前置技能是 `bzoj3238`

`5` `20190615` `bzoj4912` `虚树` `前后缀优化建图` `dp`

### 树直径

`2` `20190427` `bzoj2870` `树直径`

对两棵树加边形成新的树，新的树的直径一定是旧的树直径中的两个点

### 长链剖分

`3` `20190427` `bzoj3252` `长链剖分` `贪心`

`3` `20190516` `bzoj3653` `长链剖分` 

`5` `20190610` `bzoj4543` `长链剖分` `dp`

- 前置题目 bzoj3522，其实没啥联系
- dp状态不好想
  - $g[u][i]$ 表示 u 的子树中有多少个 pair 对只要在 u 顶上加一条长度 i 的就凑成一个合法的三元组了
  - $f[u][i]$ 表示 u 的子树中有多少个点与 u 距离 i
  - dep[u] 表示 u 与子树中最远的叶子距离
  - 显然 i 的范围是 0 到 dep[u]
- 转移
  - 一棵子树一棵子树的加，考虑新加子树与原来那一坨对答案的贡献
  - 考虑子树中已有的 g 数组，新子树与原来一坨对当前 g 的贡献
  - f 比较简单
- 长链剖分
  - f 比较简单
  - g 的过程就是把最前面那个删掉，在最后面加上两个。首先要倒着存，其次数组开两倍。坐标重定位推一推。

### 基环树

`3` `20190516` `bzoj3648` `基环树`

首先删掉环中一条边，做点分治。

然后计数经过这条边的。

### dfs序

> **修改时修改一段dfs序里的内容，查询时单点查询**

`3` `20190605` `bzoj3991` `思维` `dfs序`

`3` `20190610` `bzoj4034` `树链剖分` `dfs序` `括号序` `线段树`

https://www.cnblogs.com/skylee03/p/8066974.html#commentform

树剖做法比其他两个多了log，但是比较通用。其他两个暂时还不知道有啥用。

### 点分树

`3` `20190605` `bzoj4012` `点分树` `树链剖分` `lca` `主席树`

**解法一：**

点分治可以查询块内的点与当前重心的信息，点分树是将这个信息减去重复统计的。

通常先把点分树建出来，然后像点分治那样正常统计。

统计的细节稍微推一下。

**解法二：**

dis(a, b) = dis(a) + dis(b) - 2 * dis(lca(a, b))

离线：和`bzoj3626`差不多。线段树的部分可以标记不下传。

在线：用主席树。

`2` `20190610` `bzoj4372` `点分树` `线段树`

`3` `20190615` `bzoj5912` `点分树` `动态点分治` `树直径`

### LCT

`3` `20190607` `bzoj4025` `LCT` `线段树分治` `可撤销并查集`

`3` `20190615` `bzoj5912` `点分树` `动态点分治` `树直径`

### 括号序

> **修改时区间修改，查询时查询前缀和**

`3` `20190610` `bzoj4034` `树链剖分` `dfs序` `括号序` `线段树`

https://www.cnblogs.com/skylee03/p/8066974.html#commentform

树剖做法比其他两个多了log，但是比较通用。其他两个暂时还不知道有啥用。

### 思维

`3` `20190427` `bzoj2006` `思维`

### 线段树合并

`1` `20190516` `bzoj3653` `线段树合并`

## 题目

http://www.lydsy.com/JudgeOnline/problem.php?id=5210

http://www.lydsy.com/JudgeOnline/problem.php?id=5287

http://www.lydsy.com/JudgeOnline/problem.php?id=5329

http://www.lydsy.com/JudgeOnline/problem.php?id=5362

http://www.lydsy.com/JudgeOnline/problem.php?id=3435

http://www.lydsy.com/JudgeOnline/problem.php?id=3914

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

1.http://poj.org/problem?id=1741

http://acm.hdu.edu.cn/showproblem.php?pid=5571

http://acm.hdu.edu.cn/showproblem.php?pid=6104

2.http://acm.hdu.edu.cn/showproblem.php?pid=4812

3.http://codeforces.com/contest/161/problem/D

9.http://uoj.ac/problem/33

10.http://www.spoj.com/problems/FTOUR2/

15.http://poj.org/problem?id=1987

21.http://www.spoj.com/problems/QTREE5/

22.https://cn.vjudge.net/contest/187749#problem/G

23.http://codeforces.com/problemset/problem/914/E

24.http://codeforces.com/problemset/problem/960/E

2.http://www.spoj.com/problems/QTREE4/

1.https://vijos.org/d/Bashu_OIers/p/5a79a3e1d3d8a103be7e2b81

4.http://codeforces.com/problemset/problem/1009/F

8.http://acm.hdu.edu.cn/showproblem.php?pid=6370

9.http://acm.hdu.edu.cn/showproblem.php?pid=6403

10.http://acm.hdu.edu.cn/showproblem.php?pid=5304

11.http://acm.hdu.edu.cn/showproblem.php?pid=6393

12.http://acm.hdu.edu.cn/showproblem.php?pid=5967

13.https://agc008.contest.atcoder.jp/tasks/agc008_e

9.http://codeforces.com/problemset/problem/613/D

10.http://codeforces.com/problemset/problem/966/E

11.http://codeforces.com/problemset/problem/986/E

12.http://codeforces.com/problemset/problem/809/E

13.http://acm.hdu.edu.cn/showproblem.php?pid=6035

14.https://cn.vjudge.net/problem/CodeChef-BTREE

或者：https://www.codechef.com/problems/BTREE

2.http://acm.hdu.edu.cn/showproblem.php?pid=4095

4.http://acm.hdu.edu.cn/showproblem.php?pid=5324

7.http://acm.hdu.edu.cn/showproblem.php?pid=6406

8.http://acm.hdu.edu.cn/showproblem.php?pid=5412

11.http://poj.org/problem?id=1785

12.http://poj.org/problem?id=2201

1.http://codeforces.com/gym/102012/problem/G

https://www.luogu.org/problemnew/show/U21715

## TBD

### LCT进阶

http://www.lydsy.com/JudgeOnline/problem.php?id=2759

[题解](https://www.cnblogs.com/yoyoball/p/9311127.html)

这题需要改板子

### 过的人很少的题

http://www.lydsy.com/JudgeOnline/problem.php?id=2543
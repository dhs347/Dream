# Tree

2019/4/26 18:51 ~ 2019/4/30

2019/5/14 18:40 ~

## 记录

|  专题  | LCA  | 点分治  | 树链剖分 |  虚树  | 树直径  | 长链剖分 | 基环树  |
| :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: |
|  题量  |  2   |  7   |  4   |  2   |  1   |  1   |  1   |

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

### 虚树

`1` `20190427` `bzoj2286` `虚树` `树dp`

`2` `20190515` `bzoj3611` `虚树` `树dp`

树dp调了一会儿

### 树直径

`2` `20190427` `bzoj2870` `树直径`

对两棵树加边形成新的树，新的树的直径一定是旧的树直径中的两个点

### 长链剖分

`3` `20190427` `bzoj3252` `长链剖分` `贪心`

### 基环树

`3` `20190516` `bzoj3648` `基环树`

首先删掉环中一条边，做点分治。

然后计数经过这条边的。

### 思维

`3` `20190427` `bzoj2006` `思维`

### 线段树合并

`1` `20190516` `bzoj3653` `线段树合并`

## 题目

http://www.lydsy.com/JudgeOnline/problem.php?id=3653

http://www.lydsy.com/JudgeOnline/problem.php?id=3697

http://www.lydsy.com/JudgeOnline/problem.php?id=3730

http://www.lydsy.com/JudgeOnline/problem.php?id=3784

http://www.lydsy.com/JudgeOnline/problem.php?id=3784

http://www.lydsy.com/JudgeOnline/problem.php?id=3879

http://www.lydsy.com/JudgeOnline/problem.php?id=3914

http://www.lydsy.com/JudgeOnline/problem.php?id=3991

http://www.lydsy.com/JudgeOnline/problem.php?id=4012

http://www.lydsy.com/JudgeOnline/problem.php?id=4016

http://www.lydsy.com/JudgeOnline/problem.php?id=4025

http://www.lydsy.com/JudgeOnline/problem.php?id=4034

http://www.lydsy.com/JudgeOnline/problem.php?id=4543

http://www.lydsy.com/JudgeOnline/problem.php?id=4712

http://www.lydsy.com/JudgeOnline/problem.php?id=4912

http://www.lydsy.com/JudgeOnline/problem.php?id=5210

http://www.lydsy.com/JudgeOnline/problem.php?id=5287

http://www.lydsy.com/JudgeOnline/problem.php?id=5329

http://www.lydsy.com/JudgeOnline/problem.php?id=5362

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

### 动态点分治

http://www.lydsy.com/JudgeOnline/problem.php?id=1095

### 过的人很少的题

http://www.lydsy.com/JudgeOnline/problem.php?id=2543
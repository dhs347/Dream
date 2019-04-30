# Tree

2019/4/26 18:51 ~ 

## 记录

|  专题  | LCA  | 点分治  | 树链剖分 |  虚树  | 树直径  | 长链剖分 |
| :--: | :--: | :--: | :--: | :--: | :--: | :--: |
|  题量  |  1   |  6   |  1   |  1   |  1   |  1   |

### LCA

`5` `20190426` `bzoj1146` `树状数组套主席树` 

将树上路径拆分成链的容斥之后，修改一个点的值会影响这个点的子树。

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

### 树链剖分

`1` `20190427` `bzoj2243` `树链剖分`

树链剖分裸题

### 虚树

`1` `20190427` `bzoj2286` `虚树` `树dp`

### 树直径

`2` `20190427` `bzoj2870` `树直径`

对两棵树加边形成新的树，新的树的直径一定是旧的树直径中的两个点

### 长链剖分

`3` `20190427` `bzoj3252` `长链剖分` `贪心`

### 思维

`3` `20190427` `bzoj2006` `思维`

## 题目

http://www.lydsy.com/JudgeOnline/problem.php?id=3083

http://www.lydsy.com/JudgeOnline/problem.php?id=3451

http://www.lydsy.com/JudgeOnline/problem.php?id=3531

http://www.lydsy.com/JudgeOnline/problem.php?id=3611

http://www.lydsy.com/JudgeOnline/problem.php?id=3626

http://www.lydsy.com/JudgeOnline/problem.php?id=3648

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
# 动态dp

2019/6/10 20:40 ~ 2019/6/15 15:50

中间咕了两三天

## 参考资料

https://www.cnblogs.com/YoungNeal/p/10360291.html

http://immortalco.blog.uoj.ac/blog/2625

https://www.luogu.org/blog/gkxx-is-here/what-the-hell-is-ddp （洛谷日报 #130）

https://www.luogu.org/problemnew/solution/P4719

## 动态dp

1、用树剖实现复杂度是 $O(nlog_2^2n*矩乘复杂度)$

2、LCT实现复杂度是 $O(nlog_2n)$，常数比较大

只需要用到其中的access操作。

3、全局平衡二叉树实现复杂度是 $O(nlog_2n)$，常数非常优秀，可以替代一类静态树上的路径问题。

## 题目

https://www.luogu.org/problemnew/show/P4719

- 写出dp转移
- 修改结点价值，维护dp值
  - 序列问题可以用数据结构维护矩阵乘法
  - 树上问题需要先树剖，维护和重儿子之间的关系，修改一个点的时候，它所在重链顶端节点的父亲的矩阵会改变，需要一直跳上去更新。只维护重链顶端的节点的真实dp值，其他节点的dp值均需要在线查询。

https://www.lydsy.com/JudgeOnline/problem.php?id=4712

https://www.lydsy.com/JudgeOnline/problem.php?id=5210

http://uoj.ac/problem/441

https://www.luogu.org/problemnew/show/P4751

## TBD

https://www.lydsy.com/JudgeOnline/problem.php?id=4732

https://www.lydsy.com/JudgeOnline/problem.php?id=4911

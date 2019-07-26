# Kruskal重构树

2019/7/25 21:37 ~ 2019/7/26 14:57

## 参考资料

https://blog.csdn.net/hwzzyr/article/details/81190442

## Kruskal重构树

### 性质

是一个二叉堆

原树两点之间的边权最大值 / 原图两点之间所有路径的最大边权最小值 -> 是重构树上两点Lca的权值

重构树中代表原树中的点的节点全是叶子节点，其余每个节点都代表了某条边

## 题目

1.![a](a.png)

**原树两点之间的边权最大值 / 原图两点之间所有路径的最大边权最小值 -> 是重构树上两点Lca的权值**

2.https://www.lydsy.com/JudgeOnline/problem.php?id=3551

点 v 向上爬到权值为 w 的内部节点，该节点的子树都是 v 能到达的点。

3.http://uoj.ac/problem/393

和上题差不多

4.http://uoj.ac/problem/407

本质是要判断两段 dfs 序是否有相同元素，将每个元素用 $(x, y)$ 表示它在第一段、第二段出现位置，问题转化为求二维矩形内部是否有点。

5.https://ac.nowcoder.com/acm/contest/883/E
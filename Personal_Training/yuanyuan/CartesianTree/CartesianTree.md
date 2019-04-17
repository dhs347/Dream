# Cartesian Tree

2019/4/14 10:30 ~ 2019/4/17 15:26

## 参考资料

https://www.cnblogs.com/gtarcoder/p/4702853.html

## Cartesian Tree

从下标来看，满足二叉搜索树的特性，从value来看，满足堆的性质

![](https://oss.v8cloud.cn/images/9d74e2c8447938ef046a26300004712c.png)

## 模板

```c++
// desc : bud a cartesion tree from a[0] .. a[n - 1]
// time : O(N)
// !!!! : return rt, a[n] will be rewrite
int ls[N], rs[N];
int cartesionTree(int a[], int n) {
	a[n] = INT_MAX;
	vi v(1, n);
	fill_n(ls, n, -1), fill_n(rs, n, -1);
	rep(i, 0, n) {
		while (a[v.back()] < a[i])
			ls[i] = v.back(), v.pop_back();
		v.pb(rs[v.back()] = i);
	}
	return v[1];
}
```

## 题目

1、利用了笛卡尔树既有堆的性质，又有二叉搜索树的性质。

2、枚举区间最小的值，将区间分成两部分。就可以进行计数或者dp。

3、用treap维护笛卡尔树。

http://acm.hdu.edu.cn/showproblem.php?pid=1506

http://acm.hdu.edu.cn/showproblem.php?pid=4125

https://www.lydsy.com/JudgeOnline/problem.php?id=2616

http://acm.hdu.edu.cn/showproblem.php?pid=6305

http://acm.hdu.edu.cn/showproblem.php?pid=6044

把区间画成树状结构会发现有点像笛卡尔树，按照左端点升序，右端点降序排列之后发现这是这个树状结构的前序遍历，因此直接前序遍历这棵树即可还原。

https://www.lydsy.com/JudgeOnline/problem.php?id=2658


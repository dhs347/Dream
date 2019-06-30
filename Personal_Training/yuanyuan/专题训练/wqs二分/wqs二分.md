# wqs二分

## 学习资料

https://m.doc88.com/p-949564862405.html

https://blog.csdn.net/CHHNZ/article/details/78827430

http://codeforces.com/blog/entry/49691

https://blog.csdn.net/chhnz/article/details/78846104

https://www.cnblogs.com/CreeperLKF/p/9045491.html



## 总结

这一类题目，要求带限制选择严格k个物品，使得目标函数最优化

特点是：目标函数关于物品选择的个数k单调，设为g(k)，g(k)关于k单峰（形状是凸壳）

朴素的dp复杂度太高，如果去掉物品个数那一维的话，往往可以优化到O(n)或者较优的复杂度

二分一个C，表示每选择一个物品的Cost，则目标函数变为f(k)=g(k)-k*C

注意到：f'(k)=g'(k)-C单调，因此可以考虑二分C，dp求出全局无物品个数限制意义下的dp最优值和物品个数(D,X)

用X与题目给的k比较，调整二分的方向；最后获得X=k，ans=D+C*k

当然，对于C，是加入答案，还是从中扣除，根据题目具体情况而定



## 细节说明

往往我们优化过的dp，每次求的X是能够取到最优dp值的最大物品个数，

也就是说如果当前物品必取，大于等于不取当前沿用之前最值，就更新，然后与k比较(>=k为一边方向)

这样做的根据是：我们总是找使得x>=k成立的最大或最小的C(C如果是小数，不必十分精确)

每次只要符合这个要求，那么我们记录二元pair(dp最优值，物品个数)

设想一下，比我们找的C次一点的C'，会使得h(C')=x' < k成立，那么[h(C')+1,h(C)]这一段C相同，因而dp最优值相同

而题目的k必然在其中的，因此不影响答案求法的正确性



## 题目

1.http://codeforces.com/problemset/problem/958/E2

2.http://codeforces.com/problemset/problem/739/E

3.https://www.lydsy.com/JudgeOnline/problem.php?id=2654

4.http://poj.org/problem?id=1160

5.https://www.lydsy.com/JudgeOnline/problem.php?id=5252

6.https://www.lydsy.com/JudgeOnline/problem.php?id=5311

7.http://codeforces.com/gym/101981/attachments B题

8.http://uoj.ac/problem/240
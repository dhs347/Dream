$$
\max(S)=\sum_{T \subseteq S}(-1)^{|T|+1}\min(T)
$$

$$
\min(S)=\sum_{T \subseteq S}(-1)^{|T|+1}\max(T)
$$

$$
kth\max(S)=\sum_{T \subseteq S} (-1)^{|T|-k} {|T|-1 \choose k-1} \min(T)
$$

主要用于一些求期望的题目，求一些随机变量的最大值可以转化为求这些随机变量最小值实现

kthmax容斥这个系数是可以关于k进行递推的，如洛谷4707




$$
lcm(S)=\prod_{T\subset S}gcd(T)^{(-1)^{|T|+1}}
$$
若有
$$
g(n)=\prod _{T\subset 2^{[n]}}f(gcd_{i\in T}(i))^{(-1)^{|T|+1}}
$$
可构造出h满足
$$
f(n)=\prod _{d|n}h(d)
$$
于是
$$
g(n)=\prod _{d=1}^{n}h(d)
$$

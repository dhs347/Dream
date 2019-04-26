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


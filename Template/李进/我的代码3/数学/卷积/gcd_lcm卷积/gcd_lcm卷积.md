卷积是一种比较耗费计算资源的基础数学运算，在数学上我们处理卷积的一般方法都是通过各种变换或者转化，使得问题转化为比较容易计算的计算类型(比如序列点积)，想方设法加速计算的效率，当然这需要卷积本身具有一定的数学性质。

***gcd*卷积**是说我们需要计算的卷积公式为：
$$
\huge
\begin{equation}

c_k=\sum_{(i,j)=k}a_i*b_j

\end{equation}
$$

$$
\Large
\begin{equation}

令A,B,C分别为a,b,c的类点值序列(闭区间[1,n],下标超过n值为0)，\\
其中一个定义如下：\\
A_k=\sum_{k|d}a_d \\

那么即有：\\

C_k=\sum_{k|d}c_d=\sum_{k|d}\sum_{(i,j)=d}a_i*b_j=\sum_{k|(i,j)}a_i*b_j \\
=\sum_{k|i}\sum_{k|j}a_i*b_j=(\sum_{k|i}a_i)*(\sum_{k|i}b_i)=A_k*B_k \\

我们得到：\\
C=A\bullet B \\

序列反演公式： \\
a_k=\sum_{k|d}A_d*\mu_{\frac{d}{k}}

\end{equation}
$$

***lcm*卷积**是说我们需要计算的卷积公式为：
$$
\huge
\begin{equation}

c_k=\sum_{[i,j]=k}a_i*b_j

\end{equation}
$$

$$
\Large
\begin{equation}

令A,B,C分别为a,b,c的类点值序列，其中一个定义如下：\\
A_k=\sum_{d|k}a_d \Leftrightarrow A=a \circ I \\

那么即有：\\

C_k=\sum_{d|k}c_d=\sum_{d|k}\sum_{[i,j]=d}a_i*b_j=\sum_{[i,j]|k}a_i*b_j \\
=\sum_{i|k}\sum_{j|k}a_i*b_j=(\sum_{i|k}a_i)*(\sum_{i|k}b_i)=A_k*B_k \\

我们得到：\\
C=A\bullet B \\

序列反演公式： \\
a_k=\sum_{d|k}A_d*\mu_{\frac{k}{d}}=\sum_{x*y=k}A_x*\mu_y \Leftrightarrow a=A \circ\mu

\end{equation}
$$


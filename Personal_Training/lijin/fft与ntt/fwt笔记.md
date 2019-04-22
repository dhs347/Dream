fwt基本原理和性质



https://blog.csdn.net/john123741/article/details/76576925



性质：
$$
fwt(A+B)=fwt(A)+fwt(B)\\

+为按位加
$$


变换：
$$
fwt(A \circ B)=fwt(A)*fwt(B)\\
*为按位乘
$$
几种卷积：
$$
\begin{array}{l}{\text { xor }} \\ 

{t f(A)=\left(t f\left(A_{0}\right)+t f\left(A_{1}\right), t f\left(A_{0}\right)-t f\left(A_{1}\right)\right)} 

\\ {u t f(A)=\left(u t f\left(\frac{A_{0}+A_{1}}{2}\right),\left(\frac{A_{0}-A_{1}}{2}\right)\right.} 

\\ {\text { and }} 

\\ {t f(A)=\left(t f\left(A_{0}\right)+t f\left(A_{1}\right), t f\left(A_{1}\right)\right)} 

\\ {u t f(A)=\left(u t f\left(A_{0}\right)-u t f\left(A_{1}\right), u t f\left(A_{1}\right)\right)} 

\\ {\text { or } 

\\tf(A)=\left(t f\left(A_{0}\right), t f\left(A_{1}\right)+t f\left(A_{0}\right)\right)} 

\\ {\operatorname{tf}(A)=\left(t f\left(A_{0}\right), t f\left(A_{1}\right)+t f\left(A_{0}\right)\right)} 

\\ {u t f(A)=\left(u t f\left(A_{0}\right), u t f\left(A_{1}\right)-u t f\left(A_{0}\right)\right)}\end{array}
$$



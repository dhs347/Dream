/*
* FT_fft_2D 使用说明
*
* 【接口说明】
*
* cp get(double x) ：获取一个辐角为 x 的复数
*
* void FFT(cp *a,int n,int op) ：变换接口，注意： op=1 为正卷积， op=-1 为逆卷积
*
* void FFT(cp a[ ][_M],int n,int op) ：行变换接口，逐行进行正 / 逆变换
*
* void Transpose(T a[ ][_M],int n) ：转置接口
*
* void Reverse(V a[ ][_M],int n,int m) ：翻转接口
*
* void Shift(V a[ ][_M],int n,int m,int p,int q) ：移位接口，将矩阵 a 的 (n,m) 整体移位到 (0,0) 长度保留 p 和 q ( 长和宽 )
*
* void In(cp p[][_M],int len,V a[][_M],int n,int m) ：数据填充接口
*
* void Out(V a[][_M],int n,int m,cp p[][_M],int len) ：数据提取接口
*
* void Multiply(V A[][_M],int n,V B[][_M],int m,V C[][_M],int &len,int op=0) ：
*
* 乘法接口，表示 n * n 的矩阵 A 乘上 m*m 的矩阵 B ，结果放到 C 中，规模为 len * len 且计算并返回到 len 中， op=1 为差卷积
*/
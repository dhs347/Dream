###NTT_2D使用说明



**【接口说明】**



**1）FT部分：**

void Init(int _K,int p)：两个参数为用户所期望的结果最大次数，和模数

void init_w(int m)：预处理长度为1<<m的w数组和rev数组

void FFT(vector<V>& A,int m,int op)：变换接口，长度为1<<m，op为0表示普通和卷积，op为1表示差卷积

void multiply(const vector<V>& A,const vector<V>& B,vector<V> *C)：

乘法接口，注意第三个参数传入指针



**2）Matrix部分：**

void Set_m(int _m,int x=0)：将每列resize为m，不足元素填充为x

void Set_n(int _n)：将行扩充为n

void Set(int _n,int _m,int x=0)：设置矩阵规模

**void Transpose()：转置接口**

void Reverse()：翻转接口，不光行翻转，列也翻转

void Shift(int x,int y)：移位接口，将(x,y)设置为矩阵左上角元素，整体移位，不足部分填充0

**void FFT(FT<int> &T,int len,int op)：批量行变换，对每行进行正/逆变换**

void print() const：打印接口

void Normalize(int _p)：规范化接口，保证矩阵中每个元素都严格非负且已模

void Random()：产生随机数，填充此矩阵

==：矩阵可以直接比较判等



**3）Calculator部分：**

void Init(int p)：预处理模数

**void Multiply(const Matrix &A,const Matrix &B,Matrix &C,int op=0)：**

**乘法接口，op=0为和卷积，op=1为差卷积**

void Multiply_B(const Matrix &A,const Matrix &B,Matrix &C)：

暴力和卷积接口

void Multiply_B_sub(const Matrix &A,const Matrix &B,Matrix &C)：

暴力差卷积接口
```
固定框架

import java.io.*;
import java.math.*;
import java.util.*;
public class Main {
    //内部类，类似结构体
    //static class A {...}
    public static void main(String[] args) {
        Scanner cin=new Scanner(System.in);
    } 
}


//各种类型读入
int n;n=cin.nextInt();
BigDecimal t;t=cin.nextBigDecimal();  
BigInteger a;a=cin.nextBigInteger();
double b;b=cin.nextDouble();
string s;s=cin.nextLine();


//各种操作(大数！！) +- * / mod
a=BigInteger.valueOf(0);//赋值
a=a.add(a);
a=a.mod(x);
a=a.divide(a);
a=a.multiply(a);
a=a.subtract(a);
if(a.compareTo(x)==0);//判相等 a>x返回1 <返回-1 

//double 的sqrt操作,BigDecimal
import java.lang.*;
Math.sqrt(a);


//BigDecimal无法整除时需要设置精度 divide(,小数点后位数,上/下取整)
a/b
BigDecimal a=a.divide(b,105,RoundingMode.CEILING);//取上整
BigDecimal a=a.divide(b,105,RoundingMode.FLOOR);//取下整

RoundingMode是一个枚举类，有一下几个常量：UP，DOWN，CEILING，FLOOR，HALF_UP，HALF_DOWN，HALF_EVEN，UNNECESSARY
UP 远离0方向舍入，DOWN向0方向舍入
CEILING 取上整（正数类似UP，负数类似DOWN），FLOOR取下整
HALF_UP四舍五入
            

//排序    
int n=cin.nextInt();
BigInteger a[]=new BigInteger[n];
for(int i=0;i<n;++i) a[i]=cin.nextBigInteger();
Arrays.sort(a);

    

//各种输出
System.out.println();
System.out.printf("%.5f\n",b);//类似printf
```
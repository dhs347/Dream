#include <ext/rope>
using namespace __gnu_cxx;

//index : [0..sz(rp))
rope<char> rp;

// 在任意处插入字符数组
rp.push_back(ch);             // 在末尾插入
rp.insert(cur, 字符数组 );    // 在 cur 处插入字符数组

// 删除任意片段
rp.erase(cur, len);           // 删除 cur 开始的 len 个字符

rp.replace(cur, 字符数组 );   // 删除 cur 处的字符，换成字符数组

// 取出任意片段
rp.copy(cur, len, 字符数组 ); // 复制 cur 处开始的 len 个字符到字符数组
rp.at(cur);                   // 取第 cur 个字符 
rp[cur];                      // 同上
rp.substr(cur, len);          // 提取从 cur 处开始的 len 个字符

// 可持久化
rp[i] = rp[i - 1];            // 可持久化, O(1), 直接拷贝根节点

/* 

* 一）翻转操作
*  1. 维护一正一反两个 rope 
*  2. 翻转等价于交换两个子串

* 二）区间循环位移
*  1. 拆成多个子串连在一起

* 三）区间 a -> b, b -> c, c -> d ... z -> a 
*  1. 维护 26 个 rope 

*/
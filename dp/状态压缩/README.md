<!--
 * @Description: 
 * @Author: shadow221213
 * @Date: 2023-11-01 13:56:45
 * @LastEditTime: 2023-11-02 15:58:42
-->

# <div align="center">状态压缩</div>
<!-- TOC -->

- [状态压缩](#状态压缩)
  - [方法：](#方法)
  - [例题：](#例题)

<!-- /TOC -->

## 方法：

1. x 是否是 y 的子集：`(x & y) == x`
2. x 是否有连续的 1：`x & (x - 1)`
3. x 的二进制中 1 的个数：`__builtin_popcount(x)`
4. dp时遍历集合内所有情况：
```C++
int cnt = sub;
while(cnt) {
    if(val.count(cnt)) dp[i | cnt] = min(dp[i | cnt], dp[i] + val[cnt]);
    cnt = (cnt - 1) & sub;
}
```


## 例题：

*1681. 最小不兼容性*

*1494. 并行课程 II*

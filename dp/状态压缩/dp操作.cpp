/*
 * @Description:
 * @Author: shadow221213
 * @Date: 2023-10-17 21:52:20
 * @LastEditTime: 2023-10-24 19:48:09
 */
#include <bits/stdc++.h>
using namespace std;

// x 是否是 y 的子集
bool isSubset(int x, int y) {
    return (x & y) == x;
}

// x 是否有连续的1
bool isContinue1(int x) {
    return x & (x - 1);
}

// x 的二进制中1的个数
int numOfBinary(int x) {
    return __builtin_popcount(x);
}

/*
int cnt = sub;
while(cnt) {
    if(val.count(cnt)) dp[i | cnt] = min(dp[i | cnt], dp[i] + val[cnt]);
    cnt = (cnt - 1) & sub;
}
*/

// 例题：
// 1681. 最小不兼容性
// 1494.并行课程 II
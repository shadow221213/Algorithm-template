/*
 * @Description:
 * @Author: shadow221213
 * @Date: 2023-11-09 15:16:40
 * @LastEditTime: 2023-11-15 12:23:03
 */
#include<bits/stdc++.h>
using namespace std;

signed main( ) {
    auto dfs = [&] ( ) -> int {
        auto calc = [&] (auto &&self) -> int {
            // ...
            return self(self);
            };
        return calc(calc);
        };
}
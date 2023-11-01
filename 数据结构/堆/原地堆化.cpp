/*
 * @Description:
 * @Author: shadow221213
 * @Date: 2023-10-28 19:26:25
 * @LastEditTime: 2023-10-28 19:40:44
 */

#include <bits/stdc++.h>
using namespace std;

#define all(x) (x).begin(), (x).end()
#define Sum(x) accumulate(all(x), 0ll)

class Solution {
public:
    long long pickGifts(vector<int>& gifts, int k) {
        // 就地建堆，保证最大值在最前面，其他不确定，O(n)
        make_heap(all(gifts));

        while( k-- && gifts[0] > 1 ) {
            // 将堆顶元素移动到最后，并将新的最大值置于最前面
            pop_heap(all(gifts));
            gifts.back( ) = sqrt(gifts.back( ));
            // 将最后元素插入堆中
            push_heap(all(gifts));
        }

        return Sum(gifts);
    }
};

// 例题：
// 2558. 从数量最多的堆取走礼物